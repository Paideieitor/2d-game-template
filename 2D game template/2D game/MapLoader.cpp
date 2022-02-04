#include "MapLoader.h"
#include "Game.h"
#include "Physics.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "AssetManager.h"

MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

bool MapLoader::SetUp(pugi::xml_node&)
{
	LoadMap("tiled/test_map.tmx");
	return true;
}

bool MapLoader::Update(float dt)
{
	return true;
}

bool MapLoader::CleanUp()
{
	return true;
}

void MapLoader::LoadMap(const char* mapName)
{
	pugi::xml_parse_result result = game->assets->LoadXML(document, mapName);

	pugi::xml_node physicsObjects = document.first_child().child("objectgroup");

	//std::cout << physicsObjects.attribute("name").as_string() << "\n";

	for (const auto& child : document.first_child().child("objectgroup")) {

		//BOX COLLIDER
		if (!child.child("polygon") && !child.child("ellipse")&& !child.child("point"))
		{
			child.attribute("x").as_int();
			fpoint position = { child.attribute("x").as_float(),-(child.attribute("y").as_float())};
			fpoint size = { child.attribute("width").as_float(),child.attribute("height").as_float() };
			BodyType type = BodyType::DYNAMIC;

			//CHECKING FOR PROPERTIES
			if (child.child("properties")) 
			{
				for (const auto& child : child.child("properties"))
				{
					if (!std::strcmp(child.attribute("name").as_string(),"static"))
					{
						if (child.attribute("value").as_bool()) 
						{
							type = BodyType::STATIC;
						}
					}
					
				}
			}
			/////////////////////////

			game->physics->AddPhysicsObject(new BoxCollider(position, size, 0.0f, type, 1.0f, 0.5f, 0.25f, false, false));
		}

		//CIRCLE COLLIDER
		if (child.child("ellipse")) 
		{
			fpoint position = { child.attribute("x").as_float(),-child.attribute("y").as_float() };
			float radius = child.attribute("width").as_float();

			game->physics->AddPhysicsObject(new CircleCollider(position,radius,0.0f,BodyType::DYNAMIC));
		}

		//POLYGON COLLIDER
		if (child.child("polygon"))
		{
			fpoint position = { child.attribute("x").as_float(),child.attribute("y").as_float() };

			//Thats rough, 
			//std::cout << child.child("polygon").attribute("points").as_string() << "\n";

		}

		//POINT
		if (child.child("point"))
		{

		}
	}
}
