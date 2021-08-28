#pragma once
#include "Entity.h"

class AIComponent
{
protected:
	Entity* self;
	Entity* target;
public:
	AIComponent(Entity* self, Entity* target);
	virtual void update() = 0;
};

