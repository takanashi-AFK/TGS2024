#include "Scene_Splash.h"

// インクルード
#include "../../Engine/Global.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/SceneManager.h"

// 定数
namespace {
	const float LIMIT_TIME = 1.f;				// シーンを切り替えるまでに掛かる時間（秒）
	const float IMAGE_REDUCTION_RATE = 0.67f;	// スプラッシュ画像の縮小倍率
}

Scene_Splash::Scene_Splash(GameObject* _parent)
	:GameObject(_parent,"Scene_Splash"),imageHandle_(-1),count_()
{
}

void Scene_Splash::Initialize()
{
	// 画像の読込
	imageHandle_ = Image::Load("Images/splash_Image_dungeon_Path.png");
	assert(imageHandle_ >= 0);

	// 画像サイズを指定
	SetScale2D(IMAGE_REDUCTION_RATE);
}

void Scene_Splash::Update()
{
	// n秒経過したらシーンを移動
	if (count_ >= LIMIT_TIME * FPS)((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT);
	
	// カウントアップ
	count_++;
}

void Scene_Splash::Draw()
{
	// 画像の描画
	Image::SetTransform(imageHandle_,transform_);
	Image::Draw(imageHandle_);
}

void Scene_Splash::Release()
{
}
