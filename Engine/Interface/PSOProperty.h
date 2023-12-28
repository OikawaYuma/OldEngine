#pragma once
#include <d3d12.h>
#include "DirectXCommon.h"
struct PSOProperty {
	Microsoft::WRL::ComPtr < ID3D12PipelineState> graphicsPipelineState;
	Microsoft::WRL::ComPtr < ID3D12RootSignature> rootSignature;
	Microsoft::WRL::ComPtr < ID3DBlob> signatureBlob;
	Microsoft::WRL::ComPtr < ID3DBlob> errorBlob;
	Microsoft::WRL::ComPtr < IDxcBlob> vertexShaderBlob;
	Microsoft::WRL::ComPtr < IDxcBlob> pixelShaderBlob;
};