#pragma once
#include "StageObject.h"

//ゲームオブジェクトじゃなくてステージオブジェクトを継承するように変更

const float BULLET_SPEED = 2.0f;
class Bullet :public StageObject
{
private:
	XMFLOAT3 Move_Position;
	XMVECTOR Move_Direction;
	SphereCollider* collision;
	int modelHandle_;
	bool isHit_;
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

	void Attack(XMFLOAT3 _playerPosition, XMVECTOR _direction);

};

