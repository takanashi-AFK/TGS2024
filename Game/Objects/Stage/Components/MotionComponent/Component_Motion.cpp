#include "Component_Motion.h"

Component_Motion::Component_Motion(string _name, StageObject* _holder, ComponentType _type, Component* _parent)
 :Component(_holder, _name, _type, _parent)
{
}

void Component_Motion::Initialize()
{
}

void Component_Motion::Update()
{


}

void Component_Motion::Release()
{
}

void Component_Motion::DrawData()
{
}

MotionData::MotionData(string _filePath, int startFrame, int endFrame, int speed)
{
    // ファイルパスを設定
    filePath = _filePath;

    // モデルハンドルを設定
    modelHandle = Model::Load(filePath);

    // 開始フレームを設定
    startFrame = startFrame;

    // 終了フレームを設定
    endFrame = endFrame;

    // アニメーションスピードを設定
    speed = speed;
}
