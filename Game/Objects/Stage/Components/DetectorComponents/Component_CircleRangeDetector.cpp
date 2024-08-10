#include "Component_CircleRangeDetector.h"

// インクルード
#include "../../../../../Engine/Global.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Stage.h"
#include "../../StageObject.h"

Component_CircleRangeDetector::Component_CircleRangeDetector(string _name, StageObject* _holder, Component* _parent)
    : Component(_holder, _name, CircleRangeDetector,_parent), radius_(0.0f), isContains_(false), target_(nullptr)
{
}

void Component_CircleRangeDetector::Initialize()
{
}

void Component_CircleRangeDetector::Update()
{

	if (target_ == nullptr)target_ = (StageObject*)holder_->FindObject(targetName_);
	// 対象が存在しない場合は処理を行わない
	if (target_ == nullptr)return;

	// 円形範囲判定
	// 範囲内に入っているかどうかを判定
	isContains_ = IsContains();
}

void Component_CircleRangeDetector::Release()
{
}

void Component_CircleRangeDetector::Save(json& _saveObj)
{
	// 自身の情報を保存
	_saveObj["radius_"] = radius_;
	if (target_ != nullptr)_saveObj["target_"] = target_->GetObjectName();
}

void Component_CircleRangeDetector::Load(json& _loadObj)
{
	// 自身の情報を読み込み
	if(_loadObj.find("radius_") != _loadObj.end())radius_ = _loadObj["radius_"];
	if (_loadObj.find("isContains_") != _loadObj.end())isContains_ = _loadObj["isContains_"];
	if (_loadObj.contains("target_"))targetName_ = _loadObj["target_"];
}

void Component_CircleRangeDetector::DrawData()
{
#ifdef _DEBUG

    // ImGuiでデータを描画
    ImGui::Text("isContains_ : %s", isContains_ ? "true" : "false");

    // 半径の入力
    ImGui::DragFloat("radius_", &radius_);

    ImGui::Separator();

    //対象の選択
    vector<string> objNames;
    objNames.push_back("null");

    for (auto obj : ((Stage*)holder_->GetParent())->GetStageObjects()) {
        objNames.push_back(obj->GetObjectName());
    }

    static int select = 0;

    // target_の名前に基づいて初期値を設定する
    if (target_ != nullptr) {
        string targetName = target_->GetObjectName();
        auto it = find(objNames.begin(), objNames.end(), targetName);
        if (it != objNames.end()) {
            select = distance(objNames.begin(), it);
        }
    }

    if (ImGui::BeginCombo("target_", objNames[select].c_str())) {
        for (int i = 0; i < objNames.size(); i++) {
            bool is_selected = (select == i);
            if (ImGui::Selectable(objNames[i].c_str(), is_selected)) select = i;
            if (is_selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (select == 0) target_ = nullptr;
    else target_ = (StageObject*)holder_->FindObject(objNames[select]);

    if (target_ != nullptr) {
        XMFLOAT3 pos = target_->GetPosition();
        ImGui::Text("position_ = %f,%f,%f", REFERENCE_XMFLOAT3(pos));
    }

#endif // _DEBUG
}

bool Component_CircleRangeDetector::IsContains()
{
	// 対象が存在しない場合は処理を行わない
	if (target_ == nullptr)return false;

	// 範囲内に入っているかどうかを判定
	float a = target_->GetPosition().x - holder_->GetPosition().x;
	float b = target_->GetPosition().z - holder_->GetPosition().z;

	// 2点間の距離が半径以下ならtrue
	return sqrt(a * a + b * b) <= radius_;

}
