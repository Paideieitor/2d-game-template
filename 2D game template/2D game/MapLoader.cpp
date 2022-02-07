#include "MapLoader.h"
#include "Game.h"
#include "Physics.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"
#include "AssetManager.h"
#include "BOX2D/Box2D/Box2D.h"
#include <string>

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
			std::string polygon = child.child("polygon").attribute("points").as_string();
		
			int polygonCounter = 0;

			for (int i = 0; i < polygon.length(); i++) {
				if (polygon.at(i) == ',')
				{
					polygonCounter++;
				}
			}

			const int size = polygonCounter;
			
			b2Vec2 vertices[20];
			int numberOne = 0;
			int numberTwo = 0;
			int iterationNum = 0;
			std::string numberHelper;

			for (int i = 0; i < polygon.length(); i++) {

				//Check if last number
				if (i == polygon.length() - 1)
				{
					numberHelper.push_back(polygon.at(i));
					numberTwo = std::stoi(numberHelper);
					numberHelper = "";
					vertices[iterationNum] = b2Vec2(numberOne + position.x, numberTwo - position.y);
					numberTwo = 0;
					numberOne = 0;
					iterationNum++;
				}

				if (polygon.at(i) == ' ') 
				{
					numberTwo = std::stoi(numberHelper);
					numberHelper = "";
					vertices[iterationNum] = b2Vec2(numberOne + position.x, numberTwo - position.y);
					numberTwo = 0;
					numberOne = 0;
					iterationNum++;
				}

				if (polygon.at(i) == ',')
				{
					numberOne = std::stoi(numberHelper);
					numberHelper = "";
					
				}

				//if its a number
				if (polygon.at(i) != ' ' && polygon.at(i) != ',' && i != polygon.length() - 1)
				{
					numberHelper.push_back(polygon.at(i));
				}
			}

			for (int i = 0; i < polygonCounter; i++) 
			{
				std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
			}

			game->physics->AddPhysicsObject( new PolygonCollider(position, polygonCounter,vertices,0.0f,BodyType::STATIC,1.0f,1.0f,0.0f,false));
		}

		//POINT
		if (child.child("point"))
		{

		}
	}
}
