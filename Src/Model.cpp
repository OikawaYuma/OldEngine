#include "Model.h"
#include "DirectXCommon.h"


Model::Model() {};
ModelData Model::LoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	ModelData modelData; // 構築するMataData
	std::vector<Vector4> positions; // 位置
	std::vector<Vector3> normals; // 法線
	std::vector<Vector2> texcoords; // テクスチャ座標
	std::string line; // ファイルから読んだ1行を格納するもの

	std::ifstream file(directoryPath + "/" + filename); // ファイルを開く
	assert(file.is_open()); // とりあえず開けなかったら止める

	while(std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier; // 先頭の識別子を読む

		// identifierに応じた処理
		if (identifier == "v") {
			Vector4 position;
			s >> position.x >> position.y >> position.z;
			position.w = 1.0f;
			position.z *= -1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt") {
			Vector2 texcoord;
			s >> texcoord.x >> texcoord.y;
			
			texcoord.y *= -1.0f;// -texcoord.y; //- texcoord.y;
			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn") {
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			normal.z *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {
			VertexData triangle[3];
			// 面は三角形限定。その他は未対応
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				// 頂点の要素へのIndexは「位置/UV/法線」で格納されているので、分解してIndexを取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					std::getline(v, index, '/');// 区切りでインデックスを読んでいく
					elementIndices[element] = std::stoi(index);

				}
				// 要素へのIndexから、実際の要素の値を取得して、頂点を構築する
				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
				//position.x *= -1.0f;
				//texcoord.y = 1.0f - texcoord.y;
				//normal.x *= -1.0f;
			
				VertexData vertex = { position, texcoord, normal };
				modelData.vertices.push_back(vertex);
				
				triangle[faceVertex] = { position,texcoord,normal };
				
			}
			modelData.vertices.push_back(triangle[2]);
			modelData.vertices.push_back(triangle[1]);
			modelData.vertices.push_back(triangle[0]);
			
		}
		else if (identifier == "mtllib") {
			// materialtemplateLibraryファイルの名前を取得する
			std::string materialFilename;
			s >> materialFilename;
			// 基本的にobjファイルと同一階層にmtlは存在させるので、ディレクトリ名とファイル名を渡す
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
		}
		
	}
	return modelData;

};

MaterialData Model::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename) {
	MaterialData materialData;// 構築するMaterialData
	std::string line; // ファイルから読んだ1行をかくのうするもの
	std::ifstream file(directoryPath + "/" + filename); // ファイルを開く
	assert(file.is_open()); // とりあえず開けなかったら止める

	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;

		// identiferに応じた処理
		if (identifier == "map_Kd") {
			std::string textureFilename;
			s >> textureFilename;
			// 連結してファイルパスにする
			materialData.textureFilePath = directoryPath + "/" + textureFilename;
		}
		
	}

		return materialData;
};

void Model::Initialize(const std::string& directoryPath, const std::string& filename) {
	WinApp* sWinApp = WinApp::GetInstance();
	directXCommon_ = DirectXCommon::GetInstance();

	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;


	// シリアライズしてバイナリにする
	signatureBlob = nullptr;
	// RootParmeter作成。複数でっていできるので配列。今回は結果１つだけなので長さ1の配列
	rootParamerters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // CBVを使う
	rootParamerters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;  // PixelShaderで使う
	rootParamerters[0].Descriptor.ShaderRegister = 0; //レジスタ番号0とバインド

	rootParamerters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // CBVを使う
	rootParamerters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;  // vertexShaderで使う
	rootParamerters[1].Descriptor.ShaderRegister = 0; //レジスタ番号0とバインド

	descriptorRange_[0].BaseShaderRegister = 0; // 0から始まる
	descriptorRange_[0].NumDescriptors = 1; // 数は1つ
	descriptorRange_[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV; // SRVを使う
	descriptorRange_[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // Offsetを自動計算

	rootParamerters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescripterTableを使う
	rootParamerters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	rootParamerters[2].DescriptorTable.pDescriptorRanges = descriptorRange_; // Tableの中身の配列を指定
	rootParamerters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange_); // Tableで利用する数

	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイナリフィルタ
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 0~1の範囲外をリピート
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX; // ありったけのMipmapを使う
	staticSamplers[0].ShaderRegister = 0; // レジスタ番号0を使う
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う

	descriptionRootSignature.pParameters = rootParamerters; // ルートパラメータ配列へのポインタ
	descriptionRootSignature.NumParameters = _countof(rootParamerters); // 配列の長さ
	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

	errorBlob = nullptr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr)) {
		ConsoleLog(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	// バイナリを元に生成
	rootSignature = nullptr;
	hr = directXCommon_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(hr));


	// InputLayout
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	// blendStateの設定
	//すべての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;


	 //裏面（時計回り）を表示しない
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	// Shaderをコンパイルする
	vertexShaderBlob = CompileShader(L"Object3d.VS.hlsl",
		L"vs_6_0", directXCommon_->GetDxcUtils(), directXCommon_->GetDxcCompiler(), directXCommon_->GetIncludeHandler());
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = CompileShader(L"Object3d.PS.hlsl",
		L"ps_6_0", directXCommon_->GetDxcUtils(), directXCommon_->GetDxcCompiler(), directXCommon_->GetIncludeHandler());
	assert(pixelShaderBlob != nullptr);

	graphicsPipelineStateDesc.pRootSignature = rootSignature; // RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(),
	vertexShaderBlob->GetBufferSize() };//vertexShader
	graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(),
	pixelShaderBlob->GetBufferSize() };// PixelShader
	graphicsPipelineStateDesc.BlendState = blendDesc;//BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //ReterizerState
	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//利用するトポロジ（形状）のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	// どのように画面に色を打ち込むかの設定（気にしなくてよい）
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// DeptjStencilの設定
	graphicsPipelineStateDesc.DepthStencilState = directXCommon_->GetDepthStencilDesc();
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;



	//実際に生成
	graphicsPipelineState = nullptr;
	hr = directXCommon_->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&graphicsPipelineState));
	assert(SUCCEEDED(hr));

	// モデル読み込み
	modelData_ = LoadObjFile(directoryPath, filename);

	// 頂点リソースを作る
	vertexResource_ = Mesh::CreateBufferResource(directXCommon_->GetDevice(), sizeof(VertexData) * modelData_.vertices.size());
	// 頂点バッファビューを作成する
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress(); // リソースの先頭のアドレスから使う
	vertexBufferView_.SizeInBytes = UINT(sizeof(VertexData) * modelData_.vertices.size()); // 使用するリソースのサイズは頂点のサイズ
	vertexBufferView_.StrideInBytes = sizeof(VertexData); // 1頂点当たりのサイズ

	// 頂点リソースにデータを書き込む
	vertexData_ = nullptr;
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
	std::memcpy(vertexData_, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());

	// 実際に頂点リソースを作る
	materialResource = Mesh::CreateBufferResource(directXCommon_->GetDevice(), sizeof(Vector4));

	/*materialBufferView = CreateBufferView();;*/
	// 頂点リソースにデータを書き込む
	materialData = nullptr;
	// 書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 色のデータを変数から読み込み
	*materialData = {1.0f,1.0f,1.0f,1.0f};
	//バッファリソース
	// データを書き込む
	wvpData = nullptr;
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	wvpResource = Mesh::CreateBufferResource(directXCommon_->GetDevice(), sizeof(Matrix4x4));
	// 書き込むためのアドレスを取得
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//単位行列を書き込んでいく
	*wvpData = MakeIdentity4x4();

	//クライアント領域のサイズと一緒にして画面全体に表示
	viewport.Width = (float)sWinApp->GetKClientWidth();
	viewport.Height = (float)sWinApp->GetKClientHeight();
	viewport.TopLeftX = 1;
	viewport.TopLeftY = 1;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;


	// 基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = sWinApp->GetKClientWidth();
	scissorRect.top = 0;
	scissorRect.bottom = sWinApp->GetKClientHeight();

};

void Model::Update() {

};


void Model::Draw() {
	// 色のデータを変数から読み込み
	*materialData = {1.0f,1.0f,1.0f,1.0f};
	directXCommon_->GetCommandList()->RSSetViewports(1, &viewport);  //viewportを設定
	directXCommon_->GetCommandList()->RSSetScissorRects(1, &scissorRect);    //Scirssorを設定:
	directXCommon_->GetCommandList()->SetGraphicsRootSignature(rootSignature);
	directXCommon_->GetCommandList()->SetPipelineState(graphicsPipelineState);    //PSOを設定
	directXCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);    //VBVを設定
	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	directXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	directXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	directXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

	directXCommon_->GetCommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);
}

void Model ::Release() {
	vertexResource_->Release();
	materialResource->Release();
	wvpResource->Release();
	graphicsPipelineState->Release();
	signatureBlob->Release();
	if (errorBlob) {
		errorBlob->Release();
	}
	rootSignature->Release();
	pixelShaderBlob->Release();
	vertexShaderBlob->Release();

}
