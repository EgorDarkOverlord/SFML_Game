#pragma once
#include "AIComponent.h"
class AIFollow : public AIComponent
{
protected:
	float radius;
public:
	AIFollow(Entity* self, Entity* target, float radius = 500);
	virtual void update() override;
};

