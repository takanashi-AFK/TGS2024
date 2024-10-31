#pragma once
#include<string>
#include "../Json/JsonReader.h"

struct EasingInformation
{
	inline EasingInformation() :addRatio_{}, pile_{} {};
	virtual void Load(json& file) = 0;
	virtual void Save(json& file) = 0;

	float addRatio_;
	float pile_;

};