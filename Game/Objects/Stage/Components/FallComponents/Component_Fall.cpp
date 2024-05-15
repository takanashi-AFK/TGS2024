#include "Component_Fall.h"

//インクルード
#include "../../StageObject.h"

Component_Fall::Component_Fall(StageObject* _holder)
	:Component(_holder, "Component_Fall", Fall), fallSpeed_(0)
{
}

void Component_Fall::Initialize()
{
}

void Component_Fall::Update()
{

}

void Component_Fall::Release()
{
}

void Component_Fall::Save(json& _saveObj)
{
}

void Component_Fall::Load(json& _loadObj)
{
}

void Component_Fall::DrawData()
{
}
