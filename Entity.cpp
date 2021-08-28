#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

MovementComponent* Entity::getMovementComponent()
{
	return movementComponent;
}

HitboxComponent* Entity::getHitboxComponent()
{
	return hitboxComponent;
}

sf::Vector2f Entity::getPosition()
{
	if (hitboxComponent)
		return hitboxComponent->getPosition();
	return rect.getPosition();
}

sf::Vector2f Entity::getRectPosition()
{
	return rect.getPosition();
}

sf::FloatRect Entity::getRect()
{
	if (hitboxComponent)
		return hitboxComponent->getGlobalBounds();
	return rect.getGlobalBounds();
}

void Entity::setPosition(float x, float y)
{
	if (hitboxComponent)
		hitboxComponent->setPosition(x, y);
	else
		rect.setPosition(x, y);
}

Entity::~Entity()
{
	delete movementComponent;
	delete hitboxComponent;
}

void Entity::draw(sf::RenderWindow* window)
{
	window->draw(rect);
}
