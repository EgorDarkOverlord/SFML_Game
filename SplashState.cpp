#include "stdafx.h"
#include "SplashState.h"

SplashState::SplashState()
{
	duration = 3000;
	panel = Panel(
		stateData->window->getView().getCenter().x - 300, 
		stateData->window->getView().getCenter().y - 300,
		600, 600, "Intro");

	rect.setPosition(0, 0);
	rect.setSize(stateData->window->getView().getSize());
	rect.setFillColor(sf::Color(0, 0, 0, 255));
}

void SplashState::updateEvent()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		setState("MainMenuState");
}

void SplashState::update(float etime)
{
	float time = timer.getElapsedTime().asMilliseconds();
	int alpha = 255;
	const int SPLASH_DURATION = 1000;

	alpha = 255 * (1 - time / SPLASH_DURATION);

	if (alpha < 0)
		alpha = 0;

	if (time > duration - SPLASH_DURATION)
		alpha = 255 * ((time - (duration - SPLASH_DURATION)) / SPLASH_DURATION - 1);

	rect.setFillColor(sf::Color(0, 0, 0, alpha));

	if (time >= duration)
		setState("MainMenuState");
}

void SplashState::draw()
{
	panel.draw(stateData->window);
	stateData->window->draw(rect);
}
