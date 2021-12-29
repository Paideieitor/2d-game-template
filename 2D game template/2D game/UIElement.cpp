#include "UIElement.h"

#include "UIManager.h"
#include "SceneManager.h"
#include "Textures.h"

UIElement::UIElement(const Type& type, const fpoint& position, bool worldposition, const Observer& observer)
	: type(type), active(true), position(position), size(ipoint(0,0)), worldposition(worldposition), state(State::IDLE), observer(observer)
{
	game->ui->elements.push_back(this);
	if (this->observer.IsEmpty())
		this->observer.Fill(game->scenes->currentscene);
}

UIElement::~UIElement()
{
	game->ui->EraseElement(this);
}

void UIStateTextures::UnloadTextures()
{
	if (idle)
		game->textures->Unload(idle);
	if (hover)
		game->textures->Unload(hover);
	if (click)
		game->textures->Unload(click);
	if (disabled)
		game->textures->Unload(disabled);
}
