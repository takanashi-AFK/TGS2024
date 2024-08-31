#include "CountDown.h"
#include "../../../Engine/ResourceManager/Image.h"

CountDown::CountDown(GameObject* _parent):
	GameObject(_parent,"CountDown")
{
}

void CountDown::Initialize()
{
	for (int i = 0; i < 4; i++) {
		countDownImages_.push_back(Image::Load("Images/CountDown/count_" + std::to_string(i) + ".png"));
	}
}

void CountDown::Update()
{
}

void CountDown::Draw()
{
	static int count = 240;


	if (count >= 0) {
		count--;
		Image::SetTransform(countDownImages_[(int)(count / 60)], transform_);
		Image::Draw(countDownImages_[(int)(count / 60)]);
		isCountDown_ = true;
	}
	else {
		isCountDown_ = false;
	}

}

void CountDown::Release()
{
}
