#include "TextureManager.h"
#include "DirectXCommon.h"
#include "WinApp.h"
//DirectXCommon dirX;
void TextureManager::Initialize(  const std::string& filePath,int num) {
	sDirectXCommon_ = DirectXCommon::GetInstance();
	sWinApp_ = WinApp::GetInstance();
	// Textureを読んで転送する
	mipImages_ = LoadTexture(filePath);
	const DirectX::TexMetadata& metadata = mipImages_.GetMetadata();
	textureResource_ = CreateTextureResource(sDirectXCommon_->GetDevice(), metadata);
	UploadTextureData(textureResource_, mipImages_);

	// metaDataを基にSRVの設定
	srvDesc_.Format = metadata.format;
	srvDesc_.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc_.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャfi
	srvDesc_.Texture2D.MipLevels = UINT(metadata.mipLevels);

	// SRVを作成するDescriptorHeapの場所を決める
	textureSrvHandleCPU_ = sDirectXCommon_->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	textureSrvHandleGPU_ = sDirectXCommon_->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	// 先頭はImGuiが使っているのでその次を使う
	textureSrvHandleCPU_.ptr += sDirectXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * num;
	textureSrvHandleGPU_.ptr += sDirectXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)* num;
	// SRVの生成
	sDirectXCommon_->GetDevice()->CreateShaderResourceView(textureResource_, &srvDesc_, textureSrvHandleCPU_);
	
	

	
	


};

void TextureManager::Update() {
	
	

}


void TextureManager::Release() {
	resource_->Release();
	textureResource_->Release();
	mipImages_.Release();
	
}

//void TextureManager::Update(Mesh* mesh) {
//	descriptorRange_[0].BaseShaderRegister = 0; // 0から始まる
//	descriptorRange_[0].NumDescriptors = 1; // 数は1つ
//	descriptorRange_[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV; // SRVを使う
//	descriptorRange_[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // Offsetを自動計算
//
//	mesh->rootParamerters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescripterTableを使う
//	mesh->rootParamerters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
//	mesh->rootParamerters[2].DescriptorTable.pDescriptorRanges = descriptorRange_; // Tableの中身の配列を指定
//	mesh->rootParamerters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange_); // Tableで利用する数
//
//	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイナリフィルタ
//	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 0~1の範囲外をリピート
//	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
//	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX; // ありったけのMipmapを使う
//	staticSamplers[0].ShaderRegister = 0; // レジスタ番号0を使う
//	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
//	mesh->descriptionRootSignature.pStaticSamplers = staticSamplers;
//	mesh->descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);
//};


void TextureManager::SetTexture() {
	sDirectXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU_);
};


DirectX::ScratchImage TextureManager::LoadTexture(const std::string& filePath) {
	////// テクスチャファイルを呼んでプログラムを使えるようにする
	filePathW_ = ConvertString(filePath);

	// エラー検知用変数
	hr_ = DirectX::LoadFromWICFile(filePathW_.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image_);

	// ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr_ = DirectX::GenerateMipMaps(image_.GetImages(), image_.GetImageCount(), image_.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr_));
	
	// ミップマップ付きのデータを渡す
	return mipImages;
}

ID3D12Resource* TextureManager::CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
{
	// metadataを基にResourceの設定
	resourceDesc_.Width = UINT(metadata.width); // Textureの幅
	resourceDesc_.Height = UINT(metadata.height); // Textureの高さ
	resourceDesc_.MipLevels = UINT16(metadata.mipLevels); // mipmapの数
	resourceDesc_.DepthOrArraySize = UINT16(metadata.arraySize); // 奥行き or 配列Textureの配列数
	resourceDesc_.Format = metadata.format; // TextureのFormat
	resourceDesc_.SampleDesc.Count = 1; // サンプリングカウント。1固定・
	resourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension); // Textureの次元数。普段使っているのは2次元

	// 利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
	heapProperties_.Type = D3D12_HEAP_TYPE_CUSTOM; // 細かい設定を行う
	heapProperties_.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK; // WriteBackポリシーでCPUアクセス可能
	heapProperties_.MemoryPoolPreference = D3D12_MEMORY_POOL_L0; // プロセッサの近くに配置

	// Rewsourceの生成
	resource_ = nullptr;
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties_, // Heapの設定
		D3D12_HEAP_FLAG_NONE, //Heapの特殊な設定。特になし。
		&resourceDesc_, // Resourceの設定
		D3D12_RESOURCE_STATE_GENERIC_READ, // 初回のResourceState。Textureは基本読むだけ
		nullptr, // Clear最適地。使わないのでnullptr
		IID_PPV_ARGS(&resource_));
	assert(SUCCEEDED(hr));
	return resource_;

}


void TextureManager::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages) {
	// Meta情報を取得
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	// 全MipMapについて
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
		// MipMapLevelを指定して書くImageを取得
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
		// Textureに転送
		HRESULT hr = texture->WriteToSubresource(
			UINT(mipLevel),
			nullptr,			   // 全領域へコピー
			img->pixels,		   // 元データアクセス
			UINT(img->rowPitch),   // 1ラインサイズ
			UINT(img->slicePitch)  // 1枚サイズ
		);
		assert(SUCCEEDED(hr));
	}
};





