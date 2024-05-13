#include "Component_OtiBehavior.h"

#include "../../StageObject.h"
#include "../DetectorComponents/Component_CircleRangeDetector.h"

Component_OtiBehavior::Component_OtiBehavior(StageObject* _holder)
	: Component(_holder, "Component_OtiBehavior", OtiBehavior)
{
}

void Component_OtiBehavior::Initialize()
{
	// 子コンポーネントの追加
	AddChildComponent(CreateComponent(CircleRangeDetector, holder_));
}

void Component_OtiBehavior::Update()
{
	// 範囲内に入っているかどうかを判定
	if (((Component_CircleRangeDetector*)GetChildComponent(CircleRangeDetector))->IsContains())
	{
		// 範囲内に入っている場合の処理
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
