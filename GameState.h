#pragma once
#include "State.h"
#include "Gui.h"
#include "World.h"

class GameState : public State
{
private:
	World* world;
	sf::View view;
	GUI gui;
	Panel panel;
	Label scoreLabel, endgameLabel;
	bool paused;
	bool endgame;
	int health, score;
	void setGameOver();
public:
	GameState();
	virtual void updateEvent() override;
	virtual void update(float etime) override;
	virtual void draw() override;
};
