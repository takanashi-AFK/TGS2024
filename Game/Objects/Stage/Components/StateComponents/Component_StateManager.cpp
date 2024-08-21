#include "Component_StateManager.h"
#include "../../StageObject.h"
void Component_StateManager::Initialize()
{
    // 各状態の初期化を行う
    for (auto state : stateList_)state.second->Initialize();
}

void Component_StateManager::Update()
{
    // 状態の変更処理 //////
    {
        // 状態が遷移可能な場合遷移する
        if (count_ >= changeLimit_) {
            currentStateKey_ = changeStateKey_;  // 変更
            stateList_[currentStateKey_]->Start();
        }
        count_ += 1 / FPS;  // カウントを進める
    }

    // キーで指定された状態が存在するかどうかを確認し、現在の状態の更新処理を実行
    if (stateList_.find(currentStateKey_) != stateList_.end()) stateList_[currentStateKey_]->Update();

}

void Component_StateManager::DrawData()
{
    // 状態追加用ウィンドウ
    if (g_isAddStateWindowOpen)DrawAddStateWindow(this);

    // 追加されている状態をツリーノードで表示
    if (ImGui::TreeNode("State list")) {

        ImGui::SameLine();
        // 状態を追加
        if (ImGui::SmallButton("Add State"))g_isAddStateWindowOpen = true;

        ImGui::TreePop();
    }
}


// 状態を追加する際に表示するImGuiウィンドウ表示用関数
void Component_StateManager::DrawAddStateWindow(Component_StateManager * _stateManager)
{
    // 名前を設定
    static char inputText[256] = {}; // バッファを定義
    ImGui::InputText("Enter Here State Name", inputText, sizeof(inputText));

    // モデルのファイルパスを取得し設定
	string modelFilePath = holder_->GetModelFilePath();
    // モデルのアニメーション情報（速度/最大フレーム/開始フレーム）を設定
    float animSpeed = /*..取得..*/; 
    float animMaxFrame = /*..取得..*/;
    float animStartFrame = /*..取得..*/;

    // 上記の情報を基に状態インスタンスを作成
    State* state = new State(inputText, holder_);
    state->SetModel(modelFilePath, animSpeed, animMaxFrame, animStartFrame);

    // 状態を追加
    _stateManager->AddState(state);
    g_isAddStateWindowOpen = false;
}