#include "Component.h"

// �C���N���[�h
#include "../../../../Engine/ImGui/imgui.h"
#include "../../../../Engine/Global.h"
#include "../StageObject.h"

// �쐬�����R���|�[�l���g�̃C���N���[�h
#include "AttackComponents/Component_MeleeAttack.h"
#include "AttackComponents/Component_ShootAttack.h"
#include "BehaviorComponents/Component_BossBehavior.h"
#include "BehaviorComponents/Component_CactanBehavior.h"
#include "BehaviorComponents/Component_HelingoBehavior.h"
#include "BehaviorComponents/Component_PlayerBehavior.h"
#include "DetectorComponents/Component_CircleRangeDetector.h"
#include "DetectorComponents/Component_FanRangeDetector.h"
#include "GaugeComponents/Component_HealthGauge.h"
#include "MoveComponents/Component_Chase.h"
#include "MoveComponents/Component_Fall.h"
#include "MoveComponents/Component_HelingoFall.h"
#include "MoveComponents/Component_MoveX.h"
#include "MoveComponents/Component_Rise.h"
#include "MoveComponents/Component_TackleMove.h"
#include "MoveComponents/Component_WASDInputMove.h"
#include "RotationComponents/Component_Rotation.h"
#include "RotationComponents/Component_RotationX.h"
#include "RotationComponents/Component_RotationY.h"
#include "RotationComponents/Component_RotationZ.h"
#include "TimerComponent/Component_Timer.h"
#include "MotionComponent/Component_PlayerMotion.h"
#include "TeleporterComponent/Component_Teleporter.h"
#include "StateComponents/Component_StateManager.h"

Component::Component(StageObject* _holder, string _name,ComponentType _type)
    :holder_(_holder), name_(_name),type_(_type),childComponents_(),parent_(nullptr),isActive_(false)
{
	name_ = stringConverter::ConvertToLower(name_);
}

Component::Component(StageObject* _holder, string _name, ComponentType _type, Component* _parent)
	: holder_(_holder), name_(_name), type_(_type), childComponents_(),parent_(_parent), isActive_(false)
{
	name_ = stringConverter::ConvertToLower(name_);
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
	_name = stringConverter::ConvertToLower(_name);
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
	_name = stringConverter::ConvertToLower(_name);
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
        case BossBehavior: comp = new Component_BossBehavior(_name, _holder, _parent); break;
        case CactanBehavior: comp = new Component_CactanBehavior(_name, _holder, _parent); break;
        case Chase: comp = new Component_Chase(_name, _holder, _parent); break;
        case CircleRangeDetector: comp = new Component_CircleRangeDetector(_name, _holder, _parent); break;
        case Fall: comp = new Component_Fall(_name, _holder, _parent); break;
        case FanRangeDetector: comp = new Component_FanRangeDetector(_name, _holder, _parent); break;
        case HealthGauge: comp = new Component_HealthGauge(_name, _holder, _parent); break;
        case HelingoBehavior: comp = new Component_HelingoBehavior(_name, _holder, _parent); break;
        case HelingoFall: comp = new Component_HelingoFall(_name, _holder, _parent); break;
        case MeleeAttack: comp = new Component_MeleeAttack(_name, _holder, _parent); break;
        case MoveX: comp = new Component_MoveX(_name, _holder, _parent); break;
        case PlayerBehavior: comp = new Component_PlayerBehavior(_name, _holder, _parent); break;
        case Rise: comp = new Component_Rise(_name, _holder, _parent); break;
        case Rotation: comp = new Component_Rotation(_name, _holder, _parent); break;
        case RotationX: comp = new Component_RotationX(_name, _holder, _parent); break;
        case RotationY: comp = new Component_RotationY(_name, _holder, _parent); break;
        case RotationZ: comp = new Component_RotationZ(_name, _holder, _parent); break;
        case ShootAttack: comp = new Component_ShootAttack(_name, _holder, _parent); break;
        case TackleMove: comp = new Component_TackleMove(_name, _holder, _parent); break;
        case Timer: comp = new Component_Timer(_name, _holder, _parent); break;
        case WASDInputMove: comp = new Component_WASDInputMove(_name, _holder, _parent); break;
		case PlayerMotion: comp = new Component_PlayerMotion(_name, _holder, _parent); break;
		case Teleporter: comp = new Component_Teleporter(_name, _holder, _parent); break;
		case StateManager: comp = new Component_StateManager(_name, _holder, _parent); break;
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
	case BossBehavior: return "BossBehaviorComponent";
	case CactanBehavior: return "CactanBehaviorComponent";
	case Chase: return "ChaseComponent";
	case CircleRangeDetector: return "CircleRangeDetectorComponent";
	case Fall: return "FallComponent";
	case FanRangeDetector: return "FanRangeDetectorComponent";
	case HealthGauge: return "HealthGaugeComponent";
	case HelingoBehavior: return "HelingoBehaviorComponent";
	case HelingoFall: return "HelingoFallComponent";
	case MeleeAttack: return "MeleeAttackComponent";
	case MoveX: return "MoveXComponent";
	case PlayerBehavior: return "PlayerBehaviorComponent";
	case Rise: return "RiseComponent";
	case Rotation: return "RotationComponent";
	case RotationX: return "RotationXComponent";
	case RotationY: return "RotationYComponent";
	case RotationZ: return "RotationZComponent";
	case ShootAttack: return "ShootAttackComponent";
	case TackleMove: return "TackleMoveComponent";
	case Timer: return "TimerComponent";
	case WASDInputMove: return "WASDInputMoveComponent";
	case PlayerMotion: return "PlayerMotionComponent";
	case Teleporter: return "TeleporterComponent";
	case StateManager: return "StateManagerComponent";
	
	default: return "None";
	}	
}
