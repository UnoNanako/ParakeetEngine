#include "MapType.h"

std::map<MapType, std::string> kBlockModelPaths = {
	{MapType::NONE,""},
	{MapType::GRASS,"Resources/Models/Box1x1/Box1x1.gltf"},
	{MapType::FLOOR1,"Resources/Models/Floor1/Floor1.gltf"},
	{MapType::FLOOR2,"Resources/Models/Floor2/Floor2.gltf"},
	{MapType::HOUSE1,"Resources/Models/House1/House1.gltf"},
	{MapType::HOUSE2,"Resources/Models/House2/House2.obj"},
	{MapType::FENCE,"Resources/Models/Fence/Fence.gltf"},
	{MapType::BRIDGE,"Resources/Models/MiniBridge/MiniBridge.gltf"},
	{MapType::FLOWER,"Resources/Models/Box1x1_Flower/Box1x1_Flower.gltf"}
};