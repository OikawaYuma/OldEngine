﻿#include "TextureManager.h"
#include "DirectXCommon.h"
#include "SRVManager.h"
#include "WinAPI.h"
//DirectXCommon dirX;

// resourceを保存する場所を設定
// ImGuiが0に格納されているため1から格納する
int TextureManager::kSRVIndexTop = 1;
int TextureManager::kParIndez = 10;
std::vector<TextureData> TextureManager::textureDatas_;
//// ソースで静的メンバ変数を定義
//Microsoft::WRL::ComPtr <ID3D12Resource> TextureManager::textureResource_[SRVSizes];
//
//D3D12_CPU_DESCRIPTOR_HANDLE TextureManager::textureSrvHandleCPU_[SRVSizes];
//D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::textureSrvHandleGPU_[SRVSizes];
//DirectX::TexMetadata TextureManager::metadata_[SRVSizes];
//D3D12_SHADER_RESOURCE_VIEW_DESC TextureManager::srvDesc_[SRVSizes];
void TextureManager::Init()
{
	textureDatas_.reserve(DirectXCommon::srvDescriptorSize_);
}
int TextureManager::StoreTexture(const std::string& filePath) {
	DirectXCommon *sDirectXCommon = DirectXCommon::GetInstance();
	WinAPI* sWinAPI = WinAPI::GetInstance();

	
		//(DirectXCommon::srvDescriptorSize_);
	textureDatas_.resize(textureDatas_.size() + 1);
	TextureData& textureData = textureDatas_.back();
	// Textureを読んで転送する
	// ミップマップの作成
	DirectX::ScratchImage mipImages_ = LoadTexture(filePath);
	textureData.filePath = filePath;
	textureData.metaData = mipImages_.GetMetadata();
	textureData.resource = CreateTextureResource(sDirectXCommon->GetDevice().Get(), textureData.metaData);
	UploadTextureData(textureData.resource.Get(), mipImages_);

	uint32_t srvIndex = static_cast<uint32_t>(textureDatas_.size() -1) + kSRVIndexTop;
	
	
	// SRVを作成するDescriptorHeapの場所を決める
	textureData.textureSrvHandleCPU = sDirectXCommon->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	textureData.textureSrvHandleGPU = sDirectXCommon->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	// 先頭はImGuiが使っているのでその次を使う
	textureData.textureSrvHandleCPU.ptr += sDirectXCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * srvIndex;
	textureData.textureSrvHandleGPU.ptr += sDirectXCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * srvIndex;
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
	// metaDataを基にSRVの設定
	srvDesc.Format = textureData.metaData.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャfi
	srvDesc.Texture2D.MipLevels = UINT(textureData.metaData.mipLevels);
	// SRVの生成
	sDirectXCommon->GetDevice()->CreateShaderResourceView(textureData.resource.Get(), &srvDesc, textureData.textureSrvHandleCPU);
	//uint32_t returnIndex = srvIndex;
	textureDatas_.push_back(textureData);
	return srvIndex;
};
int  TextureManager::PlusIndex() {
	
	//int  returnIndex = kParIndez ;
	kParIndez++;

	return kParIndez;
}
void TextureManager::Release() {
}



TextureManager* TextureManager::GetInstance() {
	static TextureManager instance;
	return &instance;
}

//void TextureManager::SetTexture() {
//	sDirectXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU_);
//};


const DirectX::TexMetadata& TextureManager::GetMetaData(uint32_t textureIndex)
{
	// 範囲外指定違反チェック
	assert(textureIndex <= SRVSizes);
	//const DirectX::TexMetadata& metadata = metadata_[textureIndex];
	return  textureDatas_[textureIndex].metaData;
	//return  metadata;;
}

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
	
	D3D12_RESOURCE_DESC resourceDesc_{};
	// metadataを基にResourceの設定
	resourceDesc_.Width = UINT(metadata.width); // Textureの幅
	resourceDesc_.Height = UINT(metadata.height); // Textureの高さ
	resourceDesc_.MipLevels = UINT16(metadata.mipLevels); // mipmapの数
	resourceDesc_.DepthOrArraySize = UINT16(metadata.arraySize); // 奥行き or 配列Textureの配列数
	resourceDesc_.Format = metadata.format; // TextureのFormat
	resourceDesc_.SampleDesc.Count = 1; // サンプリングカウント。1固定・
	resourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension); // Textureの次元数。普段使っているのは2次元

	// 利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties_{};
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





