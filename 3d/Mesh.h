#pragma once
#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include <dxcapi.h>

//#include"DirectXCommon.h"
#include "VertexData.h"
#include "Vector4.h"
#include"Vector3.h"
#include"Vector2.h"
#include"Matrix4x4.h"
#include "Material.h"
#include "DirectionLight.h"
#include "TransformationMatrix.h"
#include "wrl.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")

class DirectXCommon;
class WinApp;
class TextureManager;

class Mesh
{
public:
	Mesh();
	~Mesh();
	

	static Microsoft::WRL::ComPtr <ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device,size_t sizeInBytes);
	D3D12_RESOURCE_DESC  CreateBufferResourceDesc(size_t sizeInBytes);
	D3D12_VERTEX_BUFFER_VIEW  CreateBufferView();	
	
private:
	DirectXCommon* sDirectXCommon_ = nullptr;
};

