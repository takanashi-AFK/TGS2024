#include "Component.h"

// インクルード
#include "../../../../Engine/ImGui/imgui.h"
#include "../StageObject.h"

// 作成したコンポーネントのインクルード
#include "AttackComponents/Component_ShootAttack.h"
#include "DetectorComponents/Component_CircleRangeDetector.h"
#include "DetectorComponents/Component_FanRangeDetector.h"
#include "BehaviorComponents/Component_HelingoBehavior.h"
#include "BehaviorComponents/Component_CactanBehavior.h"
#include "BehaviorComponents/Component_PlayerBehavior.h"
#include "GaugeComponents/Component_HealthGauge.h"
#include "MoveComponents/Component_Chase.h"
#include "MoveComponents/Component_HelingoFall.h"
#include "MoveComponents/Component_MoveX.h"
#include "RotationComponents/Component_Rotation.h"
#include "RotationComponents/Component_RotationX.h"
#include "RotationComponents/Component_RotationY.h"
#include "RotationComponents/Component_RotationZ.h"
#include "TimerComponent/Component_Timer.h"
#include "MoveComponents/Component_WASDInputMove.h"
#include "MoveComponents/Component_Fall.h"
#include "MoveComponents/Component_Rise.h"

Component::Component(StageObject* _holder, string _name,ComponentType _type)
    :holder_(_holder), name_(_name),type_(_type),childComponents_(),parent_(nullptr)
{
}

Component::Component(StageObject* _holder, string _name, ComponentType _type, Component* _parent)
	: holder_(_holder), name_(_name), type_(_type), childComponents_(),parent_(_parent)
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

void Component::ChildOnCollision(GameObject* _target)
{
	// 自身の衝突処理
	this->OnCollision(_target);

	// 子コンポーネントの衝突処理
	for (auto comp : childComponents_)comp->ChildOnCollision(_target);
}

void Component::ChildDrawData()
{
	if (ImGui::TreeNode(this->name_.c_str())) {
		
		ImGui::SameLine();
		
		// コンポーネントの削除
		if (ImGui::SmallButton("Delete")) {

			if(parent_ != nullptr)parent_->DeleteChildComponent(this->name_);
			holder_->DeleteComponent(this);
		}
		

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
bool Component::DeleteChildComponent(string _name)
{
    // リスト内のコンポーネントを探す
    for (auto it = childComponents_.begin(); it != childComponents_.end(); ++it)
    {
        if ((*it)->name_ == _name)
        {
            // 子コンポーネントを開放
            (*it)->ChildRelease();
            // リストから削除
            childComponents_.erase(it);
            return true;
        }
    }
    return false;
}

bool Component::FindChildComponent(string _name)
{
    // リスト内のコンポーネントを探す
    for (auto comp : childComponents_)
    {
        if (comp->name_ == _name)
        {
            return true;
        }
    }
    return false;
}

Component* Component::GetChildComponent(string _name)
{
    // リスト内のコンポーネントを探す
    for (auto comp : childComponents_)
    {
        if (comp->name_ == _name)
        {
            return comp;
        }
    }
    return nullptr;
}

Component* CreateComponent(string _name,ComponentType _type, StageObject* _holder, Component* _parent)
{
	Component* comp = nullptr;

	// タイプ(識別番号にしたがってコンポーネントを作成)
	switch (_type)
	{
	case Rotation:comp = new Component_Rotation(_name,_holder,_parent);break;
	case RotationY:comp = new Component_RotationY(_name,_holder, _parent); break;
	case RotationX:comp = new Component_RotationX(_name,_holder, _parent); break;
	case RotationZ:comp = new Component_RotationZ(_name,_holder, _parent); break;
	case MoveX:comp = new Component_MoveX(_name,_holder, _parent); break;
	case HelingoFall:comp = new Component_HelingoFall(_name,_holder, _parent); break;
	case Chase:comp = new Component_Chase(_name,_holder, _parent); break;
	case CircleRangeDetector:comp = new Component_CircleRangeDetector(_name,_holder, _parent); break;
	case FanRangeDetector:comp = new Component_FanRangeDetector(_name,_holder, _parent); break;
	case HelingoBehavior:comp = new Component_HelingoBehavior(_name,_holder, _parent); break;
	case CactanBihavior:comp = new Component_CactanBehavior(_name, _holder, _parent); break;
	case PlayerBehavior:comp = new Component_PlayerBehavior(_name, _holder, _parent); break;
	case Timer:comp = new Component_Timer(_name,_holder, _parent); break;
	case HealthGauge:comp = new Component_HealthGauge(_name,_holder, _parent); break;
	case ShootAttack:comp = new Component_ShootAttack(_name,_holder, _parent); break;
	case WASDInputMove:comp = new Component_WASDInputMove(_name, _holder, _parent); break;
	case Fall:comp = new Component_Fall(_name, _holder, _parent); break;
	case Rise:comp = new Component_Rise(_name, _holder, _parent); break;

	default:/* その他コンポーネントを追加する時は上記のように追加*/ break;
	}
	return comp;
}

Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder)
{
	return CreateComponent(_name,_type,_holder,nullptr);
}

string ComponentTypeToString(ComponentType _type)
{
	switch (_type)
	{
	case Rotation: return "RotationComponent";
	case RotationY: return "RotationYComponent";
	case RotationX: return "RotationXComponent";
	case RotationZ: return "RotationZComponent";
	case MoveX: return "MoveXComponent";
	case HelingoFall: return "HelingoFallComponent";
	case Chase: return "ChaseComponent";
	case CircleRangeDetector: return "CircleRangeDetectorComponent";
	case FanRangeDetector: return "FanRangeDetectorComponent";
	case HelingoBehavior: return "HelingoBehaviorComponent";
	case CactanBihavior: return "CactanBihaviorComponent";
	case PlayerBehavior: return "PlayerBehaviorComponent";
	case Timer: return "TimerComponent";
	case HealthGauge: return "HealthGaugeComponent";
	case ShootAttack: return "ShootAttackComponent";
	case WASDInputMove: return "WASDInputMoveComponent";
	case Fall: return "FallComponent";
	case Rise: return "RiseComponent";
		// コンポーネント追加時に識別番号を追加
	}
	return "None";
}
