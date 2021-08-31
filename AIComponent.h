#pragma once
#include "Entity.h"

class Bot;

class AIComponent
{
protected:
	Bot* self;
	WorldFacade* worldFacade;
	float minRadius, maxRadius;
public:
	AIComponent(Bot* self, WorldFacade* worldFacade);
	virtual void update() = 0;
};

