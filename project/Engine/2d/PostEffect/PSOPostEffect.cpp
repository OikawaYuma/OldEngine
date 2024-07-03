#include "PSOPostEffect.h"
#include "Effect/DepthOutline.h"
#include <d3dx12.h>



void PSOPostEffect::Init()
{
	currentEffectNo_ = PostEffectMode::kOutline;
	effectArr_[PostEffectMode::kOutline] = std::make_unique<DepthOutline>();
	property = effectArr_[currentEffectNo_]->CreatePipelineStateObject();
}

void PSOPostEffect::EffectChangeCheck()
{
	// シーンのチェック
	prevEffectNo_ = currentEffectNo_;
	currentEffectNo_ = effectArr_[currentEffectNo_]->GetEffectNo();

	// シーン変更チェック
	if (prevEffectNo_ != currentEffectNo_) {
		property = effectArr_[currentEffectNo_]->CreatePipelineStateObject();
	}
}




PSOPostEffect* PSOPostEffect::GatInstance() {
	static PSOPostEffect instance;
	return &instance;
}
