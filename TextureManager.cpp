#include "TextureManager.h"
#include"function.h"
#include"WinApp.h"
#include"DirXCommon.h"
#include"mathFunction.h"
#include"ImGuiCommon.h"

TextureManager::TextureManager() {



};





ID3D12Resource* TextureManager::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {
	ID3D12Resource* resource= nullptr;

	D3D12_RESOURCE_DESC resourceDesc{};
	// バッファリソース。テクスチャの場合はまた別の設定をする
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = sizeInBytes;// リソースのサイズ。今回はVector4を3頂点分
	//バッファの場合はこれらは1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	// バッファに場合はこれにする決まり
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&resource));
	assert(SUCCEEDED(hr));

	return resource;
};

D3D12_VERTEX_BUFFER_VIEW TextureManager::CreateBufferView() {
	D3D12_VERTEX_BUFFER_VIEW view{};

	//リソースの先頭のアドレスから使う
	view.BufferLocation = vertexResource->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点3つ分のサイズ
	view.SizeInBytes = sizeof(Vector4) * 3;
	// 1頂点あたりのサイズ
	view.StrideInBytes = sizeof(Vector4);
	

	return view;
};


	//ID3D12Resource* CreateBufferResourceDesc(ID3D12Device* device, size_t sizeInBytes);

void TextureManager::Initialize(WinApp* winApp, DirX* dirX, Vector4* vertexDataA, Vector4 DrawColor) {
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;


	// シリアライズしてバイナリにする
	signatureBlob = nullptr;// RootParmeter作成。複数でっていできるので配列。今回は結果１つだけなので長さ1の配列
	D3D12_ROOT_PARAMETER rootParamerters[2] = {};
	rootParamerters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // CBVを使う
	rootParamerters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;  // PixelShaderで使う
	rootParamerters[0].Descriptor.ShaderRegister = 0; //レジスタ番号0とバインド

	rootParamerters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // CBVを使う
	rootParamerters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;  // vertexShaderで使う
	rootParamerters[1].Descriptor.ShaderRegister = 0; //レジスタ番号0とバインド

	descriptionRootSignature.pParameters = rootParamerters; // ルートパラメータ配列へのポインタ
	descriptionRootSignature.NumParameters = _countof(rootParamerters); // 配列の長さ
	errorBlob = nullptr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr)) {
		ConsoleLog(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	// バイナリを元に生成
	rootSignature = nullptr;
	hr = dirX->device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(hr));


	// InputLayout
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

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
		L"vs_6_0", dirX->dxcUtils, dirX->dxcCompiler, dirX->includeHandler);
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = CompileShader(L"Object3d.PS.hlsl",
		L"ps_6_0", dirX->dxcUtils, dirX->dxcCompiler, dirX->includeHandler);
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
	//実際に生成
	graphicsPipelineState = nullptr;
	hr = dirX->device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&graphicsPipelineState));
	assert(SUCCEEDED(hr));

	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;// Uploadheapを使う
	//バッファリソース
	
	// 実際に頂点リソースを作る
	vertexResource = CreateBufferResource(dirX->device, sizeof(Vector4) * 3);

	vertexBufferView = CreateBufferView();
	

	// 頂点リソースにデータを書き込む
	vertexData = nullptr;
	// 書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));



	// 実際に頂点リソースを作る
	materialResource = CreateBufferResource(dirX->device, sizeof(Vector4));

	materialBufferView = CreateBufferView();;
	// 頂点リソースにデータを書き込む
	materialData = nullptr;
	// 書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 色のデータを変数から読み込み
	*materialData = DrawColor;


	//バッファリソース
	// データを書き込む
	wvpData = nullptr;
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	wvpResource = CreateBufferResource(dirX->device, sizeof(Matrix4x4));
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
		//左下
	vertexData[0] = vertexDataA[0];
	//上
	vertexData[1] = vertexDataA[1];
	//右下
	vertexData[2] = vertexDataA[2];
	
	//マテリアルにデータを書き込む
	

	//クライアント領域のサイズと一緒にして画面全体に表示
	viewport.Width = (float)winApp->kClientWidth;
	viewport.Height = (float)winApp->kClientHeight;
	viewport.TopLeftX = 1;
	viewport.TopLeftY = 1;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;


	// 基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = winApp->kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = winApp->kClientHeight;

	
};

void TextureManager::Update(DirX* dirX) {
	dirX->commandList->RSSetViewports(1, &viewport);  //viewportを設定
	dirX->commandList->RSSetScissorRects(1, &scissorRect);    //Scirssorを設定:
	// RootSignatureを設定。PSOに設定しているけど別途設定が必要
	dirX->commandList->SetGraphicsRootSignature(rootSignature);
	dirX->commandList->SetPipelineState(graphicsPipelineState);    //PSOを設定
	dirX->commandList->IASetVertexBuffers(0, 1, &vertexBufferView);    //VBVを設定
	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	dirX->commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	dirX->commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	dirX->commandList->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

	// 描画！（DrawCall/ドローコール）・3頂点で1つのインスタンス。インスタンスについては今後
	dirX->commandList->DrawInstanced(3, 1, 0, 0);
};


void TextureManager::Release() {
	vertexResource->Release();
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
};