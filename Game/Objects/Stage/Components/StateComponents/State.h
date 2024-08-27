
#pragma once
#include <string>
#include "../../../../../Engine/ResourceManager/Model.h"
#include "../../../../../Engine/Json/JsonReader.h"
class StageObject;
using std::string;
// 状態の動作 基底クラス
// ステートタイプ
enum STATE_TYPE
{
	Idle,
	Walk,
	None
};

struct ModelData {
	int modelHandle;
	string filePath;
	int animSpeed;
	int animMaxFrame;
	int animStartFrame;
	void Load() {
		modelHandle = Model::Load(filePath);
		assert(modelHandle >= -1);
		Model::SetAnimFrame(modelHandle, animSpeed,animMaxFrame,animStartFrame);
	}
};

class State
{

private:
	bool isAddModelWindowOpen_;
protected:
	string name_;  // 状態名
	STATE_TYPE type_;  // 状態タイプ
	StageObject* holder_;  // 保有者
	std::vector<ModelData> modelDatas_;
public:
	State(string _name, StageObject* _holder) :name_(_name), holder_(_holder) {}
	virtual void Initialize() = 0;  // 初期化
	virtual void Start() = 0;       // 開始
	virtual void Update() = 0;      // 更新
	void Save(json &_saveObj);
	void Load(json &_loadObj);
	void AddModel() { isAddModelWindowOpen_ = true; }
	void DrawAddModelWindow();
	void ChildInitialize();
	string GetName() { return name_; }
	std::vector<ModelData> GetModelDatas() { return modelDatas_; }	

	bool operator==(const State& other) const {
		return name_ == other.name_;
	}
};
State* CreateState(string _name, STATE_TYPE _type);
string StateTypeToString(STATE_TYPE _type);