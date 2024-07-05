#include "PSOPostEffect.h"
#include "Effect/GrayScale.h"
#include "Effect/Vignette.h"
#include "Effect/DepthOutline.h"
#include "Effect/Dissolve.h"
#include "Effect/FullScreen.h"
#include "Effect/GaussianBlur.h"
#include "Effect/RadialBlur.h"
#include "Effect/Random.h"
#include <d3dx12.h>



void PSOPostEffect::Init()
{
	currentEffectNo_ = IPostEffectState::GetEffectNo();
	effectArr_[PostEffectMode::kFullScreen] = std::make_unique<FullScreen>();
	effectArr_[PostEffectMode::kGrayscale] = std::make_unique<GrayScale>();
	effectArr_[PostEffectMode::kVignetting] = std::make_unique<Vignette>();
	effectArr_[PostEffectMode::kGaussianFilter] = std::make_unique<GaussianBlur>();
	effectArr_[PostEffectMode::kDissolve] = std::make_unique<Dissolve>();
	effectArr_[PostEffectMode::kOutline] = std::make_unique<DepthOutline>();
	effectArr_[PostEffectMode::kRadialBlur] = std::make_unique<RadialBlur>();
	effectArr_[PostEffectMode::kRandom] = std::make_unique<Random>();
	effectArr_[currentEffectNo_]->Init();
	property = effectArr_[currentEffectNo_]->CreatePipelineStateObject();
}

void PSOPostEffect::EffectChangeCheck()
{
	// シーンのチェック
	prevEffectNo_ = currentEffectNo_;
	currentEffectNo_ = IPostEffectState::GetEffectNo();

	// シーン変更チェック
	if (prevEffectNo_ != currentEffectNo_) {
		effectArr_[currentEffectNo_]->Init();
		property = effectArr_[currentEffectNo_]->CreatePipelineStateObject();
	}
}

void PSOPostEffect::SetCommand(PostProcess* postProcess)
{
	effectArr_[currentEffectNo_]->CommandRootParameter(postProcess);
}




PSOPostEffect* PSOPostEffect::GatInstance() {
	static PSOPostEffect instance;
	return &instance;
}
