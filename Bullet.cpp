#include "stdafx.h"
#include "Bullet.h"
#include "WorldFacade.h"

Bullet::Bullet(Bot* owner, sf::Texture* texture) : crashed(0), distance(0)
{
	ownerType = typeid(*owner).name();

	rect.setOrigin(5, 5);
	rect.setPosition(owner->getBattlePoint());
	rect.setSize(sf::Vector2f(10, 10));
	rect.setTexture(texture);

	movementComponent = new MovementComponent(&rect, 500);
	movementComponent->setDirection(owner->getBattleDirection());
	maxDistance = owner->getBattleDistance();
	damage = owner->getDamage();
}

bool Bullet::isAlive()
{
	return !crashed && (distance <= maxDistance);
}

std::string Bullet::getOwnerType()
{
	return ownerType;
}

void Bullet::crash()
{
	crashed = true;
}

void Bullet::crashTo(Bot* target)
{
	target->loseHealth(damage);
	crashed = true;
}

void Bullet::updateCrush()
{
	if (isAlive() && getRect().intersects(worldFacade->getPlayer()->getRect()) && (ownerType == typeid(Zombie).name()))
	{
		crashTo(worldFacade->getPlayer());
		worldFacade->playSound(&worldFacade->getBuffers()["Kick"], worldFacade->getPlayer()->getRectPosition(), 
			worldFacade->getPlayer()->getRectPosition(), 500, 1);
	}
	for (auto* j : worldFacade->getEnemies())
		if (isAlive() && getRect().intersects(j->getRect()) && (ownerType == typeid(Player).name()))
		{
			crashTo(j);
			worldFacade->playSound(&worldFacade->getBuffers()["BulletDamage"], worldFacade->getPlayer()->getRectPosition(),
				worldFacade->getPlayer()->getRectPosition(), 500, 1);
		}
	for (auto* j : worldFacade->getBlockEntities())
		if (getRect().intersects(j->getRect()))
			crash();
}

void Bullet::update(float etime)
{
	movementComponent->update(etime);
	distance += movementComponent->getSpeed() * etime;
	updateCrush();
}
