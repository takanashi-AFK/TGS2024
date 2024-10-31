#pragma once
#include "../../../Engine/DirectX/EasingInformation.h"
#include <DirectXMath.h>
#include "../../../Engine/DirectX/Easing.h"

struct EasingInformation_forUI :
    public EasingInformation
{
    virtual void Load(json& file) override;
    virtual void Save(json& file)override;

    void Update();
    DirectX::XMFLOAT3 GetValue(Easing::TYPE type);

    DirectX::XMFLOAT3 pos0_;
    DirectX::XMFLOAT3 pos1_;
};

