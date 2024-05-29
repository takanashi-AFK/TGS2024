#include "Component_CactanAttack.h"
#include "../../../../../../Engine/ImGui/imgui.h"
#include "../../../Stage.h"
Component_CactanAttack::Component_CactanAttack(StageObject* _holder):
	Component_Attack(_holder, "Component_CactanAttack", CactanAttack),
	frame{},
	target_{},
	direction_{},
	speed_(0.5f)
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

void Component_CactanAttack::Save(json& _saveobj)
{
}

void Component_CactanAttack::Load(json& _loadobj)
{

}

void Component_CactanAttack::DrawData()
{
	Attack();
}


void Component_CactanAttack::Attack()
{
	ImGui::DragFloat("Speed", &speed_,0.1f,0,2.f);
	
	//XMFLOAT3 dir;
	//XMStoreFloat3(&dir, direction_);
	//ImGui::DragFloat3("Direction", &dir.x);
	//direction_ = XMLoadFloat3(&dir);
	SetTarget();
	if (target_ == nullptr)return;
	XMFLOAT3 t = target_->GetPosition();
	XMFLOAT3 h = holder_->GetPosition();
	XMVECTOR dir = XMLoadFloat3(&t) - XMLoadFloat3(&h);

	if (ImGui::Button("Attack")) {
		Bullet* pBullet = Instantiate<Bullet>(holder_->GetParent());
		pBullet->SetDirection(dir);
		pBullet->SetSpeed(speed_);
		pBullet->SetPosition(holder_->GetPosition());
		pBullet->Execute();
	}
}

void Component_CactanAttack::SetTarget()
{
	vector<string> objNames;
	objNames.push_back("null");

	for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects()) {
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
