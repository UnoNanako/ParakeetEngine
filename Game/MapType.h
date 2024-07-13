#pragma once
#include <map>
#include <string>

//モデル、テクスチャの種類を管理するenum
enum MapType : unsigned int {
	NONE,
	GRASS,
	FLOOR1,
	FLOOR2,
	HOUSE1,
	HOUSE2,
	FENCE,
	BRIDGE,
	FLOWER,
	BUSH
};

extern std::map<MapType, std::string> kBlockModelPaths;