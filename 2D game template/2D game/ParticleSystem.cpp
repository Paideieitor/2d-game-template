#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	name = "particles";
}

ParticleSystem::~ParticleSystem()
{
}

bool ParticleSystem::SetUp(pugi::xml_node&)
{
	return true;
}

bool ParticleSystem::Update(float dt)
{
	return true;
}

bool ParticleSystem::CleanUp()
{
	return true;
}
