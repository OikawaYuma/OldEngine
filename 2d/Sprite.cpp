#include "Sprite.h"
#include "WinAPI.h"
#include "DirectXCommon.h"
#include "Camera.h"
#include "mathFunction.h"
#include "Mesh.h"



Sprite::Sprite() {};
void Sprite::Initialize() {
	sWinAPI = WinAPI::GetInstance();
	sDirectXCommon = DirectXCommon::GetInstance();

	//rootParamerters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescripterTableを使う
	//rootParamerters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	//rootParamerters[0].DescriptorTable.pDescriptorRanges = descriptorRange_; // Tableの中身の配列を指定
	//rootParamerters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange_); // Tableで利用する数

	// Sprite用の頂点リソースを作る
	vertexResourceSprite_ = Mesh::CreateBufferResource(sDirectXCommon->GetDevice(), sizeof(VertexData) * 4);

	// リソースを先頭のアドレスから使う
	vertexBufferViewSprite_.BufferLocation = vertexResourceSprite_->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferViewSprite_.SizeInBytes = sizeof(VertexData) * 4;
	// 1頂点あたりのサイズ
	vertexBufferViewSprite_.StrideInBytes = sizeof(VertexData);

	vertexResourceSprite_->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSprite_));

	// 1枚目の三角形
	vertexDataSprite_[0].position = { 0.0f,360.0f,0.0f,1.0f };//左下
	vertexDataSprite_[0].texcorrd = { 0.0f,1.0f };
	vertexDataSprite_[1].position = { 0.0f,0.0f,0.0f,1.0f }; // 左上
	vertexDataSprite_[1].texcorrd = { 0.0f,0.0f };
	vertexDataSprite_[2].position = { 640.0f,360.0f,0.0f,1.0f }; // 右下
	vertexDataSprite_[2].texcorrd = { 1.0f,1.0f };

	vertexDataSprite_[3].position = { 640.0f,0.0f,0.0f,1.0f }; // 右上
	vertexDataSprite_[3].texcorrd = { 1.0f,0.0f };

	// 実際に頂点リソースを作る
	materialResource = Mesh::CreateBufferResource(sDirectXCommon->GetDevice(), sizeof(Material));

	/*materialBufferView = CreateBufferView();;*/
	// 頂点リソースにデータを書き込む
	materialData = nullptr;
	// 書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 色のデータを変数から読み込み
	materialData->color = { 1.0f,1.0f,1.0f,1.0f };
	materialData->enableLighting = false;
	materialData->uvTransform = MakeIdentity4x4();



	// Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	transformationMatrixResouceSprite = Mesh::CreateBufferResource(sDirectXCommon->GetDevice(), sizeof(TransformationMatrix));
	// 書き込むためのアドレスを取得
	transformationMatrixResouceSprite->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSprite));
	// 単位行列を書き込んでおく
	*transformationMatrixDataSprite = MakeIdentity4x4();

	// Transform変数の初期化
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	indexResourceSprite = Mesh::CreateBufferResource(sDirectXCommon->GetDevice(), sizeof(uint32_t) * 6);
	// リソースの先頭のアドレスから使う
	indexBufferViewSprite.BufferLocation = indexResourceSprite->GetGPUVirtualAddress();
	// 使用するリソースのサイズはインデックス6つ分のサイズ
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
	// インデックスはuint_tとする
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;

	// インデックスリソースにデータを書き込む
	uint32_t* indexDataSprite = nullptr;
	indexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSprite));
	indexDataSprite[0] = 0;
	indexDataSprite[1] = 1;
	indexDataSprite[2] = 2;
	indexDataSprite[3] = 1;
	indexDataSprite[4] = 3;
	indexDataSprite[5] = 2;

	directionalLightData = nullptr;
	directionalLightResource = Mesh::CreateBufferResource(sDirectXCommon->GetDevice(), sizeof(DirectionalLight));
	// 書き込むためのアドレスを取得
	directionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));

	// デフォルト値はとりあえず以下のようにしておく
	directionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLightData->direction = { 0.0f,-1.0f,0.0f };
	directionalLightData->intensity = 1.0f;

	transformUv = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	//クライアント領域のサイズと一緒にして画面全体に表示
	viewport.Width = (float)sWinAPI->GetKClientWidth();
	viewport.Height = (float)sWinAPI->GetKClientHeight();
	viewport.TopLeftX = 1;
	viewport.TopLeftY = 1;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;


	// 基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = sWinAPI->GetKClientWidth();
	scissorRect.top = 0;
	scissorRect.bottom = sWinAPI->GetKClientHeight();

};
//void Sprite::Update() {
//
//};

void Sprite::Draw() {
	pso_ = PSO::GatInstance();
	// Sprite用のWorldViewProjectMatrixを作る
	Matrix4x4 worldMatrixSprite = MakeAffineMatrix(transform_.scale, transform_.rotate, transform_.translate);
	Matrix4x4 viewMatrixSprite = MakeIdentity4x4();
	Matrix4x4 projectionMatrixSprite = MakeOrthographicMatrix(0.0f, 0.0f, float(sWinAPI->GetKClientWidth()), float(sWinAPI->GetKClientHeight()), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrixSprite = Multiply(worldMatrixSprite, Multiply(viewMatrixSprite, projectionMatrixSprite));
	*transformationMatrixDataSprite = worldViewProjectionMatrixSprite;
	sDirectXCommon->GetCommandList()->RSSetViewports(1, &viewport);  //viewportを設定
	sDirectXCommon->GetCommandList()->RSSetScissorRects(1, &scissorRect);    //Scirssorを設定:
	sDirectXCommon->GetCommandList()->SetGraphicsRootSignature(pso_->GetProperty().rootSignature.Get());
	sDirectXCommon->GetCommandList()->SetPipelineState(pso_->GetProperty().graphicsPipelineState.Get());    //PSOを設定
	sDirectXCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite_); // VBVを設定
	sDirectXCommon->GetCommandList()->IASetIndexBuffer(&indexBufferViewSprite);
	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	sDirectXCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	sDirectXCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	// TransformationmatrixCBufferの場所を設定
	sDirectXCommon->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResouceSprite->GetGPUVirtualAddress());

	// SRV のDescriptorTableの先頭を設定。2はrootParameter[2]である。
	sDirectXCommon->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->textureSrvHandleGPU_);
	sDirectXCommon->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());
	// 描画（DrawCall/ドローコール）
	//sDirectXCommon->GetCommandList()->DrawInstanced(6, 1, 0, 0);
	sDirectXCommon->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}




D3D12_VERTEX_BUFFER_VIEW Sprite::CreateBufferView() {
	D3D12_VERTEX_BUFFER_VIEW view{};

	//リソースの先頭のアドレスから使う
	view.BufferLocation = vertexResourceSprite_->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点3つ分のサイズ
	view.SizeInBytes = sizeof(VertexData) * 6;
	// 1頂点あたりのサイズ
	view.StrideInBytes = sizeof(VertexData);


	return view;
};