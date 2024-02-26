#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include<cmath>
#include<cassert>
#include <vector>


// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

Vector3 MakeTransform(const Vector3& vector, const Matrix4x4& matrix);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// 1. 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

// 2. 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);


//Matrix4x4 MakeAffineMatrixBillboard(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
Vector3 Add(const Vector3& posa, const Vector3& posb);

Vector3 Normalize(const Vector3& v);

// 線形補間
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
// 内績
float Dot(const Vector3& v1, const Vector3& v2);
Vector3 SLerp(const Vector3& v1, const Vector3& v2, float t);
// 3. ビューポート変換行列
Matrix4x4 MakeViewportMatrix(
	float left, float top, float width, float height, float minDepth, float maxDepth);
// 3. 座標返還
Vector3 Transform1(const Vector3& vector, const Matrix4x4& matrix);

///
Vector3 CatmullRomInterpolation(const Vector3& p0,const Vector3& p1, const Vector3& p2, const Vector3& p3,float t);
Vector3 CatmullRomPosition(const std::vector<Vector3>& points, float t);
