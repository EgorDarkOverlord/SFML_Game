#include "stdafx.h"
#include "TerroristAI.h"
#include "WorldFacade.h"

TerroristAI::TerroristAI(Bot* self, WorldFacade* worldFacade) : AIComponent(self, worldFacade)
{
	minRadius = self->getBattleDistance() * 0.5;
	maxRadius = self->getBattleDistance() * 1.2;
}

void TerroristAI::update()
{
	attackBot();
}
