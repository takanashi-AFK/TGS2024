#pragma once

#include"../../../Engine/GameObject/GameObject.h"
#include"Components/Component.h"
#include<vector>
#include<string>

using std::vector;
using std::string;

class StageObject :public GameObject
{
protected:
	vector<Component*>myComponents_;
	string modelFilePath_;
	int modelHandle_;
	bool isOnGround_;
	bool hitWallCollision_;//ŽqƒŠƒWƒ‡ƒ“‚ª•Ç‚É“–‚½‚Á‚½‚©‚Ç‚¤‚©
	float fallSpeed_;

public:
	StageObject(string _name, string _modelFilePath, GameObject* _parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	virtual void Save(json& _saveObj);

	virtual  void Load(json& _loadObj);

	virtual void DrawImGui();

	bool AddComponent(Component* _component);

	Component* FindComponent(string _name);

	vector<Component*>FindComponent(ComponentType _Type);

	bool DeleteComponent(Component* _component);

	bool DeleteAllComponent();

	int GetModelHandle() { return modelHandle_; }

	void OnGround(float _fallspeed);

	void CollisionWall();

	void OnCollision(GameObject* _target, Collider* _collider) override;

	void PlayAnimation(int _startAnim, int _endAnim, float _animSpeed);

	void SetModelHandle(int _handle) { modelHandle_ = _handle; }
};

StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent);