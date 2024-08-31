#include "Component_ShootAttack.h"

// インクルード
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../Bullet.h"
#include "../../Stage.h"
#include "../../../../../Engine/Global.h"
using namespace FileManager;

Component_ShootAttack::Component_ShootAttack(string _name, StageObject* _holder, Component* _parent):
	Component_Attack(_holder, _name, ShootAttack,_parent),shootingSpeed_(),shootingDirection_()
{
}

void Component_ShootAttack::Initialize()
{
}

void Component_ShootAttack::Update()
{	
	if (isActive_ == false)return;

	// 撃ち放つプレハブを生成
	Bullet* bulletPrefab = CreateBullet(holder_->GetParent(), data_);

	bulletPrefab->SetShooter(holder_);
	
	// 撃ち放つ速度を設定
	bulletPrefab->SetSpeed(shootingSpeed_);

	// 撃ち放つ方向を設定
	bulletPrefab->SetDirection(shootingDirection_);

	// 撃ち放つ位置を設定
	if (isShootPositionSet_ == true)bulletPrefab->SetPosition(shootingPosition_);
	else bulletPrefab->SetPosition(holder_->GetPosition());

	// 撃ち放つ
	bulletPrefab->Execute();
	
	// 攻撃を停止
	Stop();
}

void Component_ShootAttack::Release()
{
}

void Component_ShootAttack::Save(json& _saveObj)
{
	// 速度と方向の保存
	_saveObj["shootingSpeed_"] = shootingSpeed_;
	_saveObj["shootingDirection_"] = { REFERENCE_XMVECTOR3(shootingDirection_)};

	// エフェクトデータの保存
	_saveObj["EffectData"] = {
		{"name",data_.name},
		{"path",data_.path}
	};
}

void Component_ShootAttack::Load(json& _loadObj)
{
	// 速度と方向の読み込み
	if (_loadObj.contains("shootingSpeed_"))shootingSpeed_ = _loadObj["shootingSpeed_"];
	if (_loadObj.contains("shootingDirection_"))shootingDirection_ = XMVectorSet(_loadObj["shootingDirection_"][0], _loadObj["shootingDirection_"][1],_loadObj["shootingDirection_"][2],0);

	// エフェクトデータの読み込み
	if (_loadObj.contains("EffectData")) {
		data_.name = _loadObj["EffectData"]["name"];
		data_.path = _loadObj["EffectData"]["path"];
	}
}

void Component_ShootAttack::DrawData()
{
	// 速度の設定
	ImGui::DragFloat("Speed", &shootingSpeed_, 0.1f,0.f);
	
	// 方向の設定
	ImGui::DragFloat3("Direction", (float*)&shootingDirection_, 0.1f);

	// 攻撃ボタン
	if (ImGui::Button("Execute"))this->Execute();

	// エフェクトデータの表示
	if(ImGui::TreeNode("Effect Data")) {

		// エフェクトの名前
		ImGui::Text("Name: %s", data_.name.c_str());
		// エフェクトのパス
		ImGui::Text("Path: %s", data_.path.c_str());

		// エフェクトの設定
		if (ImGui::Button("Set Effect")){
			//現在のカレントディレクトリを覚えておく
			char defaultCurrentDir[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

			// エフェクトのファイルパスを設定
			{
				// 「ファイルを開く」ダイアログの設定用構造体を設定
				OPENFILENAME ofn; {
					TCHAR szFile[MAX_PATH] = {}; // ファイル名を格納するバッファ
					ZeroMemory(&ofn, sizeof(ofn)); // 構造体の初期化
					ofn.lStructSize = sizeof(ofn); // 構造体のサイズ
					ofn.lpstrFile = szFile; // ファイル名を格納するバッファ
					ofn.lpstrFile[0] = '\0'; // 初期化
					ofn.nMaxFile = sizeof(szFile); // ファイル名バッファのサイズ
					ofn.lpstrFilter = TEXT("FBXファイル(*.efk)\0*.efk\0すべてのファイル(*.*)\0*.*\0"); // フィルター（efkファイルのみ表示）
					ofn.nFilterIndex = 1; // 初期選択するフィルター
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
					ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
				}

				// ファイルを選択するダイアログの表示
				if (GetOpenFileName(&ofn) == TRUE) {
					// ファイルパスを取得
					data_.path = ofn.lpstrFile;

					// カレントディレクトリからの相対パスを取得
					data_.path = GetAssetsRelativePath(data_.path);

					// 文字列内の"\\"を"/"に置換
					ReplaceBackslashes(data_.path);

					// ディレクトリを戻す
					SetCurrentDirectory(defaultCurrentDir);
				}
				else {
					return;
				}
			}

			// エフェクトの名前を設定
			data_.name = GetFileNameWithoutExtension(data_.path);
		}
		ImGui::TreePop();
	}
}
