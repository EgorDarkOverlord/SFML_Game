#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::RectangleShape* rect, float offsetX, float offsetY, float width, float height) : 
    rect(rect), offsetX(offsetX), offsetY(offsetY)
{
    hitbox = sf::FloatRect(rect->getPosition().x + offsetX, rect->getPosition().y + offsetY, width, height);
}

sf::Vector2f HitboxComponent::getPosition()
{
    return sf::Vector2f(hitbox.left, hitbox.top);
}

sf::FloatRect HitboxComponent::getGlobalBounds()
{
    hitbox.left = rect->getPosition().x + offsetX;
    hitbox.top = rect->getPosition().y + offsetY;
    return hitbox;
}

void HitboxComponent::setPosition(float x, float y)
{
    hitbox.left = x;
    hitbox.top = y;
    rect->setPosition(x - offsetX, y - offsetY);
}