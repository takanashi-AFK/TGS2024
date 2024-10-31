#include "EasingInformation_forUI.h"

void EasingInformation_forUI::Load(json& file)
{
    addRatio_ = {};
    if (file.contains("addRatio")) addRatio_= file["addRatio"].get<float>();

    pos0_ = {};
    if (file.contains("Position_First")) pos0_ = { file["Position_First"][0].get<float>(),file["Position_First"][1].get<float>() ,file["Position_First"][2].get<float>() };

    pos1_ = {};
    if (file.contains("Position_Second")) pos0_ = { file["Position_Second"][0].get<float>(),file["Position_Second"][1].get<float>() ,file["Position_Second"][2].get<float>() };
}

void EasingInformation_forUI::Save(json& file)
{
    file["addRatio"] = addRatio_;
    file["Position_First"] = { pos0_.x,pos0_.y,pos0_.z };
    file["Position_Second"] = { pos1_.x,pos1_.y,pos1_.z };
}

void EasingInformation_forUI::Update()
{
    pile_ += addRatio_;
}

DirectX::XMFLOAT3 EasingInformation_forUI::GetValue(Easing::TYPE type)
{
    return DirectX::XMFLOAT3
    (
        Easing::GetValue(pos0_.x,pos1_.x,pile_,type),
        Easing::GetValue(pos0_.y, pos1_.y, pile_, type),
        Easing::GetValue(pos0_.z, pos1_.z, pile_, type)
    );
}
