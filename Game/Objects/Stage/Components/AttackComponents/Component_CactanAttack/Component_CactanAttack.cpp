#include "Component_CactanAttack.h"

// インクルード
#include "../../../../../../Engine/ImGui/imgui.h"
#include "../../../Bullet.h"
#include "../../../Stage.h"

Component_CactanAttack::Component_CactanAttack(string _name, StageObject* _holder, Component* _parent):
	Component_Attack(_holder, _name, CactanAttack,_parent),
	bulletSpeed_(0.5f),
	target_{}
{
}

void Component_CactanAttack::Initialize()
{
}

void Component_CactanAttack::Update()
{	
}

void Component_CactanAttack::Release()
{
}

void Component_CactanAttack::Save(json& _saveObj)
{
	// 保存
	_saveObj["bulletSpeed_"] = bulletSpeed_;
	_saveObj["target_"] = target_->GetObjectName();
}

void Component_CactanAttack::Load(json& _loadObj)
{
	// 読込
	if (_loadObj.contains("bulletSpeed_"))bulletSpeed_ = _loadObj["bulletSpeed_"];
	if (_loadObj.contains("target_"))target_ = (StageObject*)holder_->FindObject(_loadObj["target_"]);
}

void Component_CactanAttack::DrawData()
{
	ImGui::DragFloat("Speed", &bulletSpeed_, 0.1f, 0, 2.f);

	//ターゲット指定
	SetTarget();
	if (target_ == nullptr)return;

	//ターゲットの位置と保持者の位置を取得し、ベクトル化
	XMFLOAT3 t = target_->GetPosition();
	XMFLOAT3 h = holder_->GetPosition();
	XMVECTOR dir = XMLoadFloat3(&t) - XMLoadFloat3(&h);

	//ベクトルを正規化
	dir = XMVector3Normalize(dir);

	if (ImGui::Button("Attack")) {
		//弾を生成
		Bullet* pBullet = Instantiate<Bullet>(holder_->GetParent());

		//弾の方向とスピード、初期地点を設定
		pBullet->SetDirection(dir);
		pBullet->SetSpeed(bulletSpeed_);
		pBullet->SetPosition(holder_->GetPosition());

		//発射
		pBullet->Execute();
	}
}

void Component_CactanAttack::Attack()
{

}

void Component_CactanAttack::SetTarget()
{
	vector<string> objNames;
	objNames.push_back("null");

	//StageObjectの名前を取得
	for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects()) {

		//自分自身以外のオブジェクト名があった場合、リストに追加
		if(obj->GetObjectName() != holder_->GetObjectName())
		objNames.push_back(obj->GetObjectName());
	}
	static int select = 0;
	if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
		for (int i = 0; i < objNames.size(); i++) {
			bool is_selected = (select == i);
			if (ImGui::Selectable(objNames[i].c_str(), is_selected))select = i;
			if (is_selected)ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	if (select == 0)target_ = nullptr;
	else target_ = (StageObject*)holder_->FindObject(objNames[select]);

}
