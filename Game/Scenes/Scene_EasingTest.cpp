#include "Scene_EasingTest.h"

// インクルード
#include"../../Engine/SceneManager.h"

#include "../Constants.h"

#include "../../Engine/DirectX/Input.h"
#include "../../Engine/ImGui/imgui.h"
#include "../Objects/UI/UIInputString.h"
#include "../Objects/UI/Easing_ForUI.h"

using namespace Constants;

Scene_EasingTest::Scene_EasingTest(GameObject* parent)
	: GameObject(parent, "Scene_EasingTest")
{
}

void Scene_EasingTest::Initialize()
{
	// UIパネル & レイアウトの読み込み
	json loadData;
	if (JsonReader::Load(EASING_TEST_SCNE_LAYOUT_JSON, loadData)) UIPanel::GetInstance()->Load(loadData);

	// ユーザー名の初期化
	i_Left = (UIImage*)UIPanel::GetInstance()->GetUIObject(Scene_EasingTestString::ImageLeft);
	i_Right = (UIImage*)UIPanel::GetInstance()->GetUIObject(Scene_EasingTestString::ImageRight);
}

void Scene_EasingTest::Update()
{
	++count_;

	auto&& e_left = i_Left->GetEasing()->GetEasing();
	auto&& e_right = i_Right->GetEasing()->GetEasing();

	e_left->pile_ = std::clamp((count_ -210.0f)/60.0f,.0f,1.0f);
	e_right->pile_ = std::clamp((count_ - 260.0f) / 60.0f, .0f, 1.0f);
	
}

void Scene_EasingTest::Draw()
{
}

void Scene_EasingTest::Release()
{
}
