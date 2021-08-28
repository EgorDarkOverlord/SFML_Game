#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Bot* owner, sf::Texture* texture) : crashed(0), distance(0)
{
	ownerType = typeid(*owner).name();

	rect.setOrigin(5, 5);
	rect.setPosition(owner->getBattlePoint());
	rect.setSize(sf::Vector2f(10, 10));
	rect.setTexture(texture);

	movementComponent = new MovementComponent(&rect, 500);
	movementComponent->setDirection(owner->getBattleComponent()->getDirection());
	maxDistance = owner->getBattleComponent()->getDistance();
	damage = owner->getBattleComponent()->getDamage();
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
	target->getAttributeComponent()->loseHealth(damage);
	crashed = true;
}

void Bullet::update(float etime)
{
	movementComponent->update(etime);
	distance += movementComponent->getSpeed() * etime;
}
