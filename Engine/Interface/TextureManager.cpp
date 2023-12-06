#include "TextureManager.h"
#include "DirectXCommon.h"
#include "WinAPI.h"
//DirectXCommon dirX;
int TextureManager::Initialize(const std::string& filePath) {
	sDirectXCommon_ = DirectXCommon::GetInstance();
	sWinAPI_ = WinAPI::GetInstance();
	// Textureを読んで転送する
	// ミップマップの作成
	DirectX::ScratchImage mipImages_ = LoadTexture(filePath);
	const DirectX::TexMetadata& metadata = mipImages_.GetMetadata();
	textureResource_ = CreateTextureResource(sDirectXCommon_->GetDevice().Get(), metadata);
	UploadTextureData(textureResource_.Get(), mipImages_);

	// metaDataを基にSRVの設定
	srvDesc_.Format = metadata.format;
	srvDesc_.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc_.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャfi
	srvDesc_.Texture2D.MipLevels = UINT(metadata.mipLevels);
	
	// SRVを作成するDescriptorHeapの場所を決める
	textureSrvHandleCPU_[index_] = sDirectXCommon_->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	textureSrvHandleGPU_[index_] = sDirectXCommon_->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	// 先頭はImGuiが使っているのでその次を使う
	textureSrvHandleCPU_[index_].ptr += sDirectXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * index_;
	textureSrvHandleGPU_[index_].ptr += sDirectXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * index_;
	// SRVの生成
	sDirectXCommon_->GetDevice()->CreateShaderResourceView(textureResource_.Get(), &srvDesc_, textureSrvHandleCPU_[index_]);
	uint32_t returnIndex = index_;
	index_++;
	return returnIndex;
};

void TextureManager::Release() {
}


//void TextureManager::SetTexture() {
//	sDirectXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU_);
//};


DirectX::ScratchImage TextureManager::LoadTexture(const std::string& filePath) {
	////// テクスチャファイルを呼んでプログラムを使えるようにする
	std::wstring filePathW = ConvertString(filePath);
	// テクスチャファイルを呼んでプログラムを使えるようにする
	 DirectX::ScratchImage image{};
	// エラー検知用変数
	HRESULT hr_ = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);

	// ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr_ = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr_));
	
	// ミップマップ付きのデータを渡す
	return mipImages;
}

Microsoft::WRL::ComPtr <ID3D12Resource> TextureManager::CreateTextureResource(Microsoft::WRL::ComPtr <ID3D12Device> device, const DirectX::TexMetadata& metadata)
{
	Microsoft::WRL::ComPtr <ID3D12Resource> resource_;
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

	resource_->SetName(L"AAAAAAA");
	return resource_;

}


void TextureManager::UploadTextureData(Microsoft::WRL::ComPtr <ID3D12Resource> texture, const DirectX::ScratchImage& mipImages) {
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





