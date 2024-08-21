#include "StageObject.h"

// �C���N���[�h
#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/ResourceManager/Model.h"
#include "Stage.h"

namespace {
	static bool isShowAddComponentWindow_ = false; // �R���|�[�l���g�ǉ��E�B���h�E�̕\���t���O
	static bool isShowSetComponentNameWindow_ = false; // �R���|�[�l���g�ǉ��E�B���h�E�̕\���t���O
	const float MODEL_SCALE = 1.f; // ���f���̃X�P�[��
	static ComponentType selectComponentType_; // �I�����ꂽ�R���|�[�l���g�^�C�v

	void DrawAddComponentWindow(StageObject* _holder)
	{
		ImGui::Begin("Components that can be added", &isShowAddComponentWindow_); {
			for (int i = 0; i < ComponentType::Max; i++) {
				if (ImGui::Selectable(ComponentTypeToString((ComponentType)i).c_str(), selectComponentType_ == i)) {

					// �I�����Ă���R���|�[�l���g�^�C�v����
					selectComponentType_ = (ComponentType)i; 

					// �E�B���h�E�����
					isShowAddComponentWindow_ = false;

					// �R���|�[�l���g������͂���E�B���h�E��\��
					isShowSetComponentNameWindow_ = true;	
				}
			}
		}
		ImGui::End();
	}

	void DrawSetComponentNameWindow(StageObject* _object)
	{
		ImGui::Begin("Set Component Name",&isShowSetComponentNameWindow_); {
            static char buffer[256] = "";
			ImGui::InputTextWithHint("##Input", "Input New name...", buffer, IM_ARRAYSIZE(buffer));
			ImGui::SameLine();
			if (ImGui::Button("create")) {

				// �R���|�[�l���g���쐬
				_object->AddComponent(CreateComponent(buffer, selectComponentType_, _object));

				isShowSetComponentNameWindow_ = false;
				
				// �o�b�t�@���N���A
				memset(buffer, 0, sizeof(buffer));

			}
		}
		ImGui::End();
	}
}


StageObject::StageObject(string _name, string _modelFilePath, GameObject* _parent)
	:GameObject(_parent, _name), modelFilePath_(_modelFilePath), modelHandle_(-1), myComponents_(), fallSpeed_(1), isOnGround_(false)
	, isShadeVisible_(true)
{
}

bool StageObject::AddComponent(Component* _comp)
{
	// �k���`�F�b�N
	if (_comp == nullptr) return false;

	// ������
	_comp->ChildIntialize();

	// �R���|�[�l���g��vector�ɒǉ�����
	myComponents_.push_back(_comp); 
	return true;
}

Component* StageObject::FindComponent(string _name)
{
	Component* result = nullptr;

	for (auto comp : myComponents_) {
		if (comp->GetName() == _name) {
			result = comp;
			break;
		}

		// �q�R���|�[�l���g���ċA�I�Ɍ���
		result = comp->GetChildComponent(_name);
		if (result != nullptr)break;
	}
	return result;
}

vector<Component*> StageObject::FindComponent(ComponentType _type)
{
	vector<Component*> result;

	for (auto comp : myComponents_) {
		if (comp->GetType() == _type)result.push_back(comp);

		// �q�R���|�[�l���g���ċA�I�Ɍ���
		auto childComps = comp->GetChildComponent(_type);
		result.insert(result.end(), childComps.begin(), childComps.end());
	}
	return result;
}

bool StageObject::DeleteComponent(Component* _comp)
{
	// �C�e���[�^�ɁA"myComponents_"���ŒT�������f�[�^��o�^
	auto it = std::find(myComponents_.begin(), myComponents_.end(), _comp);

	// �C�e���[�^�����X�g�̍Ō�܂œ��B������֐��I��
	if (it == myComponents_.end()) return false;

	// �C�e���[�^�̃R���|�[�l���g������
	myComponents_.erase(it); return true;
}

bool StageObject::DeleteAllComponent()
{
	// ���X�g���ɂ���v�f�����ׂč폜
	myComponents_.clear();return true;
}

void StageObject::OnGround(float _fallSpeed)
{
	if (isOnGround_ == false)return;

	Stage* pStage = (Stage*)FindObject("Stage");
	if (pStage == nullptr)return;
	auto stageObj = pStage->GetStageObjects();

	for (auto obj : stageObj) {
		if (obj->GetObjectName() == this->objectName_)
			continue;

		int hGroundModel = obj->modelHandle_;
		if (hGroundModel < 0)continue;

		RayCastData data;
		data.start = transform_.position_;   //���C�̔��ˈʒu
		data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
		Model::RayCast(hGroundModel, &data); //���C�𔭎�

		//���C������������
		if (data.hit) {
			//���̕��ʒu��������
			transform_.position_.y -= (data.dist- (MODEL_SCALE/2)) * _fallSpeed;
		}
	}
}

void StageObject::CollisionWall()
{
	if (!isCollisionWall_) return;

	Stage* pStage = static_cast<Stage*>(FindObject("Stage"));
	if (pStage == nullptr) return;
	auto stageObj = pStage->GetStageObjects();

	for (auto obj : stageObj) {
		if (obj->GetObjectName() == this->objectName_)
			continue;

		int hGroundModel = obj->modelHandle_;
		if (hGroundModel < 0) continue;

		std::vector<XMFLOAT3> directions = {
			XMFLOAT3(1, 0, 0),  // right
			XMFLOAT3(-1, 0, 0), // left
			XMFLOAT3(0, 0, 1),  // forward
			XMFLOAT3(0, 0, -1)  // backward
		};

		for (const auto& dir : directions) {
			RayCastData data;
			data.start = transform_.position_; // ���C�̔��ˈʒu
			data.dir = dir; // ���C�̕���
			Model::RayCast(hGroundModel, &data); // ���C�𔭎�

			if (data.dist < 0.6f && data.dist > 0.0f) {
				if (dir.x != 0) {
					transform_.position_.x -= dir.x * (0.6f - data.dist);
				}
				else if (dir.z != 0) {
					transform_.position_.z -= dir.z * (0.6f - data.dist);
				}
			}
		}
	}
}

void StageObject::PlayAnimation(int _start, int _end, float _speed)
{
	Model::SetAnimFrame(modelHandle_,_start, _end, _speed);

}

void StageObject::Initialize()
{
	// ���f���̓ǂݍ���
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= 0);

	// �ۗL����R���|�[�l���g�̏���������
	for (auto comp : myComponents_)comp->ChildIntialize();
}

void StageObject::Update()
{
	// �ۗL����R���|�[�l���g�̍X�V����
	for (auto comp : myComponents_)comp->ChildUpdate();
	OnGround(fallSpeed_);
	CollisionWall();
}

void StageObject::Draw()
{
	if (isShadeVisible_ == false)Direct3D::SetShader(Direct3D::SHADER_SKY);

	// ���f���̕`��
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);

	if (isShadeVisible_ == true)Direct3D::SetShader(Direct3D::SHADER_3D);
}

void StageObject::Release()
{
	// �ۗL����R���|�[�l���g�̊J������
	for (auto comp : myComponents_) {
		comp->ChildRelease();
		delete comp;
	}
	myComponents_.clear();
}

void StageObject::OnCollision(GameObject* _target, Collider* _collider)
{
	// �ۗL����R���|�[�l���g�̏Փˏ���
	for (auto comp : myComponents_)comp->ChildOnCollision(_target, _collider);
}

void StageObject::Save(json& _saveObj)
{
	// ���g�̕ό`�s�����ۑ�
	_saveObj["position_"] = { REFERENCE_XMFLOAT3(transform_.position_) };
	_saveObj["rotate_"] = { REFERENCE_XMFLOAT3(transform_.rotate_) };
	_saveObj["scale_"] = { REFERENCE_XMFLOAT3(transform_.scale_)};
	_saveObj["fallSpeed_"] = fallSpeed_;
	_saveObj["isOnGround_"] = isOnGround_;
	_saveObj["isCollisionWall_"] = isCollisionWall_;
	
	// ���g�̃��f���̃t�@�C���p�X��ۑ�
	_saveObj["modelFilePath_"] = modelFilePath_;

	// �A�e�̕\���t���O��ۑ�
	_saveObj["isShadeVisible_"] = isShadeVisible_;

	// �ڒn�����̏���ۑ�
	_saveObj["isOnGround_"] = isOnGround_;
	_saveObj["isCollisionWall_"] = isCollisionWall_;
	_saveObj["fallSpeed_"] = fallSpeed_;

	// �R���|�[�l���g����ۑ�
	for (auto comp : myComponents_)comp->ChildSave(_saveObj["myComponents_"][comp->GetName()]);
}

void StageObject::Load(json& _loadObj)
{
	// ���݂̂��ׂẴR���|�[�l���g�����폜
	this->DeleteAllComponent();

	// �ό`�s�����Ǎ�

	if (_loadObj.contains("position_"))transform_.position_ = { _loadObj["position_"][0].get<float>(),_loadObj["position_"][1].get<float>(), _loadObj["position_"][2].get<float>() };
	if (_loadObj.contains("rotate_"))transform_.rotate_ = { _loadObj["rotate_"][0].get<float>(),_loadObj["rotate_"][1].get<float>(), _loadObj["rotate_"][2].get<float>() };
	if (_loadObj.contains("scale_"))transform_.scale_ = { _loadObj["scale_"][0].get<float>(),_loadObj["scale_"][1].get<float>(), _loadObj["scale_"][2].get<float>() };
	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];
	if (_loadObj.contains("isOnGround_"))isOnGround_ = _loadObj["isOnGround_"];
	if (_loadObj.contains("isCollisionWall_"))isCollisionWall_ = _loadObj["isCollisionWall_"];


	// ���f���̃t�@�C���p�X��Ǎ�
	modelFilePath_ = _loadObj["modelFilePath_"];

	// �A�e�̕\���t���O��Ǎ�
	if(_loadObj.contains("isShadeVisible_"))isShadeVisible_ = _loadObj["isShadeVisible_"];

	// �ڒn�����̏���Ǎ�
	if (_loadObj.contains("isOnGround_"))isOnGround_ = _loadObj["isOnGround_"];
	if (_loadObj.contains("isCollisionWall_"))isCollisionWall_ = _loadObj["isCollisionWall_"];
	if (_loadObj.contains("fallSpeed_"))fallSpeed_ = _loadObj["fallSpeed_"];

	// �R���|�[�l���g�C���X�^���X�𐶐�
	for (auto& obj : _loadObj["myComponents_"]) {
		
		// �R���|�[�l���g�𐶐�
		Component* comp = CreateComponent(obj["name_"], obj["type_"], this);

		// �q�R���|�[�l���g�𐶐�
		for (auto& child : obj["childComponents_"])comp->AddChildComponent(CreateComponent(child["name_"], child["type_"], this));

		// "myComponents_"�ɒǉ�
		this->AddComponent(comp);
	}

	// �R���|�[�l���g����Ǎ�
	for (auto comp : myComponents_)comp->ChildLoad(_loadObj["myComponents_"][comp->GetName()]);
}

void StageObject::DrawData()
{
	// ��������������������������������������������
	// �I�u�W�F�N�g����\��
	// ��������������������������������������������
	ImGui::Text(this->objectName_.c_str());
	ImGui::SameLine();

	// ��������������������������������������������
	// �I�u�W�F�N�g�̍폜�{�^��
	// ��������������������������������������������
	if(ImGui::SmallButton("delete"))((Stage*)FindObject("Stage"))->DeleteStageObject(this);
	ImGui::Separator();

	// ��������������������������������������������
	// �ڒn����
	// ��������������������������������������������
	if (ImGui::TreeNode("OnGround")) {
		ImGui::Checkbox("isOnGround", &isOnGround_);
		ImGui::SameLine();
		ImGui::Checkbox("isCollisionWall", &isCollisionWall_);
		ImGui::DragFloat("fallSpeed", &fallSpeed_, 0.1f, 0.f, 1.f);

		ImGui::TreePop();
	}

	// ��������������������������������������������
	// �V�F�[�h�̕\��
	// ��������������������������������������������
	if (ImGui::TreeNode("shade")) {
		ImGui::Checkbox("isShadeVisible", &isShadeVisible_);
		ImGui::TreePop();
	}

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
		ImGui::DragFloat3("position_", &transform_.position_.x, 0.1f);
		ImGui::DragFloat3("rotate_", &transform_.rotate_.x, 1.f, -360.f, 360.f);
		ImGui::DragFloat3("scale_", &transform_.scale_.x, 0.1f, 0.f, LONG_MAX);
		ImGui::TreePop();
	}

	// ��������������������������������������������
	// �R���|�[�l���g�̏���`��
	// ��������������������������������������������
	if (ImGui::TreeNode("myComponents_")) {
		ImGui::SameLine();

		// �R���|�[�l���g�ǉ��{�^����`��
		if (ImGui::SmallButton("AddComponent")) isShowAddComponentWindow_ = true;

		// �ۗL����R���|�[�l���g�̏���`��
		for (auto comp : myComponents_)comp->ChildDrawData();
		ImGui::TreePop();
	}



	// �R���|�[�l���g�ǉ��E�B���h�E��`��
	if (isShowAddComponentWindow_)DrawAddComponentWindow(this);
	if (isShowSetComponentNameWindow_)DrawSetComponentNameWindow(this);


}

StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent)
{
	// �I�u�W�F�N�g�̃C���X�^���X�𐶐�
	StageObject* obj = new StageObject(_name, _modelFilePath, _parent);
	
	// ������
	obj->Initialize();
	
	// �e�I�u�W�F�N�g�̃��X�g�ɒǉ�
	if (_parent != nullptr)_parent->PushBackChild(obj);
	
	return obj;
}