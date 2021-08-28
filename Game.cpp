#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	initGraphicsSettings();
	initWindow();

	stateData.window = window;
	stateData.world = &world;
	stateData.gfxSettings = gfxSettings;
	State::setStateData(&stateData);

	Panel::loadTextures();
	Label::loadFont("C:/Windows/Fonts/Arial.ttf");
	Button::setButtonPrototypes();
	
	State::pushState("MainMenuState", new MainMenuState);
	State::pushState("GameState", new GameState);
	State::pushState("SettingsState", new SettingsState);
	State::pushState("SplashState", new SplashState);
	State::setState("SplashState");
}

Game::~Game()
{
	delete window;
	State::removeStates();
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/Graphics.ini");
}

void Game::initWindow()
{
	window = new sf::RenderWindow(gfxSettings.resolution, gfxSettings.title, gfxSettings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	gfxSettings.verticalSync ? window->setVerticalSyncEnabled(true) : window->setFramerateLimit(gfxSettings.frameRateLimit);
}

void Game::dispatchSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			window->close();
		State::getState()->updateEvent();
	}
}

void Game::update()
{
	//std::cout << 1 / etime << "\n";
	dispatchSFMLEvents();
	State::getState()->update(etime);
}

void Game::updateTime()
{
	etime = sfClock.restart().asSeconds();
}

void Game::run()
{
	while (window->isOpen())
	{
		updateTime();
		update();
		draw();
	}
}

void Game::draw()
{
	window->clear();
	State::getState()->draw();
	window->display();
}
