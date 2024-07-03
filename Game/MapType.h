#pragma once
#include <map>
#include <string>

//モデル、テクスチャの種類を管理するenum
enum MapType : unsigned int {
	NONE,
	FLOOR1,
	FLOOR2,
	GRASS,
	HOUSE1,
	HOUSE2,
};

extern std::map<MapType, std::string> kBlockModelPaths;