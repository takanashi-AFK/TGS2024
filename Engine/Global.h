#pragma once
#include "DirectX/Direct3D.h"

// ＝＝ マクロ ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// XMFLOAT3型の変数をコンマ区切りで表示するマクロ
#define REFERENCE_XMFLOAT3(p) p.x,p.y,p.z 

// ＝＝ 定数 ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //

const float FPS = 60.0f;	// フレームレート


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
