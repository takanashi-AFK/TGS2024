//#include "Component_HealthManager.h"
//
//// インクルード
//#include "../../../../../Engine/ImGui/imgui.h"
//
//Component_HealthGauge::Component_HealthGauge(string _name, StageObject* _holder, Component* _parent)
//	:Component(_holder, _name, HealthManager,_parent),max_(0),hp_(0) 
//{
//
//}
//
//void Component_HealthGauge::Initialize()
//{
//}
//
//void Component_HealthGauge::Update()
//{
//}
//
//void Component_HealthGauge::Release()
//{
//}
//
//void Component_HealthGauge::Save(json& _saveObj)
//{
//	_saveObj["max_"] = max_;
//	_saveObj["hp_"] = hp_;
//}
//
//void Component_HealthGauge::Load(json& _loadObj)
//{
//	if (_loadObj.contains("max_"))max_ = _loadObj["max_"];
//	if (_loadObj.contains("hp_"))hp_ = _loadObj["hp_"];
//}
//
//void Component_HealthGauge::DrawData()
//{
//	ImGui::DragFloat("MaxHP", &max_, 1.0f);
//	ImGui::DragFloat("HP", &hp_, 1.0f, 0.0f, max_);
//
//	if (ImGui::Button("Reset"))Reset();
//}
//
//float Component_HealthGauge::GetHP() const
//{
//	return hp_;
//}
//
//void Component_HealthGauge::SetHP(float _newHP)
//{
//	if(_newHP <= max_)hp_ = _newHP;
//}
//
//float Component_HealthGauge::GetMax() const
//{
//	return max_;
//}
//
//void Component_HealthGauge::SetMax(float _newMax)
//{
//	max_ = _newMax;
//}
//
//void Component_HealthGauge::TakeDamage(float _damageValue)
//{
//	hp_ -= _damageValue;
//	//HPが0以下にならないようにする
//	if (hp_ < 0)hp_ = 0;
//}
//
//void Component_HealthGauge::Heal(float _healValue)
//{
//	//HPが最大値を超えないようにする
//	if (hp_ + _healValue <= max_)hp_ += _healValue;
//}
//
//void Component_HealthGauge::Reset()
//{
//	hp_ = max_;
//}
