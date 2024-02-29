#pragma once
class Object3dManager
{

	Object3dManager() = default;
	~Object3dManager() = default;
	const Object3dManager& operator=(const Object3dManager&) = delete;
public:
	void Init();
	void Update();
	void Draw();

	static Object3dManager* GetInstance(); 
private:
	//ModelData modelData_;
};

