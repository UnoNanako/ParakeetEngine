#include "MapType.h"

std::map<MapType, std::string> kBlockModelPaths = {
	{MapType::NONE,""},
	{MapType::GRASS,"Resources/Models/Box1x1/Box1x1.gltf"},
	{MapType::FLOOR1,"Resources/Models/Floor1/Floor1.gltf"},
	{MapType::FLOOR2,"Resources/Models/Grass/Grass.obj"},
	{MapType::HOUSE1,"Resources/Models/House1/House1.obj"},
	{MapType::HOUSE2,"Resources/Models/House2/House2.obj"},
	{MapType::FENCE,"Resources/Models/Fence/Fence.gltf"},
	{MapType::BRIDGE,"Resources/Models/MiniBridge/MiniBridge.obj"},
	{MapType::FLOWER,"Resources/Models/Box1x1_Flower/Box1x1_Flower.gltf"}
};