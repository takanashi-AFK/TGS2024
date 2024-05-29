#pragma once
#include "../Component.h"

class Component_CircleRangeDetector : public Component
{
private:
	
	StageObject* target_;	// ÎÛIuWFNg
	float radius_;			// ¼a
	bool isContains_;		// ½è»ètO

public:
	/// <summary>
	/// RXgN^
	/// </summary>
	/// <param name="_holder">ÛLÒ</param>
	Component_CircleRangeDetector(StageObject* _holder);

	/// <summary>
	/// ú»
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// XV
	/// </summary>
	void Update() override;

	/// <summary>
	/// ðú
	/// </summary>
	void Release() override;

	/// <summary>
	/// Û¶
	/// </summary>
	/// <param name="_saveObj">Û¶îñ</param>
	void Save(json& _saveObj) override;

	/// <summary>
	/// Ç
	/// </summary>
	/// <param name="_loadObj">Çîñ</param>
	void Load(json& _loadObj) override;

	/// <summary>
	/// ImGuipl\¦
	/// </summary>
	void DrawData() override;

// setter
	
	/// <param name="_radius">{õÍÍÌ¼a</param>
	void SetRadius(float _radius) { radius_ = _radius; }

	/// <param name="_target">{õÎÛ</param>
	void SetTarget(StageObject* _target) { target_ = _target; }

// getter

	/// <returns>{õÍÍÌ¼a</returns>
	float GetRadius() { return radius_; }

	/// <returns>{õÎÛ</returns>
	StageObject* GetTarget() { return target_; }

	/// <returns>{õÎÛª{õÍÍàÉ¢½çtrue</returns>
	bool IsContains();

};

