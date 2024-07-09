#pragma once
#include "UIObject.h"

class UIButton : public UIObject
{
	string imageFilePath_;
	int imageHandle_;

	bool isMove_;
	XMFLOAT3 startPosition_;
	float distance_;
	XMVECTOR direction_;
	string easeFunc_;
	float rate_;				// イージングの割合
public:
	UIButton(string _name, GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Save(json& saveObj) override;
	void Load(json& loadObj) override;
	void DrawData() override;

	void SetImage(string _imageFilePath);
	bool OnClick();

	void Move(float _distance, XMVECTOR _direction,string _easeFunc);
	bool IsMove() { return isMove_; }
private:
	bool IsMouseOver(XMFLOAT2 _position);
	void ConvertToImageCoordinates(XMFLOAT2& _position);

};

