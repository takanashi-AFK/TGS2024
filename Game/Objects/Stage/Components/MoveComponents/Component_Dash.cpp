#include "Component_Dash.h"
#include "Component_WASDInputMove.h"
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"


Component_Dash::Component_Dash(string _name, StageObject* _holder, Component* _parent)
	: Component(_holder, _name, Dash, _parent), frontVec_(XMVectorZero()), moveDistance_(0.0f), moveSpeed_(0.0f), isActive_(false)
{
}

void Component_Dash::Initialize()
{
	if (FindChildComponent("InputMove") == false)AddChildComponent(CreateComponent("InputMove", WASDInputMove, holder_, this));
}

void Component_Dash::Update()
{
    if (!isActive_) return;
    auto move = dynamic_cast<Component_WASDInputMove*>(GetChildComponent("InputMove"));
    if (move == nullptr) 
        return;

    frontVec_ = move->GetMoveDirction();
    if (XMVector3Equal(frontVec_, XMVectorZero())) return;

    XMVECTOR moveVec = XMVector3Normalize(frontVec_) * moveSpeed_;

    XMFLOAT3 movePos;
    XMFLOAT3 holderPos = holder_->GetPosition();

    XMStoreFloat3(&movePos, moveVec);

    holderPos.x += movePos.x;
    holderPos.y += movePos.y;
    holderPos.z += movePos.z;
    holder_->SetPosition(holderPos.x, holderPos.y, holderPos.z);

    // ˆÚ“®‚µ‚½‹——£‚ðŒvŽZ‚µA‘ˆÚ“®‹——£‚É‰ÁŽZ
    float movedDistance = sqrt(movePos.x * movePos.x + movePos.y * movePos.y + movePos.z * movePos.z);
    totalMovedDistance_ += movedDistance;

    // ‘ˆÚ“®‹——£‚ªÅ‘å‹——£‚ð’´‚¦‚½‚çisActive_‚ðfalse‚É‚·‚é
    if (totalMovedDistance_ >= moveDistance_) {
        isActive_ = false;
    }
}

void Component_Dash::Release()
{
}

void Component_Dash::Save(json& _saveObj)
{
}

void Component_Dash::Load(json& _loadObj)
{
}

void Component_Dash::DrawData()
{
	ImGui::Text("Dash");
	ImGui::DragFloat("moveSpeed_", &moveSpeed_);
    ImGui::DragFloat("moveDistance_", &moveDistance_);
	if (ImGui::Button("Execute"))Execute();
}
