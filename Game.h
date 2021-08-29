#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "SettingsState.h"
#include "SplashState.h"
#include "WorldFacade.h"

class Game
{
private:
	
	sf::RenderWindow *window;
	GraphicsSettings gfxSettings;
	sf::Event sfEvent;
	float etime;
	sf::Clock sfClock;
	StateData stateData;
	World world;
	WorldFacade worldFacade;

	void initGraphicsSettings();
	void initWindow();

public:
	Game();
	~Game();
	
	void dispatchSFMLEvents();
	void update();
	void updateTime();
	void run();
	void draw();
};

