#include "Component_Teleporter.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../../../../Engine/Global.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../Stage.h"

namespace {
    EFFEKSEERLIB::EFKTransform t;/*★★★*/
}

Component_Teleporter::Component_Teleporter(string _name, StageObject* _holder, Component* _parent) :
    Component(_holder, _name, Teleporter, _parent), teleportState_(IDLE), scaleValue_(0.01f), lowerLimit_(0.0f), default_(1.0f)
{
}

void Component_Teleporter::Initialize()
{
    // 必要なコンポーネントを追加
    if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
    // effekseer: :Effectの読み込み
    EFFEKSEERLIB::gEfk->AddEffect("sword", "Effects/Salamander12.efk");/*★★★*/
}

void Component_Teleporter::Update()
{

    if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
    if (target_ == nullptr)return;

    switch (teleportState_)
    {
    case IDLE:
        Idle();
        break;
    case TELEPORTING:
        Teleporting();
        break;
    case TELEPORTSTART:
        TeleportStart();
        break;
    }

   

}

void Component_Teleporter::Release()
{
    // 解放処理
}

void Component_Teleporter::Save(json& _saveObj)
{
    // テレポーターの状態を保存
    _saveObj["teleportPosition_"] = { REFERENCE_XMFLOAT3(teleportPosition_) };
    if (target_ != nullptr)_saveObj["target_"] = target_->GetObjectName();
}

void Component_Teleporter::Load(json& _loadObj)
{
    // テレポーターの状態を読み込み
    if (_loadObj.contains("teleportPosition_"))
        teleportPosition_ = { _loadObj["teleportPosition_"][0].get<float>(),_loadObj["teleportPosition_"][1].get<float>(), _loadObj["teleportPosition_"][2].get<float>() };


}

void Component_Teleporter::DrawData()
{
    if (ImGui::TreeNode("Teleporter Component"))
    {
        // ImGui でテレポート先を設定するための入力フィールド
        ImGui::InputFloat3("Teleport Position", &teleportPosition_.x);

        ImGui::TreePop();
    }
    //対象の選択
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
    else {
        target_ = (StageObject*)holder_->FindObject(objNames[select]);

        auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
        detector->SetTarget(target_);
    }
}

void Component_Teleporter::Idle()
{
    auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
    if (detector == nullptr)return;

    if (detector->IsContains())
    {
        teleportState_ = TELEPORTING;
    }
}

void Component_Teleporter::Teleporting()
{   
    XMFLOAT3 targetScale_ = target_->GetScale();
    if (targetScale_.x <= lowerLimit_ )
        teleportState_ = TELEPORTSTART;    
    else {
        // スケールを減少させる
        targetScale_.x -= scaleValue_;
        targetScale_.y -= scaleValue_;
        targetScale_.z -= scaleValue_;

        // effekseer: :Effectの再生情報の設定

        DirectX::XMStoreFloat4x4(&(t.matrix), holder_->GetWorldMatrix());/*★★★*/
        t.isLoop = false;/*★★★*/
        t.maxFrame = 60;/*★★★*/
        t.speed = 1.0f;/*★★★*/


        // effekseer: :Effectの再生
        mt = EFFEKSEERLIB::gEfk->Play("sword", t);/*★★★*/
    }
    target_->SetScale(targetScale_);
    
}

void Component_Teleporter::TeleportStart()
{
    target_->SetPosition(teleportPosition_);
    XMFLOAT3 targetScale_ = target_->GetScale();
    if (targetScale_.x >= default_)
        teleportState_ = IDLE;
    else {
        targetScale_.x += scaleValue_;
        targetScale_.y += scaleValue_;
        targetScale_.z += scaleValue_;
    }
    target_->SetScale(targetScale_);
}

