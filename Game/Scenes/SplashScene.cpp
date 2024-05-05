#include "SplashScene.h"

// インクルード
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/SceneManager.h"

// 定数
namespace {
	const float FPS = 60.f;			// フレームレート
	const float LIMIT_TIME = 1.f;	// シーンを切り替えるまでに掛かる時間（秒）
	const float IMAGE_REDUCTION_RATE = 0.67f;	// スプラッシュ画像の縮小倍率
}

SplashScene::SplashScene(GameObject* _parent)
	:GameObject(_parent,"SplashScene"),imageHandle_(-1),count_(0)
{
}

void SplashScene::Initialize()
{
	// 画像の読込
	imageHandle_ = Image::Load("Images/splash_Image_dungeon_Path.png");
	assert(imageHandle_ >= 0);

	// 画像サイズを指定
	transform_.scale_ = { IMAGE_REDUCTION_RATE,IMAGE_REDUCTION_RATE,1.f };
}

void SplashScene::Update()
{
	// n秒経過したらシーンを移動
	if (count_ >= LIMIT_TIME * FPS)((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT);
	
	// カウントアップ
	count_++;
}

void SplashScene::Draw()
{
	// 画像の描画
	Image::SetTransform(imageHandle_,transform_);
	Image::Draw(imageHandle_);
}

void SplashScene::Release()
{
}
