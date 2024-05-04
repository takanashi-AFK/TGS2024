#pragma once

// トランジションの識別子
enum TRANSITION_ID {
	TID_NONE,
	TID_BLACKOUT,
	TID_WHITEOUT,
	TID_SLIDEOUT,
	TID_MAX,
};

//前方宣言
class Sprite;

// シーン遷移を行う
namespace Transition
{
	//実行処理
	void Initialize();
	void Update();
	void Draw();
	void Release();

	/// <summary>
	/// トランジションを設定
	/// </summary>
	/// <param name="_type">トランジションID</param>
	/// <returns>トランジションを使わない(TID_NONE)場合はfalse</returns>
	bool SetTransition(TRANSITION_ID _type);

	/// <summary>
	/// トランジションの総再生時間を設定
	/// </summary>
	/// <param name="_time">再生時間(秒)</param>
	void SetTime(float _time);

	/// <summary>
	/// トランジションを開始
	/// </summary>
	void Start();

	/// <summary>
	/// トランジションがシーンの変更するタイミングに差し掛かったかどうかを返す
	/// </summary>
	/// <returns>差し掛かったらtrue</returns>
	bool IsChangePoint();

	/// <summary>
	/// トランジションが動いているかどうかを返す
	/// </summary>
	/// <returns>動作中ならtrue</returns>
	bool IsActive();

	/// <summary>
	/// 必要な変数を初期化する処理
	/// </summary>
	/// <returns>初期化できたらtrue</returns>
	bool InitParameter();
	////////// Toransition pattern //////////////////////////////
	
	/// <summary>
	/// 暗転
	/// </summary>
	void BlackOut();

	/// <summary>
	/// ホワイトアウト
	/// </summary>
	void WhiteOut();

};
