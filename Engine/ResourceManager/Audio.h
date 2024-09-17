#pragma once
#include <string>

//-----------------------------------------------------------
//サウンドを管理する（XAudio使用）
//-----------------------------------------------------------
namespace Audio
{
	/// <summary> 初期化 </summary>
	void Initialize();

	//すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す
	/// <summary> 読込 </summary>
	/// <param name="fileName">ファイル名</param>
	/// <param name="isLoop">ループ再生させたいならtrue</param>
	/// <param name="svNum">同時に鳴らす最大数（省略可）</param>
	/// <returns>そのデータに割り当てられた番号</returns>
	int Load(std::string fileName, bool isLoop = false, int svNum = 1);

	/// <summary> 再生 </summary>
	void Play(int ID);
	void Play(int ID,float volume);

	/// <summary> 停止 </summary>
	void Stop(int ID);

	/// <summary> 解放 </summary>
	void Release();

	/// <summary> 全ての解放 </summary>
	void AllRelease();

	/// <summary> ボリューム設定 </summary>
	void SetVolume(int ID, float volume);

	/// <summary> 再生速度設定 </summary>
	void SetPlaybackSpeed(int ID, float speed);
};