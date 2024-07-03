#include "MapType.h"

std::map<MapType, std::string> kBlockModelPaths = {
	{MapType::NONE,""},
	{MapType::FLOOR1,"Resources/Models/Box1x1/Box1x1.gltf"},
	{MapType::FLOOR2,"Resources/Models/Box2x2/Box2x2.gltf"},
	{MapType::GRASS,"Resources/Models/Grass/Grass.obj"},
	{MapType::HOUSE1,"Resources/Models/House1/House1.obj"},
	{MapType::HOUSE2,"Resources/Models/House2/House2.obj"}
};