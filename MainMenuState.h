#pragma once
#include "State.h"
#include "Gui.h"

class MainMenuState : public State
{
private:
	GUI gui;
public:
	MainMenuState();
	virtual void updateEvent() override;
	virtual void update(float etime) override;
	virtual void draw() override;
};

