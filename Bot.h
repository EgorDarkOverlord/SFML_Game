#pragma once
#include "Entity.h"
#include "AIComponent.h"
#include "BattleComponent.h"
#include "AttributeComponent.h"

class Bot : public Entity
{
protected:
	AIComponent* aiComponent = NULL;
	BattleComponent* battleComponent = NULL;
	AttributeComponent* attributeComponent = NULL;
	sf::Vector2f battlePoint;
public:
	Bot(float x, float y, sf::Texture* texture);
	virtual ~Bot() override;

	AIComponent* getAIComponent();
	BattleComponent* getBattleComponent();
	AttributeComponent* getAttributeComponent();
	sf::Vector2f getBattlePoint();
	bool isAlive();

	virtual void update(float etime) override;
};

