#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::RectangleShape* rect, float speed) : rect(rect),
    sourceSpeed(speed), direction(0,0), dirSpeed(0,0)
{
  
}

void MovementComponent::setDirection(sf::Vector2f dir)
{
    if (dir != sf::Vector2f(0, 0))
        direction = vectorNormalized(dir);
    else
        direction = dir;
}

void MovementComponent::setSpeed(float speed)
{
    sourceSpeed = speed;
}

float MovementComponent::getSpeed()
{
    return sourceSpeed;
}

sf::Vector2f MovementComponent::getDirection()
{
    return direction;
}

void MovementComponent::rotateRect(float rot)
{
    rotation = rot;
    rect->setRotation(radToDeg(rot));
}

void MovementComponent::rotateRectByVector(sf::Vector2f vec)
{
    rotateRect(vectorAngle(vec));
}

void MovementComponent::update(float etime)
{
    dirSpeed = direction * sourceSpeed;
    rect->move(dirSpeed * etime);
}