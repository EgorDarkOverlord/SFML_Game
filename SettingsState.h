#pragma once
#include "State.h"
#include "Gui.h"

class SettingsState : public State
{
private:
	int modeNum;
	bool notice;
	bool fullscreen;
	std::vector<sf::VideoMode>& videoModes;
	sf::VideoMode& resolution;
	
	GUI gui;
	Label resolutionLabel;
	Button leftButton, rightButton, fullscreenButton;
	
	void resetGUI();
public:
	SettingsState();
	virtual void updateEvent() override;
	virtual void update(float etime) override;
	virtual void draw() override;
};

