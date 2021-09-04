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
	if (isAlive() && getRect().intersects(worldFacade->getPlayer()->getRect()))
	{
		if (ownerType == typeid(Zombie).name())
		{
			crashTo(worldFacade->getPlayer());
			worldFacade->playSound(&worldFacade->getBuffers()["Kick"], worldFacade->getPlayer()->getRectPosition(),
				worldFacade->getPlayer()->getRectPosition(), 500, 1);
		}
		if (ownerType == typeid(Terrorist).name())
		{
			crashTo(worldFacade->getPlayer());
			worldFacade->playSound(&worldFacade->getBuffers()["BulletDamage"], worldFacade->getPlayer()->getRectPosition(),
				worldFacade->getPlayer()->getRectPosition(), 500, 1);
		}
	}
	
	for (auto* i : worldFacade->getBots())
		if (isAlive() && getRect().intersects(i->getRect()))
		{
			if ((ownerType == typeid(Player).name()) || ownerType == typeid(Soldier).name())
				if (typeid(*i) != typeid(Soldier))
				{
					crashTo(i);
					worldFacade->playSound(&worldFacade->getBuffers()["BulletDamage"], worldFacade->getPlayer()->getRectPosition(),
						i->getRectPosition(), 500, 1);
				}
			if (ownerType == typeid(Zombie).name())
				if (typeid(*i) == typeid(Soldier))
				{
					crashTo(i);
					worldFacade->playSound(&worldFacade->getBuffers()["Kick"], worldFacade->getPlayer()->getRectPosition(),
						i->getRectPosition(), 500, 1);
				}
			if (ownerType == typeid(Terrorist).name())
				if (typeid(*i) == typeid(Soldier))
				{
					crashTo(i);
					worldFacade->playSound(&worldFacade->getBuffers()["BulletDamage"], worldFacade->getPlayer()->getRectPosition(),
						i->getRectPosition(), 500, 1);
				}
		}
	
	for (auto* i : worldFacade->getBlockEntities())
		if (getRect().intersects(i->getRect()))
			crash();
}

void Bullet::update(float etime)
{
	movementComponent->update(etime);
	distance += movementComponent->getSpeed() * etime;
	updateCrush();
}
