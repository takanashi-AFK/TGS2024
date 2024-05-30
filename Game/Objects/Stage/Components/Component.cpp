#include "Component.h"

// インクルード
#include "../../../../Engine/ImGui/imgui.h"
#include "../StageObject.h"

// 作成したコンポーネントのインクルード
#include "AttackComponents/Component_CactanAttack/Component_CactanAttack.h"
#include "DetectorComponents/Component_CircleRangeDetector.h"
#include "DetectorComponents/Component_FanRangeDetector.h"
#include "EnemyComponents/Component_OtiBehavior.h"
#include "HealthManagerComponents/Component_HealthManager.h"
#include "MoveComponents/Component_Chase.h"
#include "MoveComponents/Component_Fall.h"
#include "MoveComponents/Component_MoveX.h"
#include "RotationComponents/Component_Rotation.h"
#include "RotationComponents/Component_RotationX.h"
#include "RotationComponents/Component_RotationY.h"
#include "RotationComponents/Component_RotationZ.h"
#include "TimerComponent/Component_Timer.h"

Component::Component(StageObject* _holder, string _name,ComponentType _type)
    :holder_(_holder), name_(_name),type_(_type),childComponents_()
{
}

void Component::ChildIntialize()
{
	// 自身の初期化
	this->Initialize();

	// 子コンポーネントの初期化
	for (auto comp : childComponents_)comp->ChildIntialize();
}

void Component::ChildUpdate()
{
	// 自身の更新
	this->Update();

	// 子コンポーネントの更新
	for (auto comp : childComponents_)comp->ChildUpdate();
}

void Component::ChildRelease()
{
	// 子コンポーネントの開放
	for (auto comp : childComponents_) comp->ChildRelease();
	childComponents_.clear();
	
	// 自身の開放
	this->Release();
}

void Component::ChildDrawData()
{
	if (ImGui::TreeNode(this->name_.c_str())) {
		
		// 自身の情報を描画
		this->DrawData();

		// 子コンポーネントの情報を描画
		if (childComponents_.empty() == false) {
			if (ImGui::TreeNode("childComponents_")) {
				// 子コンポーネントの情報を描画
				for (auto comp : childComponents_) comp->ChildDrawData();

				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
}

void Component::ChildSave(json& _saveObj)
{
	// 自身の情報を保存
	_saveObj["type_"] = type_;
	_saveObj["name_"] = name_;

	this->Save(_saveObj);

	// 子コンポーネントの情報を保存
	for (auto comp : childComponents_)comp->ChildSave(_saveObj["childComponents_"][comp->GetName()]);
}

void Component::ChildLoad(json& _loadObj)
{
	// 自身の情報を保存
	this->Load(_loadObj);

	// 子コンポーネントの情報を読込
	for (auto comp : childComponents_)comp->ChildLoad(_loadObj["childComponents_"][comp->GetName()]);
}

bool Component::AddChildComponent(Component* _comp)
{
	// ヌルチェック
	if (_comp == nullptr)
		return false;

	// 初期化
	_comp->ChildIntialize();

	// コンポーネントのリストに追加する
	childComponents_.push_back(_comp);
	return true;
}

bool Component::DeleteChildComponent(Component* _comp)
{
	// イテレータに、"childComponents_"内で探したいデータを登録
	auto it = std::find(childComponents_.begin(), childComponents_.end(), _comp);

	// イテレータがリストの最後まで到達したら関数終了
	if (it == childComponents_.end())
		return false;

	// イテレータのコンポーネントを消す
	childComponents_.erase(it);
	return true;
}

bool Component::FindChildComponent(ComponentType _type)
{
	// リスト内のコンポーネントを探す
	for (auto comp : childComponents_) if (comp->type_ == _type)return true;
	return false;
}

Component* Component::GetChildComponent(ComponentType _type)
{
	// リスト内のコンポーネントを探す
	for(auto comp : childComponents_) if(comp->type_ == _type)return comp;
	return nullptr;
}

Component* CreateComponent(string _name,ComponentType _type, StageObject* _holder)
{
	Component* comp = nullptr;

	// タイプ(識別番号にしたがってコンポーネントを作成)
	switch (_type)
	{
	case Rotation:comp = new Component_Rotation(_name,_holder);break;
	case RotationY:comp = new Component_RotationY(_name,_holder); break;
	case RotationX:comp = new Component_RotationX(_name,_holder); break;
	case RotationZ:comp = new Component_RotationZ(_name,_holder); break;
	case MoveX:comp = new Component_MoveX(_name,_holder); break;
	case Fall:comp = new Component_Fall(_name,_holder); break;
	case Chase:comp = new Component_Chase(_name,_holder); break;
	case CircleRangeDetector:comp = new Component_CircleRangeDetector(_name,_holder); break;
	case FanRangeDetector:comp = new Component_FanRangeDetector(_name,_holder); break;
	case OtiBehavior:comp = new Component_OtiBehavior(_name,_holder); break;
	case Timer:comp = new Component_Timer(_name,_holder); break;
	case HealthManager:comp = new Component_HealthManager(_name,_holder); break;
	case CactanAttack:comp = new Component_CactanAttack(_name,_holder); break;

	default:/* その他コンポーネントを追加する時は上記のように追加*/ break;
	}
	return comp;
}
