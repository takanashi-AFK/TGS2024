#include "UIObject.h"

#include "UIButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"

#include "UIPanel.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"
#include "UIProgressBar.h"
#include "UITimer.h"
#include "UIDragBar.h"

UIObject::UIObject():
	UIObject("",UI_NONE,nullptr,0)
{

}

UIObject::UIObject(UIObject* parent):
	UIObject("",UI_NONE,parent,0)
{
}

UIObject::UIObject(string _name, UIType _type, UIObject* parent, int _layerNum)
	:objectName_(_name), type_(_type), pParent_(parent), layerNumber_(_layerNum), isEnable_(true)
{

	childList_.clear();
	state_ = { 0, 1, 1, 0 };

	if (parent)
		transform_.pParent_ = &parent->transform_;

}

UIObject::~UIObject()
{
}

void UIObject::ChildSave(json& _saveObj)
{
	// �^�C�v��ۑ�
	_saveObj["type_"] = type_;
	
	// �I�u�W�F�N�g����ۑ�
	_saveObj["objectName_"] = objectName_;

	// ���C���[�ԍ���ۑ�
	_saveObj["layerNumber_"] = layerNumber_;

	// ���g�̕ό`�s�����ۑ�
	_saveObj["position_"] = { REFERENCE_XMFLOAT3(transform_.position_) };
	_saveObj["rotate_"] = { REFERENCE_XMFLOAT3(transform_.rotate_) };
	_saveObj["scale_"] = { REFERENCE_XMFLOAT3(transform_.scale_) };

	// ���g�̌ŗL����ۑ�
	this->Save(_saveObj);
}

void UIObject::ChildLoad(json& _loadObj)
{
	// �^�C�v��Ǎ�
	if(_loadObj.contains("type_"))type_ = (UIType)_loadObj["type_"].get<int>();

	// �I�u�W�F�N�g����Ǎ�
	if (_loadObj.contains("objectName_"))objectName_ = _loadObj["objectName_"];

	// ���C���[�ԍ���Ǎ�
	if (_loadObj.contains("layerNumber_"))layerNumber_ = _loadObj["layerNumber_"].get<int>();

	// �ό`�s�����Ǎ�
	if (_loadObj.contains("position_"))transform_.position_ = { _loadObj["position_"][0].get<float>(),_loadObj["position_"][1].get<float>(), _loadObj["position_"][2].get<float>() };
	if (_loadObj.contains("rotate_"))transform_.rotate_ = { _loadObj["rotate_"][0].get<float>(),_loadObj["rotate_"][1].get<float>(), _loadObj["rotate_"][2].get<float>() };
	if (_loadObj.contains("scale_"))transform_.scale_ = { _loadObj["scale_"][0].get<float>(),_loadObj["scale_"][1].get<float>(), _loadObj["scale_"][2].get<float>() };

	// �ŗL����Ǎ�
	this->Load(_loadObj);
}

void UIObject::ChildDrawData()
{
	// ��������������������������������������������
	// �I�u�W�F�N�g����\��
	// ��������������������������������������������
	ImGui::Text(this->objectName_.c_str());
	ImGui::SameLine();

	// ��������������������������������������������
	// �I�u�W�F�N�g�̍폜�{�^��
	// ��������������������������������������������
	if (ImGui::SmallButton("delete"))((UIPanel*)GetParent())->DeleteUIObject(this);
	ImGui::Separator();

	// ��������������������������������������������
	// �I�u�W�F�N�g�̖��O��ύX
	// ��������������������������������������������
	if (ImGui::TreeNode("name")) {
		ImGui::Text("Current name : %s", this->objectName_.c_str());
		char buffer[256] = "";
		if (ImGui::InputTextWithHint("##Input", "Input New name...", buffer, IM_ARRAYSIZE(buffer)))
			this->objectName_ = buffer;
		ImGui::TreePop();
	}

	// ��������������������������������������������
	// ���g�̕ό`����`��
	// ��������������������������������������������
	if (ImGui::TreeNode("transform_")) {
		if(isPositionLocked_ == false)ImGui::DragFloat3("position_", &transform_.position_.x, 0.1f);
		if(isRotateLocked_ == false)ImGui::DragFloat3("rotate_", &transform_.rotate_.x, 1.f, -360.f, 360.f);
		if(isScaleLocked_ == false)ImGui::DragFloat3("scale_", &transform_.scale_.x, 0.1f, 0.f, LONG_MAX);
		ImGui::TreePop();
	}

	// ��������������������������������������������
	// ���C���[�ԍ���`��
	// ��������������������������������������������
	if (ImGui::TreeNode("LayerNumber"))
	{ 
		layerNumber_ = GetLayerNumber();
		ImGui::Text("Image Layer Number: %d", layerNumber_);

		//�������̕����G�f�B�^�[��̓����͕�����₷������
		//layerNumber��ύX����
		// ���C���[�ԍ��̕ύX���󂯕t����
		 static int newLayerNumber = layerNumber_;

		if(newLayerNumber < 0)newLayerNumber = 1;

		ImGui::InputInt("Layer Number", &newLayerNumber);

		if (ImGui::Button("Confirm")) {

			if (newLayerNumber != layerNumber_)
			{
				SetLayerNumber(newLayerNumber);
			}

		}


		//���C���[�ԍ����d�����Ă���ꍇ�̓|�b�v�A�b�v��\��
		if (ImGui::BeginPopupModal("LayerNumberDuplicate", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Layer Number is Duplicate!!");

			if (ImGui::Button("OK", ImVec2(120, 0)))ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}


		ImGui::TreePop();
	}

	// �ŗL����`��
	this->DrawData();
}

void UIObject::KillMe()
{
	state_.dead = 1;
}

UIObject* UIObject::FindChildObject(const std::string& name)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return nullptr;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g��1���T��
	while (it != end)
	{
		//�������O�̃I�u�W�F�N�g���������炻���Ԃ�
		if((*it)->GetObjectName() == name)
			return *it;

		//���̎q���i���j�ȍ~�ɂ��Ȃ����T��
		UIObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr) {
			return obj;
		}

		//���̎q��
		it++;
	}

	//������Ȃ�����
	return nullptr;
}

const std::string& UIObject::GetObjectName(void) const
{
	return objectName_;
}

UIType UIObject::GetType(void) const
{
	return type_;
}

UIObject* UIObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}

UIObject* UIObject::GetParent(void)
{
	return pParent_;
}

void UIObject::PushBackChild(UIObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);

}

void UIObject::SetLayerNumber(int newLayerNumber_)
{
	////�V�������C���[�ԍ���0�ȉ��Ȃ�1�ɂ���
	//if (newLayerNumber_ <= 0) {
	//	ImGui::OpenPopup("LayerNumberisUnder_0");
	//	return;
	//}

	//�d���`�F�b�N
	UIObject* root = GetRootJob();//������parent�ł������񂶂�Ȃ����Ǝv��(�\�z)
	if (root != nullptr && root->IsLayerNumberDuplicate(newLayerNumber_))
	{
		//�d�����Ă���ꍇ�̓|�b�v�A�b�v��\��
		ImGui::OpenPopup("LayerNumberDuplicate");
	}
	else
	{
		//�d�����Ă��Ȃ��ꍇ�̓��C���[�ԍ���ݒ�
		layerNumber_ = newLayerNumber_;
	}
}

bool UIObject::IsLayerNumberDuplicate(int newLayerNumber_)
{
	// �������g�ȊO�̃I�u�W�F�N�g�Ń��C���[�ԍ����d�����Ă��邩�`�F�b�N
	if (this->layerNumber_ == newLayerNumber_ && this != this->GetRootJob())
	{
		return true;
	}

	//�q�I�u�W�F�N�g�̃��C���[�ԍ��Ɣ�r
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		if ((*it)->IsLayerNumberDuplicate(newLayerNumber_))return true;
	}

	//�d�����Ă��Ȃ�
	return false;

}

bool UIObject::CompareLayerNumber(UIObject* _object1, UIObject* _object2)
{
	return _object1->GetLayerNumber() < _object2->GetLayerNumber();
}

UIObject* CreateUIObject(string _name, UIType _type,UIObject* _parent, int _layerNum)
{
	// �C���X�^���X�𐶐�����
	UIObject* obj = nullptr;
	switch (_type)
	{
		case UI_BUTTON:obj = new UIButton(_name, _parent,_layerNum); break;
		case UI_IMAGE:obj = new UIImage(_name, _parent,_layerNum); break;
		case UI_TEXT:obj = new UIText(_name, _parent, _layerNum); break;
		case UI_PANEL:obj = UIPanel::GetInstance(); break;
		case UI_PROGRESSBAR: obj = new UIProgressBar(_name, _parent, _layerNum); break;
		case UI_TIMER:obj = new UITimer(_name, _parent, _layerNum); break;
		case UI_DRAGBAR:obj = new UIDragBar(_name, _parent, _layerNum); break;
        default:obj = nullptr; break;
	}
	// �C���X�^���X�������ł��Ȃ������ꍇ��nullptr��Ԃ�
	if (obj == nullptr)return nullptr;

	// �e�I�u�W�F�N�g�̎q�I�u�W�F�N�g�Ƃ��ēo�^����
	if (_parent != nullptr)_parent->PushBackChild(obj);
	
	// ���������s��
	obj->Initialize();

	// ���������I�u�W�F�N�g��Ԃ�
	return obj;
}

string GetUITypeString(UIType _type)
{
	switch (_type)
	{
	case UI_BUTTON:return "BUTTON";
	case UI_IMAGE:return "IMAGE";
	case UI_TEXT:return "TEXT";
	case UI_PANEL:return "";
	case UI_PROGRESSBAR:return "PROGRESSBAR";
	case UI_TIMER:return "TIMER";
	case UI_DRAGBAR:return "DRAGBAR";
	default:return "UNKNOWN";
	}
}

void UIObject::UpdateSub()
{
	Update();
	
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}
}

void UIObject::DrawSub()
{
	Draw();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}

}

void UIObject::ReleaseSub()
{
	for (auto it = childList_.begin(); it != childList_.end();)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
		it = childList_.erase(it);
	}

	Release();
}

bool UIObject::IsDead()
{
	return (state_.dead != 0);
}

