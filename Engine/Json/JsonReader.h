#pragma once
#include "json.hpp"
#include <string>
using std::string;
using json = nlohmann::json;

// É}ÉNÉç
#define JFLOAT3(p)  p[0].get<float>(), p[1].get<float>(), p[2].get<float>() 

namespace JsonReader
{
	bool Load(string fileName, json& _data);

	bool Save(string fileName, json& _data);
	
};

