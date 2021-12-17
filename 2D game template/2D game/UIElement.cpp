#include "UIElement.h"

#include "UIManager.h"
#include "SceneManager.h"
#include "Textures.h"

UIElement::UIElement(Observer observer) : observer(observer)
{
	clickable = false;
	game->ui->elements.push_back(this);
	if (this->observer.IsEmpty())
		this->observer.Fill(game->scenes->currentscene);
}

UIElement::~UIElement()
{
	game->ui->EraseElement(this);
}
