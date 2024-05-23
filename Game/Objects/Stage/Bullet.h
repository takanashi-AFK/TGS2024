#pragma once
//#include "../../../"

//ゲームオブジェクトじゃなくてステージオブジェクトを継承するように変更

const float BULLET_SPEED = 2.0f;
class Bullet :public GameObject
{
private:
	XMFLOAT3 Move_Position;
	XMVECTOR Move_Direction;
	SphereCollider* collision;
public:

	Bullet(GameObject* parent);
	~Bullet();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Attack(XMFLOAT3 _playerPosition, XMVECTOR _direction);

};

