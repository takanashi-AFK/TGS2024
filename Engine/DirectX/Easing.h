#pragma once
class Easing
{
public :

	enum class TYPE
	{
		STRAIGHT,
		SIN,
		COS
	};

	Easing(float v0,float v1,float addRatio);

	static float GetValue(float v0, float v1, float ratio , Easing::TYPE type);
	float GetValue(Easing::TYPE type);

	void SetValue0(float val);
	void SetValue1(float val);
	void SetValue(float v0, float v1);
	void SetRatio(float ratio , bool isReset);

private:

	float pile_;
	float ratio_ ;
	float val0_;
	float val1_;

	static float CalcStraight(float v0, float v1, float ratio);
	static float CalcSin(float v0, float v1, float ratio);
	static float CalcCos(float v0, float v1, float ratio);

	static float (*GetCalcFunction(Easing::TYPE type))(float, float, float);
};

