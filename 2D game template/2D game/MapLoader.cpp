#include "MapLoader.h"
#include "Game.h"
#include "Physics.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "EntityManager.h"
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

void MapLoader::LoadMap(const char* mapName)
{
	pugi::xml_parse_result result = game->assets->LoadXML(map, mapName);

	pugi::xml_node physicsObjects = map.first_child().child("objectgroup");

	//std::cout << physicsObjects.attribute("name").as_string() << "\n";

	for (const auto& child : map.first_child().child("objectgroup")) {

		//BOX COLLIDER
		if (!child.child("polygon") && !child.child("ellipse")&& !child.child("point"))
		{
			child.attribute("x").as_int();
			fpoint position = { child.attribute("x").as_float(),-(child.attribute("y").as_float())};
			fpoint size = { child.attribute("width").as_float(),child.attribute("height").as_float() };
			BodyType type = BodyType::DYNAMIC;
			bool isSensor = false;
			const char* tag = "none";

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

					if (!std::strcmp(child.attribute("name").as_string(), "static"))
					{
						if (child.attribute("value").as_bool())
						{
							type = BodyType::STATIC;
						}
					}

					if (!std::strcmp(child.attribute("name").as_string(), "sensor"))
					{
						isSensor = child.attribute("value").as_bool();
					}

					if (!std::strcmp(child.attribute("name").as_string(), "tag"))
					{
						tag = child.attribute("value").as_string();
					}
					
				}
			}
			/////////////////////////
			if(!std::strcmp(tag, "block"))
			{
				game->entities->AddRock("Rock",position,size,0.0f, boxesFrition);
			}
			else
			{
				game->physics->AddPhysicsObject(new BoxCollider(position, size, 0.0f, type, 3.0f, objectFriction, 0.0f, false, isSensor, tag));
			}
				
				
		}

		//CIRCLE COLLIDER
		if (child.child("ellipse")) 
		{
			fpoint position = { child.attribute("x").as_float(),-child.attribute("y").as_float() };
			float radius = child.attribute("width").as_float();
			float density = 1.0f;
			float friction = 1.0f;
			float restitution = 0.15f;
			bool isSensor = false;
			const char* tag = "none";
			BodyType type = BodyType::DYNAMIC;

			//CHECKING FOR PROPERTIES
			if (child.child("properties"))
			{
				for (const auto& child : child.child("properties"))
				{
					if (!std::strcmp(child.attribute("name").as_string(), "static"))
					{
						if (child.attribute("value").as_bool())
						{
							type = BodyType::STATIC;
						}

					}

					if (!std::strcmp(child.attribute("name").as_string(), "tag"))
					{
						tag = child.attribute("value").as_string();
					}

				}
			}

			/////////////////////////

			game->physics->AddPhysicsObject(new CircleCollider(position,radius,0.0f, type,density, objectFriction,restitution,isSensor,tag));
		}

		//POLYGON COLLIDER
		if (child.child("polygon"))
		{
			fpoint position = { child.attribute("x").as_float(),- child.attribute("y").as_float() };

			std::string polygon = child.child("polygon").attribute("points").as_string();
		
			int polygonCounter = 0;

			//Get size
			for (int i = 0; i < polygon.length(); i++) {
				if (polygon.at(i) == ',')
				{
					polygonCounter++;
				}
			}
			
			//Check for size
			if (polygonCounter <= 8 && polygonCounter >= 3)
			{

			b2Vec2 vertices[8];

			//Helper variables
			int numberOne = 0;
			int numberTwo = 0;
			int iterationNum = 0;
			std::string numberHelper;

			for (int i = 0; i < polygon.length(); i++) {

				//Get vertex from string
				if (i == polygon.length() - 1)
				{
					numberHelper.push_back(polygon.at(i));
					numberTwo = std::stoi(numberHelper);
					numberHelper = "";
					vertices[iterationNum] = b2Vec2(numberOne, (-numberTwo));
					numberTwo = 0;
					numberOne = 0;
					iterationNum++;
				}

				if (polygon.at(i) == ' ') 
				{
					numberTwo = std::stoi(numberHelper);
					numberHelper = "";
					vertices[iterationNum] = b2Vec2(numberOne, (-numberTwo));
					numberTwo = 0;
					numberOne = 0;
					iterationNum++;
				}

				if (polygon.at(i) == ',')
				{
					numberOne = std::stoi(numberHelper);
					numberHelper = "";
					
				}

				if (polygon.at(i) != ' ' && polygon.at(i) != ',' && i != polygon.length() - 1)
				{
					numberHelper.push_back(polygon.at(i));
				}
			}

			BodyType type = BodyType::DYNAMIC;
			const char* tag = "none";
			//CHECKING FOR PROPERTIES
			if (child.child("properties"))
			{
				for (const auto& child : child.child("properties"))
				{
					if (!std::strcmp(child.attribute("name").as_string(), "static"))
					{
						if (child.attribute("value").as_bool())
						{
							type = BodyType::STATIC;
						}
					}

					if (!std::strcmp(child.attribute("name").as_string(), "tag"))
					{
						tag = child.attribute("value").as_string();
					}

				}
			}
			/////////////////////////


			game->physics->AddPhysicsObject( new PolygonCollider(position, polygonCounter,vertices,0.0f,type,1.0f, objectFriction,0.0f,false, tag));

			}
		}

		//POINT
		if (child.child("point"))
		{

		}
	}
}
