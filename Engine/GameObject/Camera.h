#pragma once
#include "GameObject.h"

namespace Camera
{
	/// <summary> カメラの初期化 </summary>
	void Initialize();

	/// <summary> カメラの更新 </summary>
	void Update();

/*
getter :*/
	/// <summary> 位置を取得 </summary>
	XMFLOAT3 GetPosition();

	/// <summary> 焦点を取得 </summary>
	XMFLOAT3 GetTarget();

	/// <summary> ビュー行列を取得 </summary>
	XMMATRIX GetViewMatrix();

	/// <summary> プロジェクション行列を取得 </summary>
	XMMATRIX GetProjectionMatrix();

	/// <summary> ビルボード行列を取得 </summary>
	XMMATRIX GetBillboardMatrix();

	/// <summary> 視線を取得 </summary>
	XMVECTOR GetSightLine();
/*
setter :*/
	/// <summary> 位置を設定 </summary>
	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);

	/// <summary> 焦点を設定 </summary>
	void SetTarget(XMFLOAT3 target);
	void SetTarget(float x, float y, float z);

	/// <summary> プロジェクション行列を設定 </summary>
	void SetProjectionMatrix(XMMATRIX proj);
	void SetProjectionMatrix(float fov, float aspect, float nearZ, float farZ);
	void SetProjectionMatrix(float aspect);

};