#include "Component_Teleporter.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../../../../Engine/Global.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../Stage.h"
Component_Teleporter::Component_Teleporter(string _name, StageObject* _holder, Component* _parent) :
    Component(_holder, _name, Teleporter, _parent)
{
}

void Component_Teleporter::Initialize()
{
    // 必要なコンポーネントを追加
    if (FindChildComponent("CircleRangeDetector") == false)AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
}

void Component_Teleporter::Update()
{

    if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
    if (target_ == nullptr)return;

    auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
    if (detector == nullptr)return;

    if (detector->IsContains())
    {
        // テレポート対象を指定された座標に移動
        target_->SetPosition(teleportPosition_);
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

void Component_Teleporter::Teleport(GameObject* _target)
{

}