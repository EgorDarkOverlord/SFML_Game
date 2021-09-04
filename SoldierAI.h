#pragma once
#include "AIComponent.h"
class SoldierAI : public AIComponent
{
public:
	SoldierAI(Bot* self, WorldFacade* worldFacade);
	virtual void update() override;
};

