#include "ButtonArray.h"

//#include "Input.h"
//#include "SceneManager.h"
#include "UIManager.h"
#include "Textures.h"
#include "Render.h"

#include "Label.h"
#include "Button.h"

//ButtonArray::ButtonArray(string name, Font* font, fpoint position, ipoint size, Color maincolor, Font* subfont, bool worldposition) : UIElement(Observer())
//{
//	type = BUTTONARRAY;
//
//	maintext = game->textures->LoadText(font, name.c_str(), { 0,0,0,255 });
//
//	mainposition = game->Center(maintext->GetSize(), position, { (int)size.x/2,(int)size.y });
//
//	this->name = name;
//	this->position = position;
//	this->size = size;
//	this->maincolor = maincolor;
//	this->worldposition = worldposition;
//
//	displaying = false;
//
//	if(subfont)
//		this->subfont = subfont;
//	else
//		this->subfont = font;
//
//	pugi::xml_node arraynode = game->scenes->mainnode.child(observer.GetName()).child(name.c_str());
//
//	current = arraynode.attribute("current").as_int();
//
//	amount = 0;
//	pugi::xml_node button = arraynode.first_child();
//	for (button; button != NULL; button = button.next_sibling())
//		amount++;
//	button = arraynode.first_child();
//
//	buttonsdata = new string[amount];
//	for (int i = 0; i < amount; i++)
//	{
//		buttonsdata[i] = button.attribute("name").as_string();
//		button = button.next_sibling();
//	}
//
//	currentposition = { position.x + size.x / 2, position.y };
//	currentsize = { size.x / 2, size.y };
//	mainbutton = new Button(buttonsdata[current].c_str(), this->subfont, currentposition, currentsize, maincolor + 100, LOCKONCLICK, worldposition, this);
//}
//
//ButtonArray::~ButtonArray()
//{
//	if(buttons)
//		delete[] buttons;
//	delete[] buttonsdata;
//
//	game->textures->Unload(maintext);
//
//	delete mainbutton;
//}
//
//elementstate ButtonArray::Update(float dt)
//{
//	elementstate output = OK;
//
//	if (displaying)
//	{
//		if (!buttons)
//		{
//			output = CHILD_CREATION;
//			buttons = new Button[amount];
//
//			fpoint pos = currentposition;
//			for (int i = 0; i < amount; i++)
//			{
//				pos.y += currentsize.y;
//				buttons[i].Set(buttonsdata[i], subfont, pos, currentsize, maincolor + 100, SINGLECLICK, worldposition, this);
//			}
//		}
//	}
//	else
//		if (buttons)
//		{
//			output = CHILD_DESTRUCTION;
//			delete[] buttons;
//			buttons = nullptr;
//		}
//
//	game->render->RenderRectangle(20, position, size.x/2, size.y, maincolor, worldposition);
//	game->render->RenderTexture(20, maintext, mainposition, 0, 0, maintext->GetSize(), false, maincolor.a, worldposition);
//
//	if(displaying)
//		displaying = false;
//	return output;
//}
//
//bool ButtonArray::CleanUp()
//{
//	return true;
//}
//
//void ButtonArray::UIEvent(UIElement* element)
//{
//	if (element == mainbutton)
//		displaying = true;
//
//	if (displaying)
//		for (int i = 0; i < amount; i++)
//			if (element == &buttons[i])
//			{
//				current = i;
//				mainbutton->name = buttons[i].name;
//				game->textures->ChangeTexture(buttons[i].text, mainbutton->text);
//
//				pugi::xml_node arraynode = game->scenes->mainnode.child(observer.GetName()).child(name.c_str());
//
//				arraynode.attribute("current").set_value(current);
//				game->document.save_file("config.xml");
//
//				mainbutton->state = NOTPRESSED;
//				displaying = false;
//
//				observer.UIEvent(this);
//				break;
//			}
//}
//
//string ButtonArray::GetArrayCurrent() 
//{
//	return mainbutton->name;
//}

ButtonArray::ButtonArray(const string& text, Font* font, const Color& fontcolor, const vector<string>& options, const fpoint& position, 
	Texture* texture, const UIStateTextures& maintextures, const UIStateTextures& unfoldtextures, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, worldposition, observer), texture(texture), unfoldtextures(unfoldtextures), 
	options(options), change("")
{
	if (options.size() <= 0)
		delete this;

	if (text.size() > 0)
		this->text = new Label(text, font, fontcolor, position, worldposition);
	current = new Button(options[0], font, fontcolor, position, maintextures, Button::Type::LOCKONCLICK, worldposition, this);

	if (texture)
		textsize = texture->GetSize();
	else
		if (this->text)
			textsize = game->ResizeIPoint(this->text->GetSize(), RECT_SIZE_MULTIPLIER);
		else
			textsize = ipoint(0, 0);
	SetSize(textsize.x + current->GetSize().x, textsize.y);

	PositionChanged();
}

ButtonArray::~ButtonArray()
{
	delete text;
	delete current;

	DeleteButtons();
}

UIElement::Output ButtonArray::Update(float dt)
{
	if (change.size() > 0)
	{
		current->ChangeText(change);
		change = "";

		DeleteButtons();
		current->Lock(false);
		observer.UIEvent(this);

		return UIElement::Output::LIST_MODIFY;
	}

	return UIElement::Output::NO_MODIFY;
}

void ButtonArray::Render()
{
	if (!texture)
		game->render->RenderRectangle(UI_RENDER_LAYER, GetPosition(), textsize, Color(255, 50, 50), IsWorldPos());
}

void ButtonArray::UIEvent(UIElement* element)
{
	if (element == current)
	{
		if (buttons.size() > 0)
			DeleteButtons();
		else
			CreateButtons();
	}
	else
		change = ((Button*)element)->GetText();
}

const string ButtonArray::GetCurrent() const
{
	return current->GetText();
}

void ButtonArray::SetCurrent(unsigned int index)
{
	if (index < options.size())
		current->ChangeText(options[index]);
}

void ButtonArray::SetCurrent(const string& str)
{
	current->ChangeText(str);
}

void ButtonArray::ActiveChanged()
{
	text->SetActive(IsActive());
	current->SetActive(IsActive());

	for (size_t i = 0; i < buttons.size(); ++i)
		buttons[i]->SetActive(IsActive());
}

void ButtonArray::PositionChanged()
{
	fpoint position = GetPosition();

	text->SetPosition(game->Center(text->GetSize(), position, textsize));
	current->SetPosition(position.x + textsize.x, position.y);

	PlaceButtons();
}

void ButtonArray::SizeChanged()
{
}

void ButtonArray::WorldPosChanged()
{
	text->EnableWorldPos(IsWorldPos());
	current->EnableWorldPos(IsWorldPos());

	for (size_t i = 0; i < buttons.size(); ++i)
		buttons[i]->EnableWorldPos(IsWorldPos());
}

void ButtonArray::CreateButtons()
{
	for (size_t i = 0; i < options.size(); ++i)
		buttons.push_back(new Button(options[i], current->GetFont(), current->GetColor(), fpoint(0, 0), unfoldtextures, 
			Button::Type::SINGLECLICK, IsWorldPos(), this));
	PlaceButtons();
}

void ButtonArray::DeleteButtons()
{
	for (size_t i = 0; i < buttons.size(); ++i)
		delete buttons[i];
	buttons.clear();
}

void ButtonArray::PlaceButtons()
{
	fpoint position = current->GetPosition();

	float positiony = position.y + (float)current->GetSize().y;
	for (size_t i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->SetPosition(position.x, positiony);
		positiony += (float)buttons[i]->GetSize().y;
	}
}
