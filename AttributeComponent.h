#pragma once
class AttributeComponent
{
private:
	float health, healthMax;
	int score;
	int exp, expNext;
	int level;
public:
	AttributeComponent(float healthMax);
	AttributeComponent(float healthMax, int expNext);
	
	void loseHealth(float hp);
	void gainHealth(float hp);
	void gainScore(int score);
	void setHealthMax(float hp);

	float getHealth();
	int getScore();
	int getLevel();
	float getHealthMax();

	void updateLevel();
};

