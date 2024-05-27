#pragma once
#include "StageObject.h"

//ゲームオブジェクトじゃなくてステージオブジェクトを継承するように変更


class Bullet :public StageObject
{
private:
	SphereCollider* collision;
	int modelHandle_;
	bool isActive_;
	int frame;
	float speed_;
	XMVECTOR direction_;
	const int FPS = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");
public:

	Bullet(GameObject* _parent);
	~Bullet();

	//Update関数をオーバーロード
	//XMFLOAT3 _playerPosition, XMVECTOR _directionを引数に追加
	//引数を元に弾を発射する処理を追加
	//弾の移動処理を追加
	//CactanのUpdate関数でBulletのUpdateを呼び出す?


	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void DrawData() override;
	void Save(json& _saveobj) override;
	void Load(json& _loadobj) override;

	void SetSpeed(float _speed) { speed_ = _speed; }
	void SetDirection(XMVECTOR _direction) { direction_ = _direction; }


	/// <summary>
	/// 攻撃開始
	/// </summary>
	void Execute() { isActive_ = true; }
};

