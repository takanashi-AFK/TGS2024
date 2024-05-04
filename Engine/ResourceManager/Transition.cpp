#include "Transition.h"
#include "../DirectX/Sprite.h"
#include "../Global.h"



namespace Transition 
{
	TRANSITION_ID type_ = TID_NONE;
	Sprite* pSprite_[TID_MAX] = { nullptr };

	bool isActive_ = false;	//実行中か否か
	bool isChange_ = false;	//シーンを変更して良いか
	bool isFlag = false;
	float time_ = 0;		//トランジションの再生時間
	
	Transform transform_;	//変形行列
	RECT rect_;				//画像サイズ
	float alpha_;			//画像の透明度

	const float FPS = 60.0f;			//フレームレート
	const float FINISH_TIME = 510.0f;	//トランジションの終了まで掛かる時間(fps)
	const float ALPHA_MAX = 255.0f;		//最大alpha値
	const float ALPHA_MIN = 0.0f;		//最小alpha値
}


void Transition::Initialize()
{
	for (int i = 0; i < TID_MAX; i++)
	{
		pSprite_[i] = new Sprite;
	}
	pSprite_[TID_NONE]->Load("Images/transition_blackOut.png");
	pSprite_[TID_BLACKOUT]->Load("Images/transition_blackOut.png");
	pSprite_[TID_WHITEOUT]->Load("Images/transition_whiteOut.png");
}

void Transition::Update()
{
	if (isActive_) {switch (type_) 
	{
	case TID_NONE:	isChange_ = true; isActive_ = false; break;
	case TID_BLACKOUT:BlackOut();break;
	case TID_WHITEOUT:WhiteOut();break;
	
	}}else InitParameter();
}

void Transition::Draw()
{
	pSprite_[type_]->Draw(transform_, rect_, (alpha_ / ALPHA_MAX));
}

void Transition::Release()
{
	for (int i = 0; i < TID_MAX; i++)SAFE_DELETE(pSprite_[i]);
}

bool Transition::SetTransition(TRANSITION_ID _type)
{
	type_ = _type;return _type != TID_NONE;
}

void Transition::SetTime(float _time)
{
	time_  = FINISH_TIME /(FPS *_time);
}

bool Transition::IsActive()
{
	return isActive_;
}

bool Transition::InitParameter()
{
	isChange_ = false;
	isFlag = false;
	time_ = 0;
	alpha_ = 0;

	return true;
}

void Transition::Start()
{
	isActive_ = true;
}

bool Transition::IsChangePoint()
{
	return isChange_;
}

void Transition::BlackOut()
{
	//Rectの初期化
	rect_.left = 0; rect_.right = pSprite_[TID_BLACKOUT]->GetTextureSize().x;
	rect_.top = 0; rect_.bottom = pSprite_[TID_BLACKOUT]->GetTextureSize().y;

	if (alpha_ >= ALPHA_MAX) {
		isChange_ = true;
		isFlag = true;
	}

	if (isFlag){
		alpha_-= time_;
		if (alpha_ <= ALPHA_MIN) isActive_ = false;
	}
	else alpha_+= time_;
}

void Transition::WhiteOut()
{
	//Rectの初期化
	rect_.left = 0; rect_.right = pSprite_[TID_WHITEOUT]->GetTextureSize().x;
	rect_.top = 0; rect_.bottom = pSprite_[TID_WHITEOUT]->GetTextureSize().y;

	if (alpha_ >= ALPHA_MAX) {
		isChange_ = true;
		isFlag = true;
	}

	if (isFlag) {
		alpha_ -= time_;
		if (alpha_ <= ALPHA_MIN) isActive_ = false;
	}
	else alpha_ += time_;
}