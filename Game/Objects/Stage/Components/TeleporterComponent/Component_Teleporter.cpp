#include "Component_Teleporter.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../../../../Engine/Global.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../Stage.h"
Component_Teleporter::Component_Teleporter(string _name, StageObject* _holder, Component* _parent) :
    Component(_holder, _name, Teleporter, _parent), teleportState_(TELEPORTING)
{
}

void Component_Teleporter::Initialize()
{
    // �K�v�ȃR���|�[�l���g��ǉ�
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
        TeleportingState();
        //// �e���|�[�g�Ώۂ��w�肳�ꂽ���W�Ɉړ�
        //target_->SetPosition(teleportPosition_);
    }

}

void Component_Teleporter::Release()
{
    // �������
}

void Component_Teleporter::Save(json& _saveObj)
{
    // �e���|�[�^�[�̏�Ԃ�ۑ�
    _saveObj["teleportPosition_"] = { REFERENCE_XMFLOAT3(teleportPosition_) };
    if (target_ != nullptr)_saveObj["target_"] = target_->GetObjectName();
}

void Component_Teleporter::Load(json& _loadObj)
{
    // �e���|�[�^�[�̏�Ԃ�ǂݍ���
    if (_loadObj.contains("teleportPosition_"))
        teleportPosition_ = { _loadObj["teleportPosition_"][0].get<float>(),_loadObj["teleportPosition_"][1].get<float>(), _loadObj["teleportPosition_"][2].get<float>() };


}

void Component_Teleporter::DrawData()
{
    if (ImGui::TreeNode("Teleporter Component"))
    {
        // ImGui �Ńe���|�[�g���ݒ肷�邽�߂̓��̓t�B�[���h
        ImGui::InputFloat3("Teleport Position", &teleportPosition_.x);

        ImGui::TreePop();
    }
    //�Ώۂ̑I��
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

void Component_Teleporter::IdleState(Component_CircleRangeDetector* detector)
{
    if (detector->IsContains())
    {
        // �R���C�_�[��PlayerBehavior�������Ă��邩���m�F
        // �@�\���A�N�e�B�u�ɂ���
       
    }
}

void Component_Teleporter::TeleportingState()
{
    scaleValue_ -= 0.01f;

    if (scaleValue_ <= 0.0f)
    {
        scaleValue_ = 0.0f;
        target_->SetPosition(teleportPosition_);
        //teleportState_ = Effect;
       
    }
    target_->SetScale(XMFLOAT3(scaleValue_, scaleValue_, scaleValue_));

}

void Component_Teleporter::EffectState()
{
    // �G�t�F�N�g�����i�K�v�ɉ����Ēǉ��j
}
