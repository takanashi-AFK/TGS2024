#include "State.h"
#include "../../../../../Engine/ImGui/imgui.h"
#include "../../../../../Engine/Global.h"
using namespace FileManager;

#include "PlayerState/State_Idle.h"
#include "PlayerState/PlayerState_Walk.h"

void State::ChildInitialize()
{
	Initialize();
	for (auto& modelData : modelDatas_) modelData.Load();
}


void State::ChildSave(json& _saveObj)
{
    _saveObj["modelData"] = json::array();
    for (int i = 0; i < modelDatas_.size(); i++) {
        json data;
        data["filePath"] = modelDatas_[i].filePath;
        data["animSpeed"] = modelDatas_[i].animSpeed;
        data["animMaxFrame"] = modelDatas_[i].animMaxFrame;
        data["animStartFrame"] = modelDatas_[i].animStartFrame;
        _saveObj["modelData"].push_back(data);
    }
    _saveObj["name_"] = name_;
    _saveObj["stateType_"] = stateType_;

}

void State::ChildLoad(json& _loadObj)
{
    if (_loadObj.find("modelData") != _loadObj.end() && _loadObj["modelData"].is_array()) {
        modelDatas_.clear();
        for (const auto& data : _loadObj["modelData"]) {
            ModelData modelData;
            if (_loadObj.contains("filePath")) modelData.filePath = data["filePath"];
            if (_loadObj.contains("animSpeed"))modelData.animSpeed = data["animSpeed"];
            if (_loadObj.contains("animMaxFrame"))modelData.animMaxFrame = data["animMaxFrame"];
            if (_loadObj.contains("animStartFrame"))modelData.animStartFrame = data["animStartFrame"];
            modelDatas_.push_back(modelData);
        }
    }

    if (_loadObj.contains("name_"))name_ = _loadObj["name_"];
    if (_loadObj.contains("stateType_"))stateType_ = (STATE_TYPE)_loadObj["stateType_"];

}

void State::DrawAddModelWindow()
{
    if (isAddModelWindowOpen_) {
        // ImGui::Begin の戻り値でウィンドウが開いているか確認
        if (ImGui::Begin("Add Model", &isAddModelWindowOpen_)) {
            static string filePath{};

            static int speed, max, start = 0;
            if (ImGui::Button("...")) {
                // 現在のカレントディレクトリを覚えておく
                char defaultCurrentDir[MAX_PATH];
                GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

                // 読み込むファイルのパスを取得
                {
                    OPENFILENAME ofn;
                    TCHAR szFile[MAX_PATH] = {};
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.lpstrFile = szFile;
                    ofn.lpstrFile[0] = '\0';
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrFilter = TEXT("FBXファイル(*.fbx)\0*.fbx\0すべてのファイル(*.*)\0*.*\0");
                    ofn.nFilterIndex = 1;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                    ofn.lpstrInitialDir = TEXT(".");

                    if (GetOpenFileName(&ofn) == TRUE) {
                        filePath = ofn.lpstrFile;
                        filePath = GetAssetsRelativePath(filePath);
                        ReplaceBackslashes(filePath);
                        SetCurrentDirectory(defaultCurrentDir);
                    }
                    else {
                        return;
                    }
                }
            }

            ModelData modelData;
            ImGui::DragInt("Animation Speed", &speed);
            ImGui::DragInt("Animation Max Frame", &max);
            ImGui::DragInt("Animation Start Frame", &start);
            ImGui::Text("Model :%s",filePath.c_str());

            if (filePath == "") {
                ImGui::Text("Please Set FilePath");
            }
            else {
                modelData.filePath = filePath;
				modelData.animSpeed = speed;
				modelData.animMaxFrame = max;
				modelData.animStartFrame = start;
                if (ImGui::SmallButton("Confirm")) {

                    modelDatas_.push_back(modelData);
                    
                    modelData.Load();
                    isAddModelWindowOpen_ = false; // 確定ボタンでウィンドウを閉じる
                }
            }
        }
        ImGui::End(); // ウィンドウを閉じる
    }
}

State* CreateState(string _name, STATE_TYPE _type)
{
    switch (_type)
    {
    case Idle: return new State_Idle(_name);
	case Walk: return new PlayerState_Walk(_name);
    default: return nullptr;
    }
}

string StateTypeToString(STATE_TYPE _type)
{
    switch (_type)
    {
    case Idle: return "Idle";
    case Walk: return "Walk";
    default: return "None";
    }
}