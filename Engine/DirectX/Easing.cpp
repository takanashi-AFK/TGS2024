#include "Easing.h"
#include <cstdlib>
#include<algorithm>
#include<numbers>
#include<cmath>
#include<utility>

float Easing::GetValue(float v0, float v1, float ratio, Easing::TYPE type)
{
	auto func = GetCalcFunction(type);
	return func(v0, v1, ratio);
}

Easing::Easing(float v0, float v1, float addRatio) :val0_(v0), val1_(v1), ratio_(addRatio), pile_(.0f), isStop(false)
{
}

auto Check = [](float v0, float v1, float& ratio)
	{
		ratio = std::clamp(ratio, .0f, 1.0f);
	};

float Easing::GetValue(Easing::TYPE type)
{
	auto func = GetCalcFunction(type);

	if(!isStop)	pile_ += ratio_;

	Check(.0f, 1.0f, pile_);
	return func(val0_, val1_, pile_);
}


float Easing::CalcStraight(float v0, float v1, float ratio)
{
	Check(v0, v1, ratio);

	float invRatio = 1 - ratio;

	return ((ratio * v0) + (invRatio * v1));
}

float Easing::CalcSin(float v0, float v1, float ratio)
{
	Check(v0, v1, ratio);

	ratio = std::sin((std::numbers::pi / 2) * ratio);
	float invRatio = 1 - ratio;

	return ((ratio * v0) + (invRatio * v1));
}

float Easing::CalcCos(float v0, float v1, float ratio)
{
	Check(v0, v1, ratio);

	ratio =1- std::cos((std::numbers::pi / 2) * ratio);
	float invRatio = 1 - ratio;

	return ((ratio * v0) + (invRatio * v1));
}

float(*Easing::GetCalcFunction(Easing::TYPE type))(float, float, float)
{
	switch (type)
	{
	case Easing::TYPE::STRAIGHT:	
		return Easing::CalcStraight;
	case Easing::TYPE::SIN:
		return Easing::CalcSin;
	case Easing::TYPE::COS:
		return Easing::CalcCos;
	default:
		return Easing::CalcStraight;
	}
}
