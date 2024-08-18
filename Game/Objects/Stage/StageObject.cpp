#include "StageObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "Stage.h"

namespace {
	static bool isShowAddCompWindow_ = false;
	static bool isShowSetCompNameWindow_ = false;
	const float MODEL_SCALE = 1.f; // モデルのスケール
	static ComponentType selectCompType_;

	void DrawAddComponent(StageObject* _holder)
	{
		ImGui::Begin("Components that can be added ", &isShowAddCompWindow_);

		for (int i = 0; i < ComponentType::Max; i++) {
			if (ImGui::Selectable(ComponentTypeToString((ComponentType)i).c_str(), selectCompType_ == i)) {

				// 選択しているコンポーネントタイプを代入
				selectCompType_ = (ComponentType)i;

				// ウィンドウを閉じる
				isShowAddCompWindow_ = false;

				// コンポーネント名を入力するウィンドウを表示
				isShowSetCompNameWindow_ = true;
			}
		}

		ImGui::End();

	}

	void DrawSetCompNameWindow(StageObject* _object)
	{
		ImGui::Begin("Plz Set Component Name", &isShowSetCompNameWindow_);
		static char buffer[256] = "";
		ImGui::InputTextWithHint("##Input", "Input New name...", buffer, IM_ARRAYSIZE(buffer));
		ImGui::SameLine();

		if (ImGui::Button("Create Component")) {
			_object->AddComponent(CreateComponent(buffer, selectCompType_, _object));

			isShowSetCompNameWindow_ = false;

			memset(buffer, 0, sizeof(buffer));
		}
		ImGui::End();
	}
}


void StageObject::Save(json& _saveObj)
{
	_saveObj["position"] = { REFERENCE_XMFLOAT3(transform_.position_) };
	_saveObj["scale"] = { REFERENCE_XMFLOAT3(transform_.scale_) };
	_saveObj["rotate"] = { REFERENCE_XMFLOAT3(transform_.rotate_) };
	_saveObj["fallSpeed"] = fallSpeed_;
	_saveObj["isOnGround"] = isOnGround_;
	_saveObj["hitWallCollision_"] = hitWallCollision_;

	_saveObj["modelFilePath_"] = modelFilePath_;

	_saveObj["isOnGround_"] = isOnGround_;
	_saveObj["hitWallCollision_"] = hitWallCollision_;
	_saveObj["fallSpeed_"] = fallSpeed_;

	for (auto component : myComponents_)component->ChildSave(_saveObj["myComponents_"][component->GetName()]);

}

void StageObject::Load(json& _loadObj)
{
	this->DeleteAllComponent();

	if (_loadObj.contains("position_"))transform_.position_ = { _loadObj["position_"][0].get<float>(),_loadObj["position_"][1].get<float>(), _loadObj["position_"][2].get<float>() };
	if (_loadObj.contains("rotate_"))transform_.rotate_ = { _loadObj["rotate_"][0].get<float>(),_loadObj["rotate_"][1].get<float>(), _loadObj["rotate_"][2].get<float>() };
	if (_loadObj.contains("scale_"))transform_.scale_ = { _loadObj["scale_"][0].get<float>(),_loadObj["scale_"][1].get<float>(), _loadObj["scale_"][2].get<float>() };
	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];
	if (_loadObj.contains("isOnGround_"))isOnGround_ = _loadObj["isOnGround_"];
	if (_loadObj.contains("hitWallCollision_"))hitWallCollision_ = _loadObj["hitWallCollision_"];

	modelFilePath_ = _loadObj["modelFilePath_"];

	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];
	if (_loadObj.contains("isOnGround_"))isOnGround_ = _loadObj["isOnGround_"];
	if (_loadObj.contains("hitWallCollision_"))hitWallCollision_ = _loadObj["hitWallCollision_"];

	for (auto& obj : _loadObj["myComponents_"]) {

		// コンポーネントを生成
		Component* comp = CreateComponent(obj["name_"], obj["type_"], this);

		// 子コンポーネントを生成
		for (auto& child : obj["childComponents_"])comp->AddChildComponent(CreateComponent(child["name_"], child["type_"], this));

		// "myComponents_"に追加
		this->AddComponent(comp);
	}

	// コンポーネント情報を読込
	for (auto comp : myComponents_)comp->ChildLoad(_loadObj["myComponents_"][comp->GetName()]);
}

void StageObject::DrawImGui()
{
	ImGui::Text(this->objectName_.c_str());
	ImGui::SameLine();

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// オブジェクトの削除ボタン
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//if (ImGui::SmallButton("delete"))((Stage*)FindObject("Stage"))->DeleteStageObject(this);
	//ImGui::Separator();

	if (ImGui::TreeNode("name")) {
		ImGui::Text("Current name : %s", this->objectName_.c_str());
		char buffer[256] = "";
		if (ImGui::InputTextWithHint("##Input", "Input New name...", buffer, IM_ARRAYSIZE(buffer)))
			this->objectName_ = buffer;
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("transform_")) {
		ImGui::DragFloat3("position_", &transform_.position_.x, 0.1f);
		ImGui::DragFloat3("rotate_", &transform_.rotate_.x, 1.f, -360.f, 360.f);
		ImGui::DragFloat3("scale_", &transform_.scale_.x, 0.1f, 0.f, LONG_MAX);
		ImGui::TreePop();
	}

	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// コンポーネントの情報を描画
	// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (ImGui::TreeNode("myComponents_")) {
		ImGui::SameLine();

		// コンポーネント追加ボタンを描画
		if (ImGui::SmallButton("AddComponent"))isShowAddCompWindow_ = true;

		// 保有するコンポーネントの情報を描画
		for (auto comp : myComponents_)comp->ChildDrawImgui();
		ImGui::TreePop();
	}



	// コンポーネント追加ウィンドウを描画
	if (isShowAddCompWindow_)DrawAddComponent(this);
	if (isShowSetCompNameWindow_)DrawSetCompNameWindow(this);
}

bool StageObject::AddComponent(Component* _component)
{
	if (_component == nullptr)return false;
	_component->ChildInitialize();

	myComponents_.push_back(_component);
	return true;
}

Component* StageObject::FindComponent(string _name)
{
	Component* result = nullptr;

	for (auto comp : myComponents_) {
		if (comp->GetName() == _name) {
			result = comp;
			break;
		}
		result = comp->GetChildComponent(_name);
		if (result != nullptr)break;
	}

	return result;
}

vector<Component*> StageObject::FindComponent(ComponentType _Type)
{
	vector<Component*>result;
	for (auto comp : myComponents_) {
		if (comp->GetType() == _Type)result.push_back(comp);

		auto childComps = comp->GetChildComponent(_Type);
		result.insert(result.end(), childComps.begin(), childComps.end());
	}
	return result;
}

bool StageObject::DeleteComponent(Component* _component)
{
	auto it = std::find(myComponents_.begin(), myComponents_.end(), _component);
	if (it == myComponents_.end())return false;

	//ちゃんと削除されたかどうかの確認
	myComponents_.erase(it); return true;

}

bool StageObject::DeleteAllComponent()
{
	myComponents_.clear(); return true;
}

//void StageObject::OnGround(float _fallspeed)
//{
//	if (isOnGround_ == false)return;
//
//	Stage* pStage = static_cast<Stage*>(FindObject("Stage"));
//	if (pStage == nullptr)return;
//	auto stage = pStage->GetStageObject();
//
//	for (auto obj : stage) {
//		if (obj->GetObjectName() == this->objectName_)
//			continue;
//		int StageModel = obj->modelHandle_;
//		if (StageModel < 0)continue;
//
//		RayCastData rayCastData;
//
//		rayCastData.start = transform_.position_;
//		rayCastData.dir = XMFLOAT3(0, -1, 0);
//		Model::RayCast(StageModel, &rayCastData);
//		if (rayCastData.hit) {
//			transform_.position_.y -= (rayCastData.dist - (MODEL_SCALE / 2)) * _fallspeed;
//
//		}
//	}
//}

//void StageObject::CollisionWall()
//{
//	if (!hitWallCollision_)return;
//
//	Stage* pStage = static_cast<Stage*>(FindObject("Stage"));
//	if (pStage == nullptr)return;
//	auto stage = pStage->GetStageObject();
//
//	for (auto obj : stage) {
//		if (obj->GetObjectName() == this->objectName_)
//			continue;
//		int StageModel = obj->modelHandle_;
//		if (StageModel < 0)continue;
//
//		vector<XMFLOAT3>directions{
//			XMFLOAT3(1,0,0),
//			XMFLOAT3(-1,0,0),
//			XMFLOAT3(0,0,1),
//			XMFLOAT3(0,0,-1)
//		};
//
//		for (auto dir : directions) {
//			RayCastData rayCastData;
//
//			rayCastData.start = transform_.position_;
//			rayCastData.dir = XMFLOAT3(0, -1, 0);
//			Model::RayCast(StageModel, &rayCastData);
//
//			if (rayCastData.dist < 0.6f && rayCastData.dist > 0.0f) {
//				if (dir.x != 0) {
//					transform_.position_.x -= dir.x * (0.6f - rayCastData.dist);
//				}
//				else if (dir.z != 0) {
//					transform_.position_.z -= dir.z * (0.6f - rayCastData.dist);
//				}
//			}
//		}
//	}
//
//}

void StageObject::OnCollision(GameObject* _target, Collider* _collider)
{
	// 保有するコンポーネントの衝突処理
	for (auto comp : myComponents_)comp->ChildOnCollision(_target, _collider);
}



void StageObject::PlayAnimation(int _startAnim, int _endAnim, float _animSpeed)
{
	Model::SetAnimFrame(modelHandle_, _startAnim, _endAnim, _animSpeed);
}

StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent)
{
	StageObject* stageobj = new StageObject(_name, _modelFilePath, _parent);

	stageobj->Initialize();

	if (_parent != nullptr)_parent->PushBackChild(stageobj);

	return stageobj;
}

StageObject::StageObject(string _name, string _modelFilePath, GameObject* _parent)
	:GameObject(_parent, _name), modelFilePath_(_modelFilePath), modelHandle_(-1), myComponents_(), fallSpeed_(1), isOnGround_(false)
{
}




void StageObject::Initialize()
{
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= 0);

	for (auto comp : myComponents_)comp->ChildInitialize();

}

void StageObject::Update()
{
	for (auto comp : myComponents_)comp->ChildUpdate();
	OnGround(fallSpeed_);
	CollisionWall();
}

void StageObject::Draw()
{
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
}

void StageObject::Release()
{
	// 保有するコンポーネントの開放処理
	for (auto comp : myComponents_) {
		comp->ChildRelease();
		delete comp;
	}
	myComponents_.clear();
}
