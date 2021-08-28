#pragma once
#include "Bot.h"
#include "AIFollow.h"

class Zombie : public Bot
{
public:
	Zombie(float x, float y, sf::Texture* texture, Entity* player);
};

