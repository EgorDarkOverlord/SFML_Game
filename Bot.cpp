#include "stdafx.h"
#include "Bot.h"

Bot::Bot(float x, float y, sf::Texture* texture)
{
	rect.setPosition(x, y);
	rect.setTexture(texture);
}

Bot::~Bot()
{
	delete aiComponent;
	delete battleComponent;
	delete attributeComponent;
}

AIComponent* Bot::getAIComponent()
{
	return aiComponent;
}

BattleComponent* Bot::getBattleComponent()
{
	return battleComponent;
}

AttributeComponent* Bot::getAttributeComponent()
{
	return attributeComponent;
}

sf::Vector2f Bot::getBattlePoint()
{
	return rect.getTransform().transformPoint(battlePoint);
}

sf::Vector2f Bot::getBattleDirection()
{
	return battleComponent->getDirection();
}

float Bot::getDamage()
{
	return battleComponent->getDamage();
}

float Bot::getBattleDistance()
{
	return battleComponent->getDistance();
}

bool Bot::isReadyToAttack()
{
	return battleComponent->isReady();
}

bool Bot::attacked()
{
	return battleComponent->attacked();
}

float Bot::getHealth()
{
	return attributeComponent->getHealth();
}

float Bot::getHealthMax()
{
	return attributeComponent->getHealthMax();
}

int Bot::getScore()
{
	return attributeComponent->getScore();
}

int Bot::getLevel()
{
	return attributeComponent->getLevel();
}

bool Bot::isAlive()
{
	return attributeComponent->getHealth() > 0;
}

void Bot::initAttack()
{
	battleComponent->initAttack();
}

void Bot::resetAttack()
{
	battleComponent->resetAttack();
}

void Bot::setBattleDirection(sf::Vector2f dir)
{
	battleComponent->setDirection(dir);
}

void Bot::setDamage(float dmg)
{
	battleComponent->setDamage(dmg);
}

void Bot::gainHealth(float hp)
{
	attributeComponent->gainHealth(hp);
}

void Bot::loseHealth(float hp)
{
	attributeComponent->loseHealth(hp);
}

void Bot::setHealthMax(float hp)
{
	attributeComponent->setHealthMax(hp);
}

void Bot::gainScore(int score)
{
	attributeComponent->gainScore(score);
}

void Bot::update(float etime)
{
	aiComponent->update();
	movementComponent->update(etime);
}
