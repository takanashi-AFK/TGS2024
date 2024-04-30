#include "StageObject.h"
#include "Engine/ResourceManager/Model.h"

#define REFERENCE_XMFLOAT3(p) p.x,p.y,p.z

StageObject::StageObject(string _name, string _modelFilePath, GameObject* _parent)
	:GameObject(_parent,_name),modelFilePath_(_modelFilePath),modelHandle_(-1)
{
}

bool StageObject::AddComponent(Component* _comp)
{
	// エラー処理
	if (_comp == nullptr) 
	return false;

	// コンポーネントのvectorに追加する
	myComponents_.push_back(_comp); 
	return true;
}

bool StageObject::DeleteComponent(Component* _comp)
{
	// イテレータに、"myComponents_"内で探したいデータを登録
	auto it = std::find(myComponents_.begin(), myComponents_.end(), _comp);

	// イテレータがリストの最後まで到達したら関数終了
	if (it == myComponents_.end()) 
	return false;

	// イテレータのコンポーネントを消す
	myComponents_.erase(it); 
	return true;
}

void StageObject::Initialize()
{
	// モデルの読み込み
	modelHandle_ = Model::Load(modelFilePath_);
	assert(modelHandle_ >= 0);

	// 保有するコンポーネントの初期化処理
	for (auto comp : myComponents_)
		comp->ChildIntialize();
}

void StageObject::Update()
{
	// 保有するコンポーネントの更新処理
	for (auto comp : myComponents_)
		comp->ChildUpdate();
}

void StageObject::Draw()
{
	// モデルの描画
	Model::SetTransform(modelHandle_, transform_);
	Model::Draw(modelHandle_);
}

void StageObject::Release()
{
	// 保有するコンポーネントの開放処理
	for (auto comp : myComponents_) comp->ChildRelease();
	myComponents_.clear();

}

void StageObject::Save(json& _saveObj)
{
	// 自身の変形行列情報を保存
	_saveObj["position_"] = { REFERENCE_XMFLOAT3(transform_.position_) };
	_saveObj["rotate_"] = { REFERENCE_XMFLOAT3(transform_.rotate_) };
	_saveObj["scale_"] = { REFERENCE_XMFLOAT3(transform_.scale_)};
	
	// 自身のモデルのファイルパスを保存
	_saveObj["modelFilePath_"] = modelFilePath_;
	
	// 保有するコンポーネントを保存
	for (auto comp : myComponents_)comp->Save(_saveObj["myComponents_"][comp->GetType()]);
}

void StageObject::Load(json& _loadObj)
{
	// 自身の変形行列情報を読込
	transform_.position_ = { _loadObj["position_"][0].get<float>(),_loadObj["position_"][1].get<float>(), _loadObj["position_"][2].get<float>() };
	transform_.rotate_ = { _loadObj["rotate_"][0].get<float>(),_loadObj["rotate_"][1].get<float>(), _loadObj["rotate_"][2].get<float>() };
	transform_.scale_ = { _loadObj["scale_"][0].get<float>(),_loadObj["scale_"][1].get<float>(), _loadObj["scale_"][2].get<float>() };

	// 自身のモデルのファイルパスを保存
	modelFilePath_ = _loadObj["modelFilePath_"];

	// 自身のコンポーネントを読込
	for (auto it = _loadObj["myComponents_"].begin(); it != _loadObj["myComponents_"].end(); ++it) LoadComponent((ComponentType)std::stoi(it.key()),it.value());
}

StageObject* CreateStageObject(string _name, string _modelFilePath, GameObject* _parent)
{
	// オブジェクトのインスタンスを生成
	StageObject* obj = new StageObject(_name, _modelFilePath, _parent);
	
	// 初期化
	obj->Initialize();
	
	// 親オブジェクトのリストに追加
	if (_parent != nullptr)_parent->PushBackChild(obj);
	
	return obj;
}