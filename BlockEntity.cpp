#include "stdafx.h"
#include "BlockEntity.h"

BlockEntity::BlockEntity(float x, float y, float w, float h)
{
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Yellow);
    rect.setOutlineThickness(-1);
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(w, h));
}

void BlockEntity::updateCollision(Entity* entity, float etime)
{
    sf::FloatRect prevPosX, prevPosY, bound;
    prevPosX = prevPosY = bound = entity->getRect();
    float dx = entity->getMovementComponent()->getSpeed() * entity->getMovementComponent()->getDirection().x * etime;
    float dy = entity->getMovementComponent()->getSpeed() * entity->getMovementComponent()->getDirection().y * etime;
    prevPosY.left -= dx;
    prevPosX.top -= dy;

    if (getRect().intersects(prevPosX))
    {
        if (bound.left > prevPosY.left) entity->setPosition(getRect().left - bound.width, entity->getPosition().y);
        if (bound.left < prevPosY.left) entity->setPosition(getRect().left + getRect().width, entity->getPosition().y);
    }
    if (getRect().intersects(prevPosY))
    {
        if (bound.top > prevPosX.top) entity->setPosition(entity->getPosition().x, getRect().top - bound.height);
        if (bound.top < prevPosX.top) entity->setPosition(entity->getPosition().x, getRect().top + getRect().height);
    }
}

void BlockEntity::update(float etime)
{

}