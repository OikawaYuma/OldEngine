#include "Sphere.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Mesh.h"
#include "mathFunction.h"

Sphere::Sphere() {

}

Sphere::~Sphere() {

}

void Sphere::Initialize() {
sWinApp = WinApp::GetInstance();
	sDirectXCommon_ = DirectXCommon::GetInstance();
	

	HRESULT hr;
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
	hr = sDirectXCommon_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
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


	// 裏面（時計回り）を表示しない
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	// Shaderをコンパイルする
	vertexShaderBlob = CompileShader(L"Object3d.VS.hlsl",
		L"vs_6_0", sDirectXCommon_->GetDxcUtils(), sDirectXCommon_->GetDxcCompiler(), sDirectXCommon_->GetIncludeHandler());
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = CompileShader(L"Object3d.PS.hlsl",
		L"ps_6_0", sDirectXCommon_->GetDxcUtils(), sDirectXCommon_->GetDxcCompiler(), sDirectXCommon_->GetIncludeHandler());
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
	graphicsPipelineStateDesc.DepthStencilState = sDirectXCommon_->GetDepthStencilDesc();
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;



	//実際に生成
	graphicsPipelineState = nullptr;
	hr = sDirectXCommon_->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&graphicsPipelineState));
	assert(SUCCEEDED(hr));


	//バッファリソース

	// 実際に頂点リソースを作る
	vertexResource = mesh_->CreateBufferResource(sDirectXCommon_->GetDevice(), sizeof(VertexData) * 1536);

	vertexBufferView = CreateBufferView();


	// 頂点リソースにデータを書き込む
	vertexData_ = nullptr;
	// 書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
	const uint32_t kSubdivision = 16;
	float pi = 3.1415f;
	const float kLonEvery = pi * 2.0f / (float)kSubdivision;  // 軽度分割1つ分の角度
	const float kLatEvery = pi / (float)kSubdivision;  // 緯度分割1つ分の角度


	// 緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;// 現在の緯度
		// 経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			uint32_t start = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;// 現在の緯度

			const float latD = pi / kSubdivision;
			const float lonD = 2 * pi / kSubdivision;
			//左下
			vertexData_[start].position = 
			{
						(cos(lat) * cos(lon)),
						(sin(lat)) ,
						(cos(lat) * sin(lon)),
			1.0f};
			vertexData_[start].texcorrd = {
				float(lonIndex) / float(kSubdivision),
				1.0f - float(latIndex) / float(kSubdivision)
			
			};

			vertexData_[start+1].position = {
				(cos(lat + latD) * cos(lon)) ,
				(sin(lat + latD)) ,
				(cos(lat + latD) * sin(lon)),
			1.0f };
			vertexData_[start+1].texcorrd = {
				float(lonIndex) / float(kSubdivision),
				1.0f - float(latIndex +1) / float(kSubdivision)

			};

			vertexData_[start +2].position = {
				(cos(lat) * cos(lon + lonD)),
				(sin(lat)) ,
				(cos(lat) * sin(lon + lonD)) ,
			1.0f };
			vertexData_[start+2].texcorrd = {
				float(lonIndex +1 ) / float(kSubdivision),
				1.0f - float(latIndex) / float(kSubdivision)

			};

			vertexData_[start+3].position = {
				(cos(lat + latD) * cos(lon)) ,
				(sin(lat + latD)) ,
				(cos(lat + latD) * sin(lon)),
			1.0f };
			vertexData_[start+3].texcorrd = {
				float(lonIndex) / float(kSubdivision),
				1.0f - float(latIndex +1) / float(kSubdivision)

			};

			vertexData_[start+4].position = {
				(cos(lat + latD) * cos(lon + lonD)),
				(sin(lat + latD)) ,
				(cos(lat + latD) * sin(lon + lonD)) ,
			1.0f };
			vertexData_[start+4].texcorrd = {
				float(lonIndex + 1) / float(kSubdivision),
				1.0f - float(latIndex + 1) / float(kSubdivision)

			};

			vertexData_[start+5].position = {
				(cos(lat) * cos(lon + lonD)),
				(sin(lat)) ,
				(cos(lat) * sin(lon + lonD)) ,
			1.0f };
			vertexData_[start+5].texcorrd = {
				float(lonIndex + 1) / float(kSubdivision),
				1.0f - float(latIndex) / float(kSubdivision)

			};



		}
	}
	
	


\

	//バッファリソース
	// データを書き込む
	wvpData = nullptr;
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	wvpResource = mesh_->CreateBufferResource(sDirectXCommon_->GetDevice(), sizeof(Matrix4x4));
	// 書き込むためのアドレスを取得
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//単位行列を書き込んでいく
	*wvpData = MakeIdentity4x4();





	////左下
	//vertexData[0] = { -0.5f,-0.5f,0.0f,1.0f };
	////上
	//vertexData[1] = { 0.0f,0.5f,0.0f,1.0f };
	////右下
	//vertexData[2] = { 0.5f,-0.5f,0.0f,1.0f };


	//マテリアルにデータを書き込む


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


}

void Sphere::Update(){
	
}

void Sphere::Draw() {
	//// 色のデータを変数から読み込み

	sDirectXCommon_->GetCommandList()->RSSetViewports(1, &viewport);  //viewportを設定
	sDirectXCommon_->GetCommandList()->RSSetScissorRects(1, &scissorRect);    //Scirssorを設定:
	// RootSignatureを設定。PSOに設定しているけど別途設定が必要
	sDirectXCommon_->GetCommandList()->SetGraphicsRootSignature(rootSignature);
	sDirectXCommon_->GetCommandList()->SetPipelineState(graphicsPipelineState);    //PSOを設定
	sDirectXCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);    //VBVを設定
	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	sDirectXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	//sDirectXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//sDirectXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

	// SRV のDescriptorTableの先頭を設定。2はrootParameter[2]である。
	sDirectXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->textureSrvHandleGPU_);
	// 描画！（DrawCall/ドローコール）・3頂点で1つのインスタンス。インスタンスについては今後
	sDirectXCommon_->GetCommandList()->DrawInstanced(1536, 1, 0, 0);

}

void Sphere::Release() {
	vertexResource->Release();
	//materialResource->Release();
	wvpResource->Release();
}

D3D12_VERTEX_BUFFER_VIEW  Sphere::CreateBufferView() {
	D3D12_VERTEX_BUFFER_VIEW view{};

	//リソースの先頭のアドレスから使う
	view.BufferLocation = vertexResource->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点3つ分のサイズ
	view.SizeInBytes = sizeof(VertexData) * 1536;
	// 1頂点あたりのサイズ
	view.StrideInBytes = sizeof(VertexData);


	return view;
};

void Sphere::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportmatrix, int color) {
	const uint32_t kSubdivision = 16;
	float pi = 3.1415f;
	const float kLonEvery = pi * 2.0f / (float)kSubdivision;  // 軽度分割1つ分の角度
	const float kLatEvery = pi / (float)kSubdivision;  // 緯度分割1つ分の角度


	// 緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;// 現在の緯度
		// 緯度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			uint32_t start = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;// 現在の緯度
			
			const float latD = pi / kSubdivision;
			const float lonD = 2 * pi / kSubdivision;
			Vector3 a = {
				(cos(lat) * cos(lon)),
				(sin(lat)) ,
				(cos(lat) * sin(lon)) };

			Vector3 b = {
				(cos(lat + latD) * cos(lon)) ,
				(sin(lat + latD)) ,
				(cos(lat + latD) * sin(lon))};

			Vector3 c = {
				(cos(lat) * cos(lon + lonD) ),
				(sin(lat)) ,
				(cos(lat) * sin(lon + lonD))  };

			Vector3 d = {
				(cos(lat+latD) * cos(lon + lonD)),
				(sin(lat + latD)) ,
				(cos(lat + latD) * sin(lon + lonD)) };


			
		}
	}
}
