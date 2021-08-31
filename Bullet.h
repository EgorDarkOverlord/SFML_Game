#pragma once
#include"Bot.h"

class Bullet : public Entity
{
private:
	std::string ownerType;
	bool crashed;
	float distance, maxDistance;
	float damage;
public:
	Bullet(Bot* owner, sf::Texture* texture);
	std::string getOwnerType();
	bool isAlive();
	void crash();
	void crashTo(Bot* target);
	void updateCrush();
	virtual void update(float etime) override;
};

