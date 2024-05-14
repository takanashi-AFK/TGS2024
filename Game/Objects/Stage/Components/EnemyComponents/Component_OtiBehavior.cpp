#include "Component_OtiBehavior.h"

#include "../../StageObject.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"
#include "../DetectorComponents/Component_FanRangeDetector.h"
#include "../RotationComponents/Component_RotationY.h"
#include "../TimerComponent/Component_Timer.h"

Component_OtiBehavior::Component_OtiBehavior(StageObject* _holder)
	: Component(_holder, "Component_OtiBehavior", OtiBehavior)
{
}

void Component_OtiBehavior::Initialize()
{
	// 子コンポーネントの追加
	if (FindChildComponent(CircleRangeDetector) == false)AddChildComponent(CreateComponent(CircleRangeDetector, holder_));
	if (FindChildComponent(FanRangeDetector) == false)AddChildComponent(CreateComponent(FanRangeDetector, holder_));
	if (FindChildComponent(RotationY) == false)AddChildComponent(CreateComponent(RotationY, holder_));
	if (FindChildComponent(Timer) == false)AddChildComponent(CreateComponent(Timer, holder_));
}

void Component_OtiBehavior::Update()
{
	// 円形範囲内に入っているかどうかを判定
	if (((Component_CircleRangeDetector*)GetChildComponent(CircleRangeDetector))->IsContains()){

		// タイマーを開始
		((Component_Timer*)GetChildComponent(Timer))->Reset();
		((Component_Timer*)GetChildComponent(Timer))->Start();

		// 回転速度を設定
		((Component_RotationY*)GetChildComponent(RotationY))->SetRotationSpeed(5.f);
	}
	else{
		// タイマーが５秒を観測したら
		if (((Component_Timer*)GetChildComponent(Timer))->IsOnTime(5)) {
			
			// タイマーを停止
			((Component_Timer*)GetChildComponent(Timer))->Stop();

			// 回転速度を設定
			((Component_RotationY*)GetChildComponent(RotationY))->SetRotationSpeed(0.f);
		}		
	}
}

void Component_OtiBehavior::Release()
{
}

void Component_OtiBehavior::Save(json& _saveObj)
{
}

void Component_OtiBehavior::Load(json& _loadObj)
{
}

void Component_OtiBehavior::DrawData()
{
}
