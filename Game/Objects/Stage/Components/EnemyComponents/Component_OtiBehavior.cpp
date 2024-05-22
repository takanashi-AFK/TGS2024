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
	if (FindChildComponent(Timer) == false)AddChildComponent(CreateComponent(Timer, holder_));
	if (FindChildComponent(Fall) == false)AddChildComponent(CreateComponent(Fall, holder_));
	if (FindChildComponent(Chase) == false)AddChildComponent(CreateComponent(Chase, holder_));

}

void Component_OtiBehavior::Update()
{
	if (((Component_CircleRangeDetector*)GetChildComponent(CircleRangeDetector))->IsContains()) {

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
