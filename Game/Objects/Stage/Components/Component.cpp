#include "Component.h"

// インクルード
#include "../../../../Engine/ImGui/imgui.h"
#include "../StageObject.h"

// 作成したコンポーネントのインクルード
#include "StateManagerComponent/Component_StateManager.h"
#include "MoveComponent/Component_InputMove.h"

Component::Component(StageObject* _holder, string _name,ComponentType _type)
    :holder_(_holder), name_(_name),type_(_type),childComponents_(),parent_(nullptr),isActive_(false)
{
}

Component::Component(StageObject* _holder, string _name, ComponentType _type, Component* _parent)
	: holder_(_holder), name_(_name), type_(_type), childComponents_(),parent_(_parent), isActive_(false)
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
	for (auto comp : childComponents_) {
		comp->ChildRelease();
		delete comp;
	}
	childComponents_.clear();
	
	// 自身の開放
	this->Release();
}

void Component::ChildOnCollision(GameObject* _target, Collider* _collider)
{
	// 自身の衝突処理
	this->OnCollision(_target,_collider);

	// 子コンポーネントの衝突処理
	for (auto comp : childComponents_)comp->ChildOnCollision(_target,_collider);
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

vector<Component*> Component::GetChildComponent(ComponentType _type)
{
	vector<Component*> result;

	// リスト内のコンポーネントを探す
	for (auto comp : childComponents_)
	{
		if (comp->type_ == _type)
		{
			result.push_back(comp);
		}
	}
	return result;
}

Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder, Component* _parent)
{
    Component* comp = nullptr;

    // タイプ(識別番号にしたがってコンポーネントを作成)
    switch (_type)
    {
		case ComponentType::StateManager: comp = new Component_StateManager(_name, _holder, _parent); break;
		case ComponentType::InputMove: comp = new Component_InputMove(_name, _holder, _parent); break;

		default: /* その他コンポーネントを追加する時は上記のように追加 */ break;
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
		case ComponentType::StateManager:	return "StateManager";
		case ComponentType::InputMove:		return "InputMove";
		default: return "None";
	}	
}
