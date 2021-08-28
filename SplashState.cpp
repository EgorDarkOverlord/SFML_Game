#include "stdafx.h"
#include "SplashState.h"

SplashState::SplashState()
{
	duration = 3000;
	panel = Panel(
		stateData->window->getView().getCenter().x - 300, 
		stateData->window->getView().getCenter().y - 300,
		600, 600, "Intro");
}

void SplashState::updateEvent()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		setState("MainMenuState");
}

void SplashState::update(float etime)
{
	if (timer.getElapsedTime().asMilliseconds() >= duration)
		setState("MainMenuState");
}

void SplashState::draw()
{
	panel.draw(stateData->window);
}
