#include "Model.h"
#include "Camera.h"
#include "Vector3.h"
#include "WorldTransform.h"

class PlayerBullet {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Init(Model* model, const Vector3& pos);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	void Draw(Camera* camera);

private:
	WorldTransform worldtransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
};