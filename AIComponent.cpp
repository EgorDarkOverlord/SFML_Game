#include "stdafx.h"
#include "AIComponent.h"
#include "WorldFacade.h"

void AIComponent::attackBot()
{
	self->setMovementDirection(sf::Vector2f(0, 0));

	sf::Vector2f moveVec = worldFacade->getPlayer()->getRectPosition() - self->getRectPosition();
	float vecLength = vectorLength(moveVec);

	//поиск ближайшего враждебного бота

	for (auto* i : worldFacade->getBots())
		if (typeid(*i) == typeid(Soldier) &&
			vectorDistance(self->getRectPosition(), i->getRectPosition()) < vecLength)
		{
			moveVec = i->getRectPosition() - self->getRectPosition();
			vecLength = vectorLength(moveVec);
		}

	if (vectorDistance(worldFacade->getPlayer()->getRectPosition(), self->getRectPosition()) < vecLength)
	{
		moveVec = worldFacade->getPlayer()->getRectPosition() - self->getRectPosition();
		vecLength = vectorLength(moveVec);
	}

	//погоня за врагом и атака

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

void AIComponent::protectBot()
{
	self->setMovementDirection(sf::Vector2f(0, 0));

	sf::Vector2f moveVec = worldFacade->getPlayer()->getRectPosition() - self->getRectPosition();
	float vecLength = vectorLength(moveVec);

	sf::Vector2f battleDirection(0, 0);
	float battleDistance = maxRadius;
	
	//поиск ближайшего враждебного бота
	
	for (auto* i : worldFacade->getBots())
		if ((typeid(*i) == typeid(Zombie) || (typeid(*i) == typeid(Terrorist))) &&
			vectorDistance(self->getRectPosition(), i->getRectPosition()) < battleDistance)
		{
			battleDirection = i->getRectPosition() - self->getRectPosition();
			battleDistance = vectorLength(battleDirection);
		}

	//Следование за игроком
	
	if (vecLength <= maxRadius)
	{
		if (vecLength > minRadius)
			self->setMovementDirection(moveVec);
		self->rotateRectByVector(moveVec);
	}

	//Атака ближайшего врага, если он в зоне видимости

	if (battleDistance < self->getBattleDistance())
	{
		self->rotateRectByVector(battleDirection);
		self->setBattleDirection(battleDirection);
		if (self->isReadyToAttack())
			self->initAttack();
	}
}

AIComponent::AIComponent(Bot* self, WorldFacade* worldFacade) : self(self), worldFacade(worldFacade)
{
	
}