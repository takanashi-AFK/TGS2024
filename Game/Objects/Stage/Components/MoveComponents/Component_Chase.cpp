#include "Component_Chase.h"
#include "../../StageObject.h"
#include "../../Stage.h"
#include "../../../../../Engine/ImGui/imgui.h"

namespace {
	const float LIMIT_DISTANCE = 0.5f; // この距離以下になったら追従をやめる
}

Component_Chase::Component_Chase(StageObject* _holder)
	:Component(_holder,"Component_Chase",Chase), speed_(0.0f),target_(nullptr)
{
}

void Component_Chase::Initialize()
{
	speed_ = 0.3f;
}

void Component_Chase::Update()
{
	if (target_ == nullptr || isActive_ == false)return;

	//対象と保有者のポジションを取得
	XMFLOAT3 targetPos = target_->GetPosition();
	XMFLOAT3 holderPos = holder_->GetPosition();

	// 追従する方向を計算
	XMVECTOR direction = XMVectorSetY(CalcDirection(holderPos, targetPos),0);

	// ホルダーの向きを計算
	float rotateAngle = CalcRotateAngle(direction);

	// 距離を計算
	float distance = CalcDistance(holderPos, targetPos);

	if (distance > LIMIT_DISTANCE) {
		
		//向きをを適応
		holder_->SetRotateY(rotateAngle);

		//移動
		Move(direction);
	}
	else
	{
		rotateAngle = 0;
	}
}

void Component_Chase::Release()
{
}

void Component_Chase::Save(json& _saveobj)
{
	_saveobj["speed_"] = speed_;
	_saveobj["isActive_"] = isActive_;
	if(target_ != nullptr)_saveobj["target_"] = target_->GetObjectName();
}

void Component_Chase::Load(json& _loadobj)
{
	if(_loadobj.contains("speed_"))speed_ = _loadobj["speed_"];
	if(_loadobj.contains("isActive_"))isActive_ = _loadobj["isActive_"];
	if(_loadobj.contains("target_"))target_ = (StageObject*)holder_->FindObject(_loadobj["target_"]);
}

void Component_Chase::DrawData()
{

	// 追従の有効無効
	ImGui::Checkbox("isActive", &isActive_);
	
	// 速度の設定
	ImGui::DragFloat("speed", &speed_, 0.01f, 0.0f, 10.0f);

	// ターゲットの選択
	{
		vector<string> objNames;
		objNames.push_back("null");

		for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects())objNames.push_back(obj->GetObjectName());

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
}

XMVECTOR Component_Chase::CalcDirection(XMFLOAT3 _holderPos, XMFLOAT3 _targetPos)
{
	return XMVector3Normalize(XMLoadFloat3(&_targetPos) - XMLoadFloat3(&_holderPos));
}

void Component_Chase::Move(XMVECTOR _direction)
{
	XMFLOAT3 holderPosition = holder_->GetPosition();
	XMStoreFloat3(&holderPosition, XMLoadFloat3(&holderPosition) + (_direction * speed_));
	holder_->SetPosition(holderPosition);
}

float Component_Chase::CalcDistance(XMFLOAT3 _holderPos, XMFLOAT3 _targetPos)
{
	return XMVectorGetX(XMVector3Length(XMLoadFloat3(&_targetPos) - XMLoadFloat3(&_holderPos)));
}

float Component_Chase::CalcRotateAngle(XMVECTOR _direction)
{
	// 回転角度を計算
	return atan2(XMVectorGetX(-_direction), XMVectorGetZ(-_direction));
}
