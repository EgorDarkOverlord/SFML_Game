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
	self->setMovementDirection(sf::Vector2f(0, 0));
	sf::Vector2f moveVec = worldFacade->getPlayer()->getRectPosition() - self->getRectPosition();
	float vecLength = vectorLength(moveVec);
	if (vecLength <= maxRadius)
	{
		if (vecLength > minRadius)
		{
			self->setMovementDirection(moveVec);
		}
		else
		{
			if (self->isReadyToAttack())
				self->initAttack();
		}
		self->rotateRectByVector(moveVec);
		self->setBattleDirection(moveVec);
	}
}
