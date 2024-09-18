#include "UIDragBar.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/ImGui/imgui.h"
\
UIDragBar::UIDragBar(string _name, UIObject* parent, int _layerNum)
	: UIObject(_name, UIType::UI_DRAGBAR, parent, _layerNum), barImageHandle_(-1), barImageFilePath_(), cursorImageHandle_(-1), cursorImageFilePath_()
{
}

void UIDragBar::Initialize()
{
}

void UIDragBar::Update()
{
	if (barImageHandle_ < 0)return;
	if (cursorImageHandle_ < 0)return;

	// �}�E�X�̍��W���擾
	XMFLOAT2 mousePos = { Input::GetMousePosition().x,Input::GetMousePosition().y };

	// �}�E�X�̍��W���摜�̍��W�ɕϊ�
	ConvertToImageCoordinates(mousePos);

	if (IsMouseOver(mousePos)){
		if (Input::IsMouseButton(0)){
			// �}�E�X�̍��W���摜�͈͓̔��ɂ��邩
			if (IsMouseOver(mousePos)){

				// ���E�ɂ��肮��ł���悤��
				cursorTransform_.position_.x = mousePos.x /2;

				//n�ȏゾ������Ȃ�Ƃ�
			}
		}
	}
}

void UIDragBar::Draw()
{
	// �摜���ǂݍ��܂�Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (barImageHandle_ < 0)return;
	if (cursorImageHandle_ < 0)return;

	Image::SetTransform(barImageHandle_, transform_);
	Image::Draw(barImageHandle_);

	Image::SetTransform(cursorImageHandle_, cursorTransform_);
	Image::Draw(cursorImageHandle_);
}

void UIDragBar::Release()
{
}

void UIDragBar::Save(json& saveObj)
{
	saveObj["barImageFilePath_"] = barImageFilePath_;
	saveObj["cursorImageFilePath_"] = cursorImageFilePath_;
}

void UIDragBar::Load(json& loadObj)
{
	if (loadObj.contains("barImageFilePath_") && loadObj.contains("cursorImageFilePath_")) {
		barImageFilePath_ = loadObj["barImageFilePath_"].get<string>();
		barImageHandle_ = Image::Load(barImageFilePath_);

		cursorImageFilePath_ = loadObj["cursorImageFilePath_"].get<string>();
		cursorImageHandle_ = Image::Load(cursorImageFilePath_);
	}
}

void UIDragBar::DrawData()
{
	if (ImGui::Button("SetBarIMG")) {
		//���݂̃J�����g�f�B���N�g�����o���Ă���
		char currentDir[256];
		GetCurrentDirectoryA(256, currentDir);

		//�t�@�C���p�X���擾
		char filePath[256];
		OPENFILENAMEA ofn;
		ZeroMemory(&filePath, sizeof(filePath));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = filePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(filePath);
		ofn.lpstrFilter = "Image\0*.png;*.jpg;*.bmp\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = currentDir;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		GetOpenFileNameA(&ofn);

		//�J�����g�f�B���N�g�������ɖ߂�
		SetCurrentDirectoryA(currentDir);

		//�t�@�C���p�X���擾�ł��Ă�����摜��ǂݍ���
		if (filePath[0] != '\0') {
			barImageFilePath_ = filePath;
		}

	}
	if (ImGui::Button("SetCursorIMG")) {
		//���݂̃J�����g�f�B���N�g�����o���Ă���
		char currentDir[256];
		GetCurrentDirectoryA(256, currentDir);

		//�t�@�C���p�X���擾
		char filePath[256];
		OPENFILENAMEA ofn;
		ZeroMemory(&filePath, sizeof(filePath));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = filePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(filePath);
		ofn.lpstrFilter = "Image\0*.png;*.jpg;*.bmp\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = currentDir;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		GetOpenFileNameA(&ofn);

		//�J�����g�f�B���N�g�������ɖ߂�
		SetCurrentDirectoryA(currentDir);

		//�t�@�C���p�X���擾�ł��Ă�����摜��ǂݍ���
		if (filePath[0] != '\0') {
			cursorImageFilePath_ = filePath;
		}
	}

	if (cursorImageFilePath_ != "" && barImageFilePath_ != "") {
		SetImage(barImageFilePath_, cursorImageFilePath_);
	}
}

void UIDragBar::SetImage(string _barImageFilePath, string _cursorImageFilePath)
{
	barImageFilePath_ = _barImageFilePath;
	barImageHandle_ = Image::Load(barImageFilePath_);

	cursorImageFilePath_ = _cursorImageFilePath;
	cursorImageHandle_ = Image::Load(cursorImageFilePath_);
}

void UIDragBar::ConvertToImageCoordinates(XMFLOAT2& _position)
{
	int scWidth = Direct3D::screenWidth_;
	int scHeight = Direct3D::screenHeight_;

	if (Direct3D::isFullScreen_)
		Direct3D::GetFullScreenSize(scWidth, scHeight);

#ifdef _DEBUG
	scWidth = scWidth * 0.7;
	scHeight = scHeight * 0.7;
#endif // _DEBUG

	// �}�E�X�̍��W���摜�̍��W�ɕϊ�
	_position.x = (float)(_position.x * 2.0f) / (float)scWidth - 1.0f;
	_position.y = 1.0f - (float)(_position.y * 2.0f) / (float)scHeight;

}

bool UIDragBar::IsMouseOver(XMFLOAT2 _mousePosition)
{
	// �摜���ǂݍ��܂�Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (cursorImageHandle_ < 0)return false;


	// ��ʂ̃T�C�Y���擾
	int scWidth = Direct3D::screenWidth_;
	int scHeight = Direct3D::screenHeight_;

	// �}�E�X�J�[�\���̍��W���擾
	XMFLOAT2 imageSize = Image::GetSize(cursorImageHandle_); {
		// �摜�̃T�C�Y����ʃT�C�Y�ɍ��킹��

		imageSize.x = imageSize.x / scWidth;
		imageSize.y = imageSize.y / scHeight;
	}

	// �摜�̔����̃T�C�Y���擾
	float imageHalfWidth = imageSize.x / 2.f;
	float imageHalfHeight = imageSize.y / 2.f;

	// �摜�̒��S���W���擾
	XMFLOAT2 center = { transform_.position_.x,transform_.position_.y };

	// �摜�̊g�嗦���擾
	XMFLOAT2 scale = { transform_.scale_.x,transform_.scale_.y };

	// ����p�͈̔͂̒l���擾
	float top = center.y - (imageHalfHeight * 2.f * scale.y);       // �摜�̒��S�����ɉ摜�̍����̔����̋���
	float bottom = center.y + (imageHalfHeight * 2.f * scale.y);    // �摜�̒��S���牺�ɉ摜�̍����̔����̋���
	float left = center.x - (imageHalfWidth * 2.f * scale.x);       // �摜�̒��S���獶�ɉ摜�̕��̔����̋���
	float right = center.x + (imageHalfWidth * 2.f * scale.x);      // �摜�̒��S����E�ɉ摜�̕��̔����̋���

	// ����͈͓��Ƀ}�E�X�J�[�\���������Ă��邩�ǂ�����Ԃ�
	return (_mousePosition.x >= left && _mousePosition.x <= right && _mousePosition.y >= top && _mousePosition.y <= bottom);

}
