#pragma once
#include "DirectXCommon.h"
class ModelManager
{
public:
	void init();
	void Update();
	void Release();
private:
	DirectXCommon* dxCommon_;

public:	//Gettrer
	DirectXCommon* GetDxCommon() const { return dxCommon_; }

};

