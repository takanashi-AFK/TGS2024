#include "Component_HealthGauge.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../StageObject.h"


Component_HealthGauge::Component_HealthGauge(string _name, StageObject* _holder, Component* _parent)
	:Component_Gauge(_holder, _name, HealthGauge,_parent), prev_(now_), shaderChangeTime_(60),isLock_(false)
{

}

void Component_HealthGauge::Initialize()
{
}

void Component_HealthGauge::Update()
{
	static int prevShaderType = (int)holder_->GetShader();
	// ダメージをくらったらシェーダーを変更
	if (prev_ > now_) {
		holder_->SetShader(Direct3D::SHADER_DAMAGE);
		shaderChangeTime_ = 30; // シェーダー変更時間をリセット
	}
	// 一定時間が経過したらシェーダーを元に戻す
	if (shaderChangeTime_ > 0) {
		shaderChangeTime_--;
		if (shaderChangeTime_ == 0) {
			holder_->SetShader((Direct3D::SHADER_TYPE)prevShaderType);
		}
	}

	// 各値のリセット
	prev_ = now_;
	isTakeDamage_ = false;

	/* DEBUG:*/{
		/*ImGui::Text("%s -> healthData", holder_->GetObjectName().c_str());
		ImGui::Text("now : %f", now_);
		ImGui::Text("prev : %f", prev_);
		ImGui::Text("max : %f", max_);
		ImGui::Text("shaderChangeTime : %d", shaderChangeTime_);
		ImGui::Text("isLock : %d", isLock_);
		ImGui::Separator();*/
	}
}

void Component_HealthGauge::Release()
{
}

void Component_HealthGauge::TakeDamage(float _damageValue)
{
	// ダメージを受けたフラグを立てる
	isTakeDamage_ = true;

	if(isLock_)return;

	// 前回の体力を保存
	prev_ = now_;

	//HPを減らす
	now_ -= _damageValue;

	//HPが0以下にならないようにする
	if (now_ < 0)now_ = 0;
}

void Component_HealthGauge::Heal(float _healValue)
{
	if (isLock_)return;

	//HPが最大値を超えないようにする
	if (now_ + _healValue <= max_)now_ += _healValue;
}