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

	// マウスの座標を取得
	XMFLOAT2 mousePos = { Input::GetMousePosition().x,Input::GetMousePosition().y };

	// マウスの座標を画像の座標に変換
	ConvertToImageCoordinates(mousePos);

	if (IsMouseOver(mousePos)){
		if (Input::IsMouseButton(0)){
			// マウスの座標が画像の範囲内にあるか
			if (IsMouseOver(mousePos)){

				// 左右にぐりぐりできるように
				cursorTransform_.position_.x = mousePos.x /2;

				//n以上だったらなんとか
			}
		}
	}
}

void UIDragBar::Draw()
{
	// 画像が読み込まれていない場合は処理を行わない
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
		//現在のカレントディレクトリを覚えておく
		char currentDir[256];
		GetCurrentDirectoryA(256, currentDir);

		//ファイルパスを取得
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

		//カレントディレクトリを元に戻す
		SetCurrentDirectoryA(currentDir);

		//ファイルパスが取得できていたら画像を読み込む
		if (filePath[0] != '\0') {
			barImageFilePath_ = filePath;
		}

	}
	if (ImGui::Button("SetCursorIMG")) {
		//現在のカレントディレクトリを覚えておく
		char currentDir[256];
		GetCurrentDirectoryA(256, currentDir);

		//ファイルパスを取得
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

		//カレントディレクトリを元に戻す
		SetCurrentDirectoryA(currentDir);

		//ファイルパスが取得できていたら画像を読み込む
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

	// マウスの座標を画像の座標に変換
	_position.x = (float)(_position.x * 2.0f) / (float)scWidth - 1.0f;
	_position.y = 1.0f - (float)(_position.y * 2.0f) / (float)scHeight;

}

bool UIDragBar::IsMouseOver(XMFLOAT2 _mousePosition)
{
	// 画像が読み込まれていない場合は処理を行わない
	if (cursorImageHandle_ < 0)return false;


	// 画面のサイズを取得
	int scWidth = Direct3D::screenWidth_;
	int scHeight = Direct3D::screenHeight_;

	// マウスカーソルの座標を取得
	XMFLOAT2 imageSize = Image::GetSize(cursorImageHandle_); {
		// 画像のサイズを画面サイズに合わせる

		imageSize.x = imageSize.x / scWidth;
		imageSize.y = imageSize.y / scHeight;
	}

	// 画像の半分のサイズを取得
	float imageHalfWidth = imageSize.x / 2.f;
	float imageHalfHeight = imageSize.y / 2.f;

	// 画像の中心座標を取得
	XMFLOAT2 center = { transform_.position_.x,transform_.position_.y };

	// 画像の拡大率を取得
	XMFLOAT2 scale = { transform_.scale_.x,transform_.scale_.y };

	// 判定用の範囲の値を取得
	float top = center.y - (imageHalfHeight * 2.f * scale.y);       // 画像の中心から上に画像の高さの半分の距離
	float bottom = center.y + (imageHalfHeight * 2.f * scale.y);    // 画像の中心から下に画像の高さの半分の距離
	float left = center.x - (imageHalfWidth * 2.f * scale.x);       // 画像の中心から左に画像の幅の半分の距離
	float right = center.x + (imageHalfWidth * 2.f * scale.x);      // 画像の中心から右に画像の幅の半分の距離

	// 判定範囲内にマウスカーソルが入っているかどうかを返す
	return (_mousePosition.x >= left && _mousePosition.x <= right && _mousePosition.y >= top && _mousePosition.y <= bottom);

}
