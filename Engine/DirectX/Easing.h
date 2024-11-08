#pragma once
#include<string>

class Easing
{
public :

	enum class TYPE
	{
		STRAIGHT,
		SIN,
		COS,
		EaseIO,

		AMOUNT
	};

	Easing(float v0,float v1,float addRatio);

	static float GetValue(float v0, float v1, float ratio , Easing::TYPE type);
	float GetValue(Easing::TYPE type);

	float pile_;
	float ratio_;
	float val0_;
	float val1_;
	bool isStop;

	static std::string GetEnumName(Easing::TYPE t);

private:

	static float CalcStraight(float v0, float v1, float ratio);
	static float CalcSin(float v0, float v1, float ratio);
	static float CalcCos(float v0, float v1, float ratio);
	static float CalsEaseIO(float v0, float v1, float ratio);

	static float (*GetCalcFunction(Easing::TYPE type))(float, float, float);
};

