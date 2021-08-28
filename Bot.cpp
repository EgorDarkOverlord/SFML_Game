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

bool Bot::isAlive()
{
	return attributeComponent->getHealth() > 0;
}

void Bot::update(float etime)
{
	aiComponent->update();
	movementComponent->update(etime);
}
