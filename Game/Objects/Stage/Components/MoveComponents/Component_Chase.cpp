#include "Component_Chase.h"
#include "../../StageObject.h"
#include "../../Stage.h"
#include "../../../../../Engine/ImGui/imgui.h"

namespace {
	const float LIMIT_DISTANCE = 0.5f;
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
	if (target_ == nullptr)return;

	//‘ÎÛ‚Æ•Û—LŽÒ‚Ìƒ|ƒWƒVƒ‡ƒ“‚ðŽæ“¾
	XMFLOAT3 targetPos = target_->GetPosition();
	XMFLOAT3 holderPos = holder_->GetPosition();

	// ’Ç]‚·‚é•ûŒü‚ðŒvŽZ
	XMVECTOR direction = CalcDirection(holderPos, targetPos);

	// ƒzƒ‹ƒ_[‚ÌŒü‚«‚ðŒvŽZ
	float rotateAngle = CalcRotateAngle(direction);

	// ‹——£‚ðŒvŽZ
	float distance = CalcDistance(holderPos, targetPos);


	if (distance > LIMIT_DISTANCE) {
		//ˆÚ“®Œã‚ÌˆÊ’u‚ð“K‰ž
		holder_->SetRotateY(rotateAngle);
		holder_->SetPosition(holderPos);
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
	_saveobj[" movingdistance_"] = speed_;
	if (target_ != nullptr)_saveobj["targetName"] = target_->GetObjectName();
}

void Component_Chase::Load(json& _loadobj)
{
	if (_loadobj.find("move_") != _loadobj.end()) speed_ = _loadobj[" movingdistance_"];
	if (_loadobj.find("target_") != _loadobj.end())target_ = (StageObject*)holder_->FindObject(_loadobj["target_"]);
}

void Component_Chase::DrawData()
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
	// ‰ñ“]Šp“x‚ðŒvŽZ
	return atan2(XMVectorGetX(-_direction), XMVectorGetZ(-_direction));
}
