#include "stdafx.h"
#include "SoldierAI.h"
#include "WorldFacade.h"

SoldierAI::SoldierAI(Bot* self, WorldFacade* worldFacade) : AIComponent(self, worldFacade)
{
	minRadius = self->getBattleDistance() * 0.5;
	maxRadius = self->getBattleDistance() * 1.2;
}

void SoldierAI::update()
{
	protectBot();
}
