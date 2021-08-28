#include "stdafx.h"
#include "AIFollow.h"

AIFollow::AIFollow(Entity* self, Entity* target, float radius) : AIComponent(self, target), radius(radius)
{
}

void AIFollow::update()
{
	self->getMovementComponent()->setDirection(sf::Vector2f(0, 0));
	sf::Vector2f moveVec = target->getRectPosition() - self->getRectPosition();
	float vecLength = vectorLength(moveVec);
	if (vecLength <= radius)
	{
		if (!self->getRect().intersects(target->getRect()))
			self->getMovementComponent()->setDirection(moveVec);
		self->getMovementComponent()->rotateRectByVector(moveVec);
	}
}
