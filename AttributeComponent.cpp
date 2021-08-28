#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(float healthMax) : health(healthMax), healthMax(healthMax), exp(0), score(0), level(0)
{
}

AttributeComponent::AttributeComponent(float healthMax, int expNext) : AttributeComponent(healthMax)
{
    this->expNext = expNext;
}

void AttributeComponent::loseHealth(float hp)
{
    health -= hp;
    if (health < 0)
        health = 0;
}

void AttributeComponent::gainHealth(float hp)
{
    health += hp;
    if (health > healthMax)
        health = healthMax;
}

void AttributeComponent::gainScore(int score)
{
    this->score += score;
    exp += score;
    updateLevel();
}

void AttributeComponent::setHealthMax(float hp)
{
    healthMax = hp;
}

float AttributeComponent::getHealth()
{
    return health;
}

int AttributeComponent::getScore()
{
    return score;
}

int AttributeComponent::getLevel()
{
    return level;
}

float AttributeComponent::getHealthMax()
{
    return healthMax;
}

void AttributeComponent::updateLevel()
{
    if (exp > expNext)
    {
        level++;
        exp -= expNext;
    }
}
