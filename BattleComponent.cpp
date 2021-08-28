#include "stdafx.h"
#include "BattleComponent.h"

BattleComponent::BattleComponent(float damage, float distance, float time) : damage(damage), distanceMax(distance), battleTimeMax(time)
{
}

bool BattleComponent::isReady()
{
	return battleTime.getElapsedTime().asMilliseconds() >= battleTimeMax;
}

void BattleComponent::initAttack()
{
	attack = true;
}

void BattleComponent::resetAttack()
{
	attack = false;
	battleTime.restart();
}

bool BattleComponent::attacked()
{
	return attack;
}

void BattleComponent::setDirection(sf::Vector2f dir)
{
	direction = dir;
}

void BattleComponent::setDamage(float dmg)
{
	damage = dmg;
}

sf::Vector2f BattleComponent::getDirection()
{
	return direction;
}

float BattleComponent::getDamage()
{
	return damage;
}

float BattleComponent::getDistance()
{
	return distanceMax;
}
