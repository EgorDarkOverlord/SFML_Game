#include "stdafx.h"
#include "ZombieAI.h"
#include "WorldFacade.h"

ZombieAI::ZombieAI(Bot* self, WorldFacade* worldFacade) : AIComponent(self, worldFacade)
{
	minRadius = 50;
	maxRadius = 500;
}

void ZombieAI::update()
{
	attackBot();
}
