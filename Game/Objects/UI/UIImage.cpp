#include "UIImage.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/ImGui/imgui.h"

UIImage::UIImage(string _name, UIObject* parent, int _layerNum)
	:UIObject(_name, UI_IMAGE, parent,_layerNum), imageHandle_(-1), imageFilePath_(""), isDraw_(true)
{
}

void UIImage::Initialize()
{
}

void UIImage::Update()
{
}

void UIImage::Draw()
{
	// �摜���ǂݍ��܂�Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (imageHandle_ < 0 || isDraw_ == false )return;
    Image::SetTransform(imageHandle_, transform_);
    Image::Draw(imageHandle_);
}

void UIImage::Release()
{
}

void UIImage::Save(json& saveObj)
{
	saveObj["imageFilePath_"] = imageFilePath_;
}

void UIImage::Load(json& loadObj)
{
	if (loadObj.contains("imageFilePath_")) {
		imageFilePath_ = loadObj["imageFilePath_"].get<string>();
		SetImage(imageFilePath_);
	}
}

void UIImage::DrawData()
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
}

void UIImage::SetImage(string _imageFilePath)
{
	imageFilePath_ = _imageFilePath;
	imageHandle_ = Image::Load(_imageFilePath);
	assert(imageHandle_ >= 0);
}
