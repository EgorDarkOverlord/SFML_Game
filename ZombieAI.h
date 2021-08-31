#pragma once
#include "AIComponent.h"
class ZombieAI : public AIComponent
{
public:
	ZombieAI(Bot* self, WorldFacade* worldFacade);
	virtual void update() override;
};

