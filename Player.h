#pragma once
#include "Bot.h"

class Player : public Bot
{
public:
	Player(float x, float y, sf::Texture *texture);
	virtual void update(float etime) override;
};

