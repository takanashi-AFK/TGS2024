#include "Component.h"

// �C���N���[�h
#include "../../../../Engine/ImGui/imgui.h"
#include "../StageObject.h"

// �쐬�����R���|�[�l���g�̃C���N���[�h
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
	// ���g�̏�����
	this->Initialize();

	// �q�R���|�[�l���g�̏�����
	for (auto comp : childComponents_)comp->ChildIntialize();
}

void Component::ChildUpdate()
{
	// ���g�̍X�V
	this->Update();

	// �q�R���|�[�l���g�̍X�V
	for (auto comp : childComponents_)comp->ChildUpdate();
}

void Component::ChildRelease()
{
	// �q�R���|�[�l���g�̊J��
	for (auto comp : childComponents_) {
		comp->ChildRelease();
		delete comp;
	}
	childComponents_.clear();
	
	// ���g�̊J��
	this->Release();
}

void Component::ChildOnCollision(GameObject* _target, Collider* _collider)
{
	// ���g�̏Փˏ���
	this->OnCollision(_target,_collider);

	// �q�R���|�[�l���g�̏Փˏ���
	for (auto comp : childComponents_)comp->ChildOnCollision(_target,_collider);
}

void Component::ChildDrawData()
{
	if (ImGui::TreeNode(this->name_.c_str())) {
		
		ImGui::SameLine();
		
		// �R���|�[�l���g�̍폜
		if (ImGui::SmallButton("Delete")) {

			if(parent_ != nullptr)parent_->DeleteChildComponent(this->name_);
			holder_->DeleteComponent(this);
		}
		

		// ���g�̏���`��
		this->DrawData();

		// �q�R���|�[�l���g�̏���`��
		if (childComponents_.empty() == false) {
			if (ImGui::TreeNode("childComponents_")) {
				// �q�R���|�[�l���g�̏���`��
				for (auto comp : childComponents_) comp->ChildDrawData();

				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
}

void Component::ChildSave(json& _saveObj)
{
	// ���g�̏���ۑ�
	_saveObj["type_"] = type_;
	_saveObj["name_"] = name_;

	this->Save(_saveObj);

	// �q�R���|�[�l���g�̏���ۑ�
	for (auto comp : childComponents_)comp->ChildSave(_saveObj["childComponents_"][comp->GetName()]);
}

void Component::ChildLoad(json& _loadObj)
{
	// ���g�̏���ۑ�
	this->Load(_loadObj);

	// �q�R���|�[�l���g�̏���Ǎ�
	for (auto comp : childComponents_)comp->ChildLoad(_loadObj["childComponents_"][comp->GetName()]);
}

bool Component::AddChildComponent(Component* _comp)
{
	// �k���`�F�b�N
	if (_comp == nullptr)
		return false;

	// ������
	_comp->ChildIntialize();

	// �R���|�[�l���g�̃��X�g�ɒǉ�����
	childComponents_.push_back(_comp);
	return true;
}

bool Component::DeleteChildComponent(string _name)
{
    // ���X�g���̃R���|�[�l���g��T��
    for (auto it = childComponents_.begin(); it != childComponents_.end(); ++it)
    {
        if ((*it)->name_ == _name)
        {
            // �q�R���|�[�l���g���J��
            (*it)->ChildRelease();
            // ���X�g����폜
            childComponents_.erase(it);
            return true;
        }
    }
    return false;
}

bool Component::FindChildComponent(string _name)
{
    // ���X�g���̃R���|�[�l���g��T��
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
    // ���X�g���̃R���|�[�l���g��T��
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

	// ���X�g���̃R���|�[�l���g��T��
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

    // �^�C�v(���ʔԍ��ɂ��������ăR���|�[�l���g���쐬)
    switch (_type)
    {
		case ComponentType::StateManager: comp = new Component_StateManager(_name, _holder, _parent); break;
		case ComponentType::InputMove: comp = new Component_InputMove(_name, _holder, _parent); break;

		default: /* ���̑��R���|�[�l���g��ǉ����鎞�͏�L�̂悤�ɒǉ� */ break;
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
