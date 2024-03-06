#include "Object3dManager.h"

void Object3dManager::Init()
{
}

void Object3dManager::Update()
{
}

void Object3dManager::Draw()
{
}

Object3dManager* Object3dManager::GetInstance()
{
    static Object3dManager instance;
    return &instance;
 
}
