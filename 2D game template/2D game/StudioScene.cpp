#include "StudioScene.h"

#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "SceneManager.h"
#include "TransitionManager.h"

#include "Textures.h"
#include "UIManager.h"
#include "EntityManager.h"
#include "MapLoader.h"

StudioScene::StudioScene(float duration) : Scene("Studio Scene")
{
	this->duration = duration;
}

StudioScene::~StudioScene()
{
}

bool StudioScene::Start()
{
	game->transition->FadeToBlack(2.0f, true);
	logoTexture = game->textures->Load("images/nyomStudiosLogo.png");
	return true;
}

bool StudioScene::Update(float dt)
{
	if (!fadingOut && duration <= 0.0f)
	{
		game->transition->FadeToBlack(2.0f, false);
		fadingOut = true;
	}
	else 
	{
		duration -= dt;
	}
	game->render->RenderTexture(true, 20, logoTexture, { 0,0 }, 0, 0, logoTexture->GetSize(), false, 255, true);



	if (game->transition->GetState() == TransitionState::TRANSITION_END_FADE_OUT)
		game->scenes->ChangeScene("Main Menu");

	return true;
}

bool StudioScene::CleanUp()
{
	return true;
}

void StudioScene::UIEvent(UIElement*)
{
}
