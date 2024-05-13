#include "Component_Timer.h"
#include "../../../../../Engine/ImGui/imgui.h"
namespace {
	const int FPS = 60;
}

Component_Timer::Component_Timer(StageObject* _holder)
	:Component(_holder, "Component_Timer", Timer)
	, time_(0), nowTime_(0), isEnd_(false), countNow_(false), isInfinity_(true)
{
}

void Component_Timer::Initialize()
{
}

void Component_Timer::Update()
{
	if (!countNow_) return;
	nowTime_++;
	if (nowTime_ >= time_ && !isInfinity_) Stop();
}

void Component_Timer::Release()
{
}

void Component_Timer::Save(json& _saveObj)
{
	_saveObj["time_"] = time_;
	_saveObj["nowTime_"] = nowTime_;
	_saveObj["isEnd_"] = isEnd_;
	_saveObj["countNow_"] = countNow_;
}

void Component_Timer::Load(json& _loadObj)
{
	if (_loadObj.find("time_") != _loadObj.end()) 	time_ = _loadObj["time_"];
	if (_loadObj.find("nowTime_") != _loadObj.end()) 	nowTime_ = _loadObj["nowTime_"];
	if (_loadObj.find("isEnd_") != _loadObj.end())   isEnd_ = _loadObj["isEnd_"];
	if (_loadObj.find("countNow_") != _loadObj.end())   countNow_ = _loadObj["countNow_"];
}

void Component_Timer::DrawData()
{
	ImGui::Text("%f", nowTime_/FPS);
	//ImGui::DragFloat("Time", &time_, 1.f);
	if (ImGui::Button("Set")){
		SetTime(10);
	}
	if (ImGui::Button("Start"))
	{
		Start();
	}
	if (ImGui::Button("Stop"))
	{
		Stop();
	}
	if (ImGui::Button("Reset"))
	{
		Reset();
	}

}

void Component_Timer::Start()
{
	countNow_ = true;
}

void Component_Timer::Stop()
{
	countNow_ = false;
	isEnd_ = true;
}

float Component_Timer::GetNowTime()
{
	return time_;
}

<<<<<<< HEAD
bool Component_Timer::GetIsEnd()
=======
bool Component_Timer::GetEnd()
>>>>>>> f70783316d3c90d38158e45362162afe10d6ae91
{
	return isEnd_;
}

void Component_Timer::SetTime(int _time)
{
	time_ = _time * FPS;
	isInfinity_ = false;
}

void Component_Timer::Reset()
{
	nowTime_ = 0;
	isEnd_ = false;
}

bool Component_Timer::IsOnTime(float _time)
{
	if (nowTime_ == _time);
	//âΩÇ…ëŒÇµÇƒí ímÇÇ∑ÇÈÇÃÅH
}

float Component_Timer::IsIntervalTime(float _time)
{
	return 0.0f;
}
