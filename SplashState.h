#pragma once
#include "State.h"
#include "Gui.h"

class SplashState : public State
{
private:
	sf::Clock timer;
	float duration;
	Panel panel;
public:
	SplashState();
	virtual void updateEvent() override;
	virtual void update(float etime) override;
	virtual void draw() override;
};

