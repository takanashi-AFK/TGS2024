#include "Component_ShockWave.h"
#include "../HealthManagerComponents/Component_HealthManager.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../../StageObject.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Stage.h"
Component_ShockWave::Component_ShockWave(string _name, StageObject* _holder, Component* _parent) :
	Component_Attack(_holder, _name,ShockWave, _parent)
{
}

void Component_ShockWave::Initialize()
{
	if (!FindChildComponent("CircleRangeDetector")) AddChildComponent(CreateComponent("CircleRangeDetector", CircleRangeDetector, holder_, this));
	shockwaveRange_ = 5.0f;
	shockwaveDamage_ = 5.0f;
}

void Component_ShockWave::Update()
{
	if (target_ == nullptr) target_ = (StageObject*)holder_->FindObject(targetName_);
	if (target_ == nullptr) return;

	auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
	if (detector == nullptr) return;

	//ショックウェーブの範囲を設定
	detector->SetRadius(shockwaveRange_);
	//プレイヤーが範囲内いたら
	if (detector->IsContains()) {
		//プレイヤーのHPを減らす
		auto hm = ((StageObject*)target_)->FindComponent("HealthManager");
		if (hm == nullptr)return;
		((Component_HealthManager*)hm)->TakeDamage(shockwaveDamage_);
	}
}

void Component_ShockWave::Release()
{
}

void Component_ShockWave::DrawData()
{
	ImGui::Text("ShockWaveRange:%f", shockwaveRange_);
	ImGui::Text("ShockWaveDamage:%f", shockwaveDamage_);
	ImGui::Text("TargetName:%s", targetName_.c_str());

	 // 対象の選択
    vector<string> objNames;
    objNames.push_back("null");

    for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects()) objNames.push_back(obj->GetObjectName());

    static int select = 0;
    if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
        for (int i = 0; i < objNames.size(); i++) {
            bool is_selected = (select == i);
            if (ImGui::Selectable(objNames[i].c_str(), is_selected)) select = i;
            if (is_selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (select == 0) target_ = nullptr;
    else {
        target_ = (StageObject*)holder_->FindObject(objNames[select]);

        auto detector = dynamic_cast<Component_CircleRangeDetector*>(GetChildComponent("CircleRangeDetector"));
        detector->SetTarget(target_);
    }
}

void Component_ShockWave::OnCollision(GameObject* _target)
{
}

void Component_ShockWave::Save(json& _saveObj)
{
}

void Component_ShockWave::Load(json& _loadObj)
{
}
