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
	sf::Vector2f getBattleDirection();
	float getDamage();
	float getBattleDistance();
	bool isReadyToAttack();
	bool attacked();
	float getHealth();
	float getHealthMax();
	int getScore();
	int getLevel();
	bool isAlive();

	
	void initAttack();
	void resetAttack();
	void setBattleDirection(sf::Vector2f dir);
	void setDamage(float dmg);
	void gainHealth(float hp);
	void loseHealth(float hp);
	void setHealthMax(float hp);
	void gainScore(int score);

	virtual void update(float etime) override;
};

