#include "UIButton.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Direct3D.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/Global.h"

using namespace FileManager;

UIButton::UIButton(string _name, GameObject* parent)
	: UIObject(_name, UIType::UI_BUTTON, parent), imageHandle_(-1), imageFilePath_()
{
}

void UIButton::Initialize()
{
	//LockRotate();

}

void UIButton::Update()
{
	if (imageHandle_ < 0)return;

	// �}�E�X�̍��W���擾
	XMFLOAT2 mousePos = { Input::GetMousePosition().x,Input::GetMousePosition().y };

	// �}�E�X�̍��W���摜�̍��W�ɕϊ�
	ConvertToImageCoordinates(mousePos);

	if (IsMouseOver(mousePos))
		Image::SetAlpha(imageHandle_, 192);
	else
		Image::SetAlpha(imageHandle_, 256);
}

void UIButton::Draw()
{
	// �摜���ǂݍ��܂�Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (imageHandle_ < 0)return;

	Image::SetTransform(imageHandle_, transform_);
	Image::Draw(imageHandle_);
}

void UIButton::Release()
{
}

void UIButton::Save(json& saveObj)
{
	saveObj["imageFilePath_"] = imageFilePath_;
}

void UIButton::Load(json& loadObj)
{
	if (loadObj.contains("imageFilePath_")) {
		imageFilePath_ = loadObj["imageFilePath_"].get<string>();
		SetImage(imageFilePath_);
	}
}

void UIButton::DrawData()
{
	if (ImGui::TreeNode("imageFilePath_")) {

		ImGui::Text("imageFilePath_:%s", imageFilePath_.c_str());
		ImGui::SameLine();

		if (ImGui::SmallButton("...")) {
			//���݂̃J�����g�f�B���N�g�����o���Ă���
			char defaultCurrentDir[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

			// �ǉ�����I�u�W�F�N�g�̃��f���t�@�C���p�X��ݒ�
			{
				// �u�t�@�C�����J���v�_�C�A���O�̐ݒ�p�\���̂�ݒ�
				OPENFILENAME ofn; {
					TCHAR szFile[MAX_PATH] = {}; // �t�@�C�������i�[����o�b�t�@
					ZeroMemory(&ofn, sizeof(ofn)); // �\���̂̏�����
					ofn.lStructSize = sizeof(ofn); // �\���̂̃T�C�Y
					ofn.lpstrFile = szFile; // �t�@�C�������i�[����o�b�t�@
					ofn.lpstrFile[0] = '\0'; // ������
					ofn.nMaxFile = sizeof(szFile); // �t�@�C�����o�b�t�@�̃T�C�Y
					ofn.lpstrFilter = TEXT("PNG�t�@�C��(*.fbx)\0*.png\0���ׂẴt�@�C��(*.*)\0*.*\0"); // �t�B���^�[�iFBX�t�@�C���̂ݕ\���j
					ofn.nFilterIndex = 1; // �����I������t�B���^�[
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // �t���O�i�t�@�C�������݂��邱�ƁA�p�X�����݂��邱�Ƃ��m�F�j
					ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
				}

				// �t�@�C����I������_�C�A���O�̕\��
				if (GetOpenFileName(&ofn) == TRUE) {
					// �t�@�C���p�X���擾
					imageFilePath_ = ofn.lpstrFile;

					// �J�����g�f�B���N�g������̑��΃p�X���擾
					imageFilePath_ = FileManager::GetAssetsRelativePath(imageFilePath_);

					// ���������"\\"��"/"�ɒu��
					FileManager::ReplaceBackslashes(imageFilePath_);

					// �f�B���N�g����߂�
					SetCurrentDirectory(defaultCurrentDir);

					// �摜��ǂݍ���
					SetImage(imageFilePath_);
				}
				else {
					return;
				}
			}
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Data"))
	{
		ImGui::Text("OnClick: %s", OnClick() ? "true" : "false");

		XMFLOAT2 mousePos = { Input::GetMousePosition().x,Input::GetMousePosition().y };
		ConvertToImageCoordinates(mousePos);
		if (imageHandle_ >= 0)ImGui::Text("IsMouseOver: %s", IsMouseOver(mousePos) ? "true" : "false");

		ImGui::TreePop();
	}
}

void UIButton::SetImage(string _imageFilePath)
{
	imageFilePath_ = _imageFilePath;
	imageHandle_ = Image::Load(_imageFilePath);
}

bool UIButton::OnClick()
{
	// �}�E�X�̍��W���擾
	XMFLOAT2 mousePos = { Input::GetMousePosition().x,Input::GetMousePosition().y };

	// �}�E�X�̍��W���摜�̍��W�ɕϊ�
	ConvertToImageCoordinates(mousePos);

	//�}�E�X�̃|�W�V�������摜�̗̈�ɓ����Ă��邩���N���b�N�������ꂽ��
	return IsMouseOver(mousePos) && Input::IsMouseButtonDown(0);
}

bool UIButton::IsMouseOver(XMFLOAT2 _mousePosition)
{
	// �摜���ǂݍ��܂�Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (imageHandle_ < 0)return false;

	// �}�E�X�J�[�\���̍��W���擾
	XMFLOAT2 imageSize = Image::GetSize(imageHandle_); {
		// �摜�̃T�C�Y����ʃT�C�Y�ɍ��킹��
		imageSize.x = imageSize.x / Direct3D::screenWidth_;
		imageSize.y = imageSize.y / Direct3D::screenHeight_;
	}

	// �摜�̔����̃T�C�Y���擾
	float imageHelfWidth = imageSize.x ;
	float imageHelfHeight = imageSize.y;

	//    // �摜�̒��S���W���擾
	//    XMFLOAT2 center = { transform_.position_.x,transform_.position_.y };
	//
	//    // �摜�̊g�嗦���擾
	//    XMFLOAT2 scale = { transform_.scale_.x,transform_.scale_.y };
	//
	//    // ����p�͈̔͂̒l���擾
	//    float top = center.y - (imageHelfHeight * 2.f * scale.y);       // �摜�̒��S�����ɉ摜�̍����̔����̋���
	//    float bottom = center.y + (imageHelfHeight * 2.f * scale.y);    // �摜�̒��S���牺�ɉ摜�̍����̔����̋���
	//    float left = center.x - (imageHelfWidth * 2.f * scale.x);       // �摜�̒��S���獶�ɉ摜�̕��̔����̋���
	//    float right = center.x + (imageHelfWidth * 2.f * scale.x);      // �摜�̒��S����E�ɉ摜�̕��̔����̋���
	//    
	//    // ����͈͓��Ƀ}�E�X�J�[�\���������Ă��邩�ǂ�����Ԃ�
	//    return (_mousePosition.x >= left && _mousePosition.x <= right && _mousePosition.y >= top && _mousePosition.y <= bottom);

	//�s��擾
	XMMATRIX buttonMat = transform_.GetWorldMatrix();

	//�t�s��v�Z
	XMMATRIX buttonMattrix = XMMatrixInverse(nullptr, buttonMat);

	//�}�E�X�̃|�W�V�������x�N�^�[�ɕϊ�
	XMVECTOR mouseVecPos = XMVectorSet(_mousePosition.x, _mousePosition.y, 0.0f, 0.0f);

	//�t�s��ƃx�N�^�[�^�̃}�E�X�̃|�W�V������������
	XMVECTOR localMousePos = XMVector3TransformCoord(mouseVecPos, buttonMattrix);

	XMFLOAT2 currentMousePos;
	XMStoreFloat2(&currentMousePos, localMousePos);

	return (currentMousePos.x >= -imageHelfWidth && currentMousePos.x <= imageHelfWidth && currentMousePos.y >= -imageHelfHeight&& currentMousePos.y <= imageHelfHeight);
}

void UIButton::ConvertToImageCoordinates(XMFLOAT2& _position)
{
	int scWidth = Direct3D::screenWidth_;
	int scHeight = Direct3D::screenHeight_;

#ifdef _DEBUG
	scWidth = scWidth * 0.7;
	scHeight = scHeight * 0.7;
#endif // _DEBUG

	// �}�E�X�̍��W���摜�̍��W�ɕϊ�
	_position.x = (float)(_position.x * 2.0f) / (float)scWidth - 1.0f;
	_position.y = 1.0f - (float)(_position.y * 2.0f) / (float)scHeight;
}
