#include "Triangle.h"
#include <mathFunction.h>

void Triangle::Initialize(ViewProjection* viewProjection, Vector4 DrawColor) {

	WinApp* sWinApp = WinApp::GetInstance();
	sDirectXCommon_ = DirectXCommon::GetInstance();
	//バッファリソース

	// 実際に頂点リソースを作る
	vertexResource = Mesh::CreateBufferResource(sDirectXCommon_->GetDevice(), sizeof(VertexData) * 6);

	vertexBufferView = CreateBufferView();


	// 頂点リソースにデータを書き込む
	vertexData_ = nullptr;
	// 書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	//左下
	vertexData_[0].position = { -1.0f,-1.0f ,0.0f,1.0f };;
	vertexData_[0].normal = {
		vertexData_[0].position.x,
		vertexData_[0].position.y,
		vertexData_[0].position.z };
	vertexData_[0].texcorrd =  { 0.0f,1.0f };
	//上
	vertexData_[1].position = { 0.0f,1.0f ,0.0f,1.0f };
	vertexData_[1].normal = {
		vertexData_[1].position.x,
		vertexData_[1].position.y,
		vertexData_[1].position.z };
	vertexData_[1].texcorrd = { 0.5f,0.0f };
	//右下
	vertexData_[2].position = { 1.0f,-1.0f,0.0f,1.0f };
	vertexData_[2].normal = {
		vertexData_[2].position.x,
		vertexData_[2].position.y,
		vertexData_[2].position.z };
	vertexData_[2].texcorrd = { 1.0f,1.0f };

	//左下
	vertexData_[3].position = { -1.0f,-1.0f ,1.0f,1.0f };
	vertexData_[3].normal = {
		vertexData_[3].position.x,
		vertexData_[3].position.y,
		vertexData_[3].position.z };
	vertexData_[3].texcorrd = { 0.0f,1.0f };
	//上
	vertexData_[4].position = { 0.0f,0.0f ,0.0f,1.0f };
	vertexData_[4].normal = {
		vertexData_[4].position.x,
		vertexData_[4].position.y,
		vertexData_[4].position.z };
	vertexData_[4].texcorrd = { 0.5f,0.0f };
	//右下
	vertexData_[5].position = { 0.5f,-0.5f,-0.5f,1.0f };
	vertexData_[5].normal = {
		vertexData_[5].position.x,
		vertexData_[5].position.y,
		vertexData_[5].position.z };
	vertexData_[5].texcorrd = { 1.0f,1.0f };

	viewProjection_ = viewProjection;
	// 実際に頂点リソースを作る
	materialResource = Mesh::CreateBufferResource(sDirectXCommon_->GetDevice(), sizeof(Material));

	materialBufferView = CreateBufferView();;
	// 頂点リソースにデータを書き込む
	materialData = nullptr;
	// 書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 色のデータを変数から読み込み
	materialData->color = DrawColor;


	//バッファリソース
	// データを書き込む
	TransformationData = nullptr;
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	wvpResource = Mesh::CreateBufferResource(sDirectXCommon_->GetDevice(), sizeof(TransformationMatrix));
	// 書き込むためのアドレスを取得
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&TransformationData));
	//単位行列を書き込んでいく
	TransformationData->World = MakeIdentity4x4();

	directionalLightData = nullptr;
	directionalLightResource = Mesh::CreateBufferResource(sDirectXCommon_->GetDevice(), sizeof(DirectionalLight));
	// 書き込むためのアドレスを取得
	directionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));

	// デフォルト値はとりあえず以下のようにしておく
	directionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLightData->direction = { 0.0f,-1.0f,0.0f };
	directionalLightData->intensity = 1.0f;

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
};


void Triangle::Draw(WorldTransform worlsTransform, ViewProjection* viewProjection, Vector4 DrawColor) {
	pso_ = PSO::GatInstance();

	viewProjection_ = viewProjection;

	Matrix4x4 worldMatrix = worlsTransform.matWorld_;
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewProjection_->viewMatrix, viewProjection_->projectionMatrix));
	TransformationData->WVP = worldViewProjectionMatrix;
	TransformationData->World = MakeIdentity4x4();
	// 色のデータを変数から読み込み
	materialData->color = DrawColor;
	sDirectXCommon_->GetCommandList()->RSSetViewports(1, &viewport);  //viewportを設定
	sDirectXCommon_->GetCommandList()->RSSetScissorRects(1, &scissorRect);    //Scirssorを設定:
	// RootSignatureを設定。PSOに設定しているけど別途設定が必要
	sDirectXCommon_->GetCommandList()->SetGraphicsRootSignature(pso_->GetProperty().rootSignature.Get());
	sDirectXCommon_->GetCommandList()->SetPipelineState(pso_->GetProperty().graphicsPipelineState.Get());    //PSOを設定
	sDirectXCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);    //VBVを設定
	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	sDirectXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	sDirectXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	sDirectXCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

	// SRV のDescriptorTableの先頭を設定。2はrootParameter[2]である。
	sDirectXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->textureSrvHandleGPU_);
	// 描画！（DrawCall/ドローコール）・3頂点で1つのインスタンス。インスタンスについては今後
	sDirectXCommon_->GetCommandList()->DrawInstanced(6, 1, 0, 0);
};

D3D12_VERTEX_BUFFER_VIEW Triangle::CreateBufferView() {
	D3D12_VERTEX_BUFFER_VIEW view{};

	//リソースの先頭のアドレスから使う
	view.BufferLocation = vertexResource->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点3つ分のサイズ
	view.SizeInBytes = sizeof(VertexData) * 6;
	// 1頂点あたりのサイズ
	view.StrideInBytes = sizeof(VertexData);


	return view;
};
