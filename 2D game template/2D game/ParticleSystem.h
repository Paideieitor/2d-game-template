#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Module.h"

class Particle
{

};

class Emitter
{

};

class ParticleSystem : public Module
{
public:

	ParticleSystem();
	~ParticleSystem();

	bool SetUp(pugi::xml_node&) override;
	bool Update(float dt) override;
	bool CleanUp() override;
};

#endif
