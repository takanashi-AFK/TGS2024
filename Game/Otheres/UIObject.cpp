#include "UIObject.h"

#include"../../Engine/ResourceManager/Image.h"
#include "../../Engine/Global.h"

UIObject::UIObject(string _name, GameObject* _parent)
	: GameObject(_parent,_name)
{
}

void UIObject::Initialize()
{
}

void UIObject::Update()
{
}

void UIObject::Draw()
{
}

void UIObject::Release()
{
}

void UIObject::Save(json& _saveUIobj)
{
	//自身の変形行列を保存
	_saveUIobj["UIposition"] = { REFERENCE_XMFLOAT3(transform_.position_)};
	_saveUIobj["UIrotate_"] = { REFERENCE_XMFLOAT3(transform_.rotate_) };
	_saveUIobj["UIscale"] = { REFERENCE_XMFLOAT3(transform_.scale_) };
}

void UIObject::Load(json& _loadUIobj)
{
	//変形行列を読み込み
	transform_.position_ = { _loadUIobj["UIposition_"][0].get<float>(),_loadUIobj["UIposition_"][1].get<float>(),_loadUIobj["UIposition_"][2].get<float>() };
	transform_.rotate_ = { _loadUIobj["UIrotate_"][0].get<float>(),_loadUIobj["UIrotate_"][1].get<float>(),_loadUIobj["UIrotate_"][2].get<float>() };
	transform_.scale_ = { _loadUIobj["UIscale_"][0].get<float>(),_loadUIobj["UIscale_"][1].get<float>(),_loadUIobj["UIscale_"][2].get<float>() };
}
