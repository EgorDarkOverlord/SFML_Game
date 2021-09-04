#pragma once
#include "Bot.h"

class BonusEntity : public Entity
{
private:
	bool active = true;
	std::function<void(Bot*)> func;
public:
	BonusEntity(float x, float y, sf::Texture* texture, std::function<void(Bot*)> func);
	bool isAlive();
	void update(float etime) {}
	void Invoke(Bot* bot);

	static void Heal(Bot* bot);
	static void MaxHealthUp(Bot* bot);
	static void IncreaseDamage(Bot* bot);
	static void IncreaseScore(Bot* bot);
	static void SpawnSoldier(Bot* bot);
};

