#include "Component_Timer.h"
#include "../../../../../Engine/ImGui/imgui.h"
namespace {
	const int FPS = 60;
}

Component_Timer::Component_Timer(StageObject* _holder)
	:Component(_holder, "Component_Timer", Timer)
	, maxTime_(0), nowTime_(0),tempMax_(0), isEnd_(false), isCountNow_(false), isInfinity_(true)
{
}

void Component_Timer::Initialize()
{
}

void Component_Timer::Update()
{
	if (nowTime_ >= maxTime_ && !isInfinity_) Stop();
	// カウント中でない場合,カウントを進める
	if (!isCountNow_) return;
	nowTime_++;
}

void Component_Timer::Release()
{
}

void Component_Timer::Save(json& _saveObj)
{
	_saveObj["maxTime_"] = maxTime_;
	_saveObj["nowTime_"] = nowTime_;
}

void Component_Timer::Load(json& _loadObj)
{
	if (_loadObj.find("maxTime_") != _loadObj.end()) 	maxTime_ = _loadObj["maxTime_"];
	if (_loadObj.find("nowTime_") != _loadObj.end()) 	nowTime_ = _loadObj["nowTime_"];
}

void Component_Timer::DrawData()
{
	//現在の時間を表示
	ImGui::Text("%f", GetNowTime());

	//最大時間を設定
	ImGui::DragFloat("Time", &tempMax_, 1.f,0,100);
	if (ImGui::Button("Set"))SetTime(tempMax_);
	ImGui::SameLine();

	//開始
	if (ImGui::Button("Start"))Start();
	ImGui::SameLine();

	//停止
	if (ImGui::Button("Stop"))Stop();
	ImGui::SameLine();

	//リセット
	if (ImGui::Button("Reset"))Reset();

	//終了したか
	ImGui::Text("isEnd_ : %s",isEnd_ ? "true" : "false");
}

void Component_Timer::Start()
{
	//countNow_をtrueにし、タイマーを開始
	isCountNow_ = true;
	isEnd_ = false;
}

void Component_Timer::Stop()
{
	//countNow_をfalseにし、タイマーを停止
	isCountNow_ = false;
	isEnd_ = true;
}

float Component_Timer::GetNowTime()
{
	return nowTime_ / FPS;
}

bool Component_Timer::GetIsEnd()
{
	return isEnd_;
}

void Component_Timer::SetTime(int _time)
{
	maxTime_ = _time * FPS;
	isInfinity_ = false;
}

void Component_Timer::Reset()
{
	isCountNow_ = false;
	nowTime_ = 0;
	isEnd_ = false;
}

bool Component_Timer::IsOnTime(float _time)
{
	//今の時間が指定された秒の時trueを返す
	return nowTime_ >= _time * FPS;
}

bool Component_Timer::IsIntervalTime(float _time)
{
	//今の時間が指定された秒の倍数の時trueを返す
	return static_cast<int>(nowTime_) % (static_cast<int>(_time) * FPS) == 0;
}
