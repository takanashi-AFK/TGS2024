#include "Stage.h"

// インクルード
#include "StageObject.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/GameObject/Camera.h"

Stage::Stage(GameObject* _parent)
	:GameObject(_parent,"Stage"),objects_()
{
}

void Stage::Initialize()
{
}

void Stage::Update()
{
	static XMFLOAT3 camPos = { 1.4f,5.f,3.8f };
	static XMFLOAT3 camTgt = { -8.4f,-3.2f,25.f };
#ifdef _DEBUG
	ImGui::DragFloat3("Camera Position", &camPos.x, 0.1f);
	ImGui::DragFloat3("Camera Target", &camTgt.x, 0.1f);
#endif // _DEBUG

	// カメラの位置を設定
	Camera::SetPosition(camPos);
	Camera::SetTarget(camTgt);
}

void Stage::Draw()
{
}

void Stage::Release()
{
}

void Stage::Save(json& _saveObj)
{
	// オブジェクト群を保存
	for (auto obj : objects_)obj->Save(_saveObj[obj->GetObjectName()]);
}

void Stage::Load(json& _loadObj)
{
	// ステージオブジェクトをすべて削除
	DeleteAllStageObject();

	for (auto it = _loadObj.begin(); it != _loadObj.end();++it) {
		
		// オブジェクトのインスタンスを生成
		StageObject* obj = CreateStageObject(it.key(), it.value()["modelFilePath_"], this);
		
		// オブジェクト情報を読込
		obj->Load(it.value());

		// オブジェクトをリストに追加
		AddStageObject(obj);
	}
}

void Stage::DrawData()
{
	// オブジェクトを描画
	for (auto obj : objects_)obj->DrawData();
}

void Stage::AddStageObject(StageObject* _obj)
{
	// リストに追加
	if (_obj != nullptr)objects_.push_back(_obj);
}

void Stage::DeleteStageObject(StageObject* _obj)
{
	// オブジェクトを削除する
	_obj->KillMe();

	// オブジェクトのイテレータを取得する
	auto it = std::find(objects_.begin(), objects_.end(), _obj);

	// イテレータが見つかった場合、ベクターから削除する
	if (it != objects_.end()) objects_.erase(it);
}

void Stage::DeleteAllStageObject()
{
	// リスト内にある要素をすべて削除
	for (auto obj : objects_) obj->KillMe();
	objects_.clear();
}
