
#pragma once
#include <string>
class StageObject;
using std::string;
// 状態の動作 基底クラス
class State
{
protected:
	string name_;  // 状態名
	StageObject* holder_;  // 保有者
public:
	State(string _name, StageObject* _holder) :name_(_name), holder_(_holder) {}
	virtual void Initialize() = 0;  // 初期化
	virtual void Start() = 0;       // 開始
	virtual void Update() = 0;      // 更新
	virtual void SetModel(string _filePath,int _animSpeed, int _animMaxFrame,int _animStartFrame) = 0;    // モデルの設定
	string GetName() { return name_; }
};