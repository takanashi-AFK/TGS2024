#pragma once

// インクルードディレクティブ
#include <string>
#include <vector>
#include "../../../../../../Engine/Json/JsonReader.h"

// usingディレクティブ
using std::string;
using std::vector;

// 前夫宣言
class StageObject;

// ステートタイプ
enum StateType
{
	Idle,
	Walk,
	None
};

class State
{
protected:
	string name_;	// ステート名(ID)
	StateType type_;	// ステートタイプ
	StageObject* holder_;	// ステートを持つオブジェクト

	struct ModelData {
		string filePath;
		int modelHandle;

		int animFrameMax;
		int animFrameStart;
		float animSpeed;

		void Load();
	};
	vector<ModelData> modelDataList_;	// モデルデータリスト

public:
	// 更新
	State(string _name,StateType _type,StageObject* _holder) :name_(_name),type_(_type),holder_(_holder){};
	
	// 初期化
	virtual void Initialize() = 0;
	
	// 開始
	virtual void Start() = 0;
	
	// 更新
	virtual void Update() = 0;

	virtual void Save(json& _saveObj){}
	virtual void Load(json& _loadObj){}
	void DrawData(){}

	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);
	void ChildDrawData();

	string GetName() const{ return name_; }
	StateType GetType() const { return type_; }
	StageObject* GetHolder() const { return holder_; }

	void AddModelData(string _filePath,int _animFrameMax,int _animFrameStart,float _animSpeed);	

private:
	bool isAddModelWindowOpen_;	// モデル追加ウィンドウ表示フラグ
	void DrawAddModelWindow();
};

State* CreateState(string _name,StateType _type,StageObject* _holder);
string StateTypeToString(StateType _type);