#include "UIButton.h"
#include "../../../Engine/ImGui/imgui.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/DirectX/Direct3D.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/Global.h"

using namespace FileManager;

UIButton::UIButton(string _name, GameObject* parent)
	: UIObject(_name, UIType::UI_BUTTON, parent)
{
}

void UIButton::Initialize()
{
}

void UIButton::Update()
{
}

void UIButton::Draw()
{
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
	if(loadObj.contains("imageFilePath_"))imageFilePath_ = loadObj["imageFilePath_"].get<string>();
}

void UIButton::DrawData()
{
    if (ImGui::TreeNode("imageFilePath_")) {

		ImGui::Text("imageFilePath_:%s", imageFilePath_.c_str());
		ImGui::SameLine();

        if (ImGui::SmallButton("...")) {
            //現在のカレントディレクトリを覚えておく
            char defaultCurrentDir[MAX_PATH];
            GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

            // 追加するオブジェクトのモデルファイルパスを設定
            {
                // 「ファイルを開く」ダイアログの設定用構造体を設定
                OPENFILENAME ofn; {
                    TCHAR szFile[MAX_PATH] = {}; // ファイル名を格納するバッファ
                    ZeroMemory(&ofn, sizeof(ofn)); // 構造体の初期化
                    ofn.lStructSize = sizeof(ofn); // 構造体のサイズ
                    ofn.lpstrFile = szFile; // ファイル名を格納するバッファ
                    ofn.lpstrFile[0] = '\0'; // 初期化
                    ofn.nMaxFile = sizeof(szFile); // ファイル名バッファのサイズ
                    ofn.lpstrFilter = TEXT("PNGファイル(*.fbx)\0*.png\0すべてのファイル(*.*)\0*.*\0"); // フィルター（FBXファイルのみ表示）
                    ofn.nFilterIndex = 1; // 初期選択するフィルター
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
                    ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
                }

                // ファイルを選択するダイアログの表示
                if (GetOpenFileName(&ofn) == TRUE) {
                    // ファイルパスを取得
                    imageFilePath_ = ofn.lpstrFile;

                    // カレントディレクトリからの相対パスを取得
                    imageFilePath_ = FileManager::GetAssetsRelativePath(imageFilePath_);

                    // 文字列内の"\\"を"/"に置換
                    FileManager::ReplaceBackslashes(imageFilePath_);

                    // ディレクトリを戻す
                    SetCurrentDirectory(defaultCurrentDir);

                    // 画像を読み込む
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

void UIButton::SetImage(string _imageFilePath)
{
	imageFilePath_ = _imageFilePath;
	imageHandle_ = Image::Load(_imageFilePath);
}

bool UIButton::OnClick()
{
    // マウスの座標を取得
    XMFLOAT2 mousePos = { Input::GetMousePosition().x,Input::GetMousePosition().y };

    // マウスの座標を画像の座標に変換
    ConvertToImageCoordinates(mousePos);

    //マウスのポジションが画像の領域に入っているかつ左クリックが押されたら
    return IsMouseOver(mousePos) && Input::IsMouseButtonDown(0);
}

bool UIButton::IsMouseOver(XMFLOAT2 _mousePosition)
{
	// マウスカーソルの座標を取得
	XMFLOAT2 imagesize = Image::GetSize(imageHandle_);
    float imageHalfWidth = imagesize.x /2;
    float imageHalfHeight = imagesize.y /2;

    XMFLOAT2 center = { transform_.position_.x,transform_.position_.y };

    float scaleX = transform_.scale_.x;
    float scaleY = transform_.scale_.y;

    float top = center.y - ((imageHalfHeight * 2) * scaleY);
    float bottom = center.y + ((imageHalfHeight * 2) * scaleY);
    float left = center.x - ((imageHalfWidth * 2) * scaleX);
    float right = center.x + ((imageHalfWidth * 2) * scaleX);

    // 判定範囲内にマウスカーソルが入っているかどうかを返す
    return (_mousePosition.x >= left && _mousePosition.x <= right && _mousePosition.y >= top && _mousePosition.y <= bottom);
	return false;
}

void UIButton::ConvertToImageCoordinates(XMFLOAT2& _position)
{
    int scWidth = Direct3D::screenWidth_;
    int scHeight = Direct3D::screenHeight_;

#ifdef _DEBUG
    scWidth = scWidth * 0.7;
    scHeight = scHeight * 0.7;
#endif // _DEBUG

    // マウスの座標を画像の座標に変換
    _position.x = (float)(_position.x * 2.0f) / (float)scWidth - 1.0f;
    _position.y = 1.0f - (float)(_position.y * 2.0f) / (float)scHeight;

    ImGui::Text("mousePos_ x:%f y:%f", _position.x, _position.y);
    ImGui::Text("screenWidth_:%d screenHeight_:%d", scWidth, scHeight);
}
