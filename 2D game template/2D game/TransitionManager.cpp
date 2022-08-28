#include "Game.h"
#include "TransitionManager.h"
#include "Render.h"
#include "Textures.h"
#include "Camera.h"


TransitionManager::TransitionManager()
{
}

TransitionManager::~TransitionManager()
{
}

bool TransitionManager::SetUp(pugi::xml_node&)
{
	return true;
}

bool TransitionManager::Update(float dt)
{
	if (state == TransitionState::TRANSITION_BEGIN) 
	{
		state = TransitionState::MID_TRANSITION;
		transitionTime = duration;
	}

	if (state == TransitionState::MID_TRANSITION) 
	{
		if (fadeIn) 
		{
		transitionTime -= dt;
		unsigned int transparency = transitionTime / duration * 255;
		Color a = { 0,0,0,transparency };
		if (transitionTime <= 0.0f) 
		{
			state = TransitionState::TRANSITION_END_FADE_IN;
		}
		game->render->RenderRectangle(true, 100, game->render->GetCameraPosition(), { 1920, 1080 }, a);
		}
		else 
		{
			transitionTime -= dt;
			unsigned int transparency =255 - transitionTime / duration * 255;
			Color a = { 0,0,0,transparency };
			if (transitionTime <= 0.0f)
			{
				state = TransitionState::TRANSITION_END_FADE_OUT;
			}
			game->render->RenderRectangle(true, 100, game->render->GetCameraPosition(), { 1920, 1080 }, a);
		}
	}

	if (state == TransitionState::TRANSITION_END_FADE_OUT) 
	{
		game->render->RenderRectangle(true, 100, game->render->GetCameraPosition(), { 1920, 1080 }, {0,0,0,255});
	}
	return true;
}

bool TransitionManager::CleanUp()
{
	return true;
}

void TransitionManager::FadeToBlack(float duration, bool fadeIn)
{
	this->duration = duration;
	this->fadeIn = fadeIn;
	state = TransitionState::TRANSITION_BEGIN;
}

TransitionState TransitionManager::GetState()
{
	return state;
}
