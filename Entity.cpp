#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

WorldFacade* Entity::worldFacade;

void Entity::setWorldFacade(WorldFacade* facade)
{
	if(!worldFacade)
		worldFacade = facade;
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
	{
		return hitboxComponent->getPosition();
	}
	return rect.getPosition();
}

sf::Vector2f Entity::getRectPosition()
{
	return rect.getPosition();
}

sf::FloatRect Entity::getRect()
{
	if (hitboxComponent)
	{
		return hitboxComponent->getGlobalBounds();
	}
	return rect.getGlobalBounds();
}

sf::Vector2f Entity::getMovementDirection()
{
	if (movementComponent)
	{
		return movementComponent->getDirection();
	}
	return sf::Vector2f(0, 0);
}

float Entity::getMovementSpeed()
{
	if (movementComponent)
	{
		return movementComponent->getSpeed();
	}
	return 0;
}

void Entity::setPosition(float x, float y)
{
	if (hitboxComponent)
	{
		hitboxComponent->setPosition(x, y);
	}
	else
	{
		rect.setPosition(x, y);
	}
}

void Entity::setMovementDirection(sf::Vector2f direction)
{
	if (movementComponent)
	{
		movementComponent->setDirection(direction);
	}
}

void Entity::setMovementSpeed(float speed)
{
	if (movementComponent)
	{
		movementComponent->setSpeed(speed);
	}
}

void Entity::rotateRect(float rotation)
{
	if (movementComponent)
	{
		movementComponent->rotateRect(rotation);
	}
}

void Entity::rotateRectByVector(sf::Vector2f vector)
{
	if (movementComponent)
	{
		movementComponent->rotateRectByVector(vector);
	}
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
