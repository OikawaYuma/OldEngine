#pragma once
#include "IPostEffectState.h"
#include "PSOProperty.h"
class FullScreen : public IPostEffectState
{
public:
	/// <summary>
	/// 描画に関する設定をまとめる関数
	/// </summary>
	PSOProperty CreatePipelineStateObject() override;
	void Init() override;
	/// <summary>
	/// 設定したことを元にコマンドリストを使う
	/// </summary>
	void CommandRootParameter(PostProcess* postProcess) override;

	std::vector<D3D12_DESCRIPTOR_RANGE> CreateDescriptorRange() override;

	/// <summary>
	/// Shaderに渡す値を決める
	/// </summary>
	/// <returns></returns>
	std::vector<D3D12_ROOT_PARAMETER> CreateRootParamerter(std::vector<D3D12_DESCRIPTOR_RANGE>& descriptorRange) override;

	/// <summary>
	/// PSにの書き込み方の設定
	/// </summary>
	/// <returns></returns>
	std::vector<D3D12_STATIC_SAMPLER_DESC> CreateSampler() override;

	/// <summary>
	/// ShaderとResourceを関係のつけ方を決める関数
	/// </summary>
	D3D12_ROOT_SIGNATURE_DESC CreateRootSignature(PSOProperty& pso, std::vector<D3D12_ROOT_PARAMETER>& rootParameters, std::vector<D3D12_STATIC_SAMPLER_DESC>& samplers) override;

	/// <summary>
	/// VSへ渡す頂点データの指定を行う関数
	/// </summary>
	D3D12_INPUT_LAYOUT_DESC SetInputLayout() override;

	/// <summary>
	/// PSからの出力をどう書き込むかの設定を行う関数
	/// </summary>
	D3D12_BLEND_DESC SetBlendState() override;

	/// <summary>
	/// ラスタライザーに関する設定の関数
	/// </summary>
	D3D12_RASTERIZER_DESC SetRasterrizerState() override;

	/// <summary>
	/// DepthBufferの生成
	/// </summary>
	D3D12_DEPTH_STENCIL_DESC CreateDepth() override;

	
};

