#pragma once
class BattleComponent
{
private:
	bool attack;
	sf::Clock battleTime;
	float battleTimeMax;
	float damage;
	float distanceMax;
	sf::Vector2f direction;
public:
	BattleComponent(float damage, float distance, float time);
	bool isReady();
	void initAttack();
	void resetAttack();
	bool attacked();
	
	void setDirection(sf::Vector2f dir);
	void setDamage(float dmg);
	sf::Vector2f getDirection();
	float getDamage();
	float getDistance();
};

