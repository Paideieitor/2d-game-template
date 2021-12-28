//#include "Console.h"
//
//#include "Input.h"
//#include "Render.h"
//#include "Fonts.h"
//#include "SceneManager.h"
//
//Console::Console()
//{
//	display = false;
//	input = nullptr;
//	scroll = nullptr;
//}
//
//Console::~Console()
//{
//
//}
//
//bool Console::SetUp(pugi::xml_node& node)
//{
//	return true;
//}
//
//bool Console::Start()
//{
//	font = game->fonts->Load("fonts/overpass/extrabold.ttf", 30);
//
//	return true;
//}
//
//bool Console::Update(float dt)
//{
//	if (game->scenes->ChangingScenes())
//	{
//		display = false;
//		input = nullptr;
//		scroll = nullptr;
//	}
//
//	if (game->input->GetKey(SDL_SCANCODE_F8) == DOWN)
//	{
//		display = !display;
//
//		if (display)
//		{
//			input = new InputBox("console input", font, { 0, 1000 }, { 600,40 }, {50,50,50,200});
//			//scroll = new ScrollBar();
//		}
//		else
//		{
//			delete input;
//			input = nullptr;
//
//			//delete scroll;
//			scroll = nullptr;
//		}
//	}
//
//	if (display)
//	{
//		game->render->RenderRectangle(30, { 0,0 }, 600, 1000, { 30,30,30,200 });
//	}
//
//	return true;
//}
//
//bool Console::CleanUp()
//{
//	while (history.size() != 0)
//		history.erase(history.begin());
//
//	if (input)
//		delete input;
//	if (scroll)
//		delete scroll;
//
//	return true;
//}
//
//void Console::UIEvent(UIElement* element)
//{
//	if (element == input)
//	{
//		history.push_back(input->GetContent());
//	}
//}