#pragma once
#include "../GameObject/GameObject.h"
#include "../DirectX/BillBoard.h"
#include <list>


//エミッター（パーティクルの発生源）を作る時のデータ一覧
//Start関数の引数として使う
struct EmitterData
{
	std::string textureFileName;	//画像ファイル名
	XMFLOAT3 position;		//位置
	XMFLOAT3 positionRnd;	//位置の誤差
	XMFLOAT3 direction;		//パーティクルの移動方向
	XMFLOAT3 directionRnd;	//移動方向の誤差（各軸の角度）
	float	 speed;			//1フレームの速度
	float	 speedRnd;		//速度誤差（0～1）
	float	 accel;			//加速度
	float	 gravity;		//重力
	XMFLOAT4 color;			//色（RGBA 0～1）
	XMFLOAT4 deltaColor;	//色の変化量
	XMFLOAT3 rotate;		//各軸での角度
	XMFLOAT3 rotateRnd;		//角度誤差
	XMFLOAT3 spin;			//回転速度
	XMFLOAT2 size;			//サイズ
	XMFLOAT2 sizeRnd;		//サイズ誤差（0～1）
	XMFLOAT2 scale;			//1フレームの拡大率
	DWORD	 lifeTime;		//パーティクルの寿命（フレーム数）
	DWORD	 delay;			//何フレームおきにパーティクルを発生させるか
	DWORD	 number;		//1度に出すパーティクル量
	bool	 isBillBoard;	//ビルボードかどうか

	//初期化
	EmitterData()
	{
		textureFileName = "defaultParticle.png";
		position = positionRnd = directionRnd = rotate = rotateRnd = spin = XMFLOAT3(0, 0, 0);
		direction = XMFLOAT3(0, 1, 0);
		speed = 0.1f;
		speedRnd = 0.0f;
		accel = 1.0f;
		gravity = 0.0f;
		color = XMFLOAT4(1, 1, 1, 1);
		deltaColor = XMFLOAT4(0, 0, 0, 0);
		size = scale = XMFLOAT2(1.0f, 1.0f);
		sizeRnd = XMFLOAT2(0.0f, 0.0f);
		lifeTime = 30;
		delay = 10;
		number = 1;
		isBillBoard = true;
	}
};



//エフェクトを管理するクラス
namespace VFX
{
	//エミッター（パーティクルの噴射口）
	struct Emitter
	{
		EmitterData data ;		//作成時に指定されたデータ
		int handle = -1;		//ハンドル（番号）
		DWORD frameCount = 0;	//開始してからのフレーム数
		BillBoard* pBillBoard = nullptr;	//パーティクルに使うポリゴン
		bool isDead = false;	//削除対象かどうか（実際はパーティクルが全部消えるまでエミッターは消えない）
		int particleNum = 0;	//このエミッターから出た現存パーティクルの数
	};


	//パーティクルの変化するデータ
	struct DynamicData
	{
		XMFLOAT3 position;	//位置
		XMFLOAT3 rotation;	//回転
		XMFLOAT2 scale;		//サイズ
		XMFLOAT4 color;		//色
	};

	//パーティクル1粒のデータ
	struct Particle
	{
		DynamicData now;	//現在の情報
		DynamicData delta;	//1フレームの変化量
		DWORD life;			//残り寿命
		float accel;		//加速度
		float gravity;		//重力
		Emitter* pEmitter;	//発生元エミッタ
	};

	



	//発生中のパーティクルを更新
	void ParticleUpdate();

	//エミッタの更新（タイミング次第でパーティクルを発生させる）
	void EmitterUpdate();

	//パーティクル生成
	//引数：emitter	エミッター情報
	void CreateParticle(std::list<VFX::Emitter*>::iterator& emitter);


	//更新
	void Update();

	//描画
	void Draw();

	//開放
	void Release();


	//エミッタを作成（エフェクト開始）
	//引数：emitterData	各種情報
	//戻値：エフェクト（エミッタ）の番号
	int Start(EmitterData emitterData);

	//エミッタを削除（エフェクト終了）
	//引数：handle	エフェクトの番号
	void End(int handle);
};

