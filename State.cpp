#include "stdafx.h"
#include "State.h"

void StateData::updateMousePosition()
{
	mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
}

State::State()
{
	pressedKeys.resize(sf::Keyboard::KeyCount);
	std::fill(pressedKeys.begin(), pressedKeys.end(), 0);
}

std::map<std::string, State*> State::states;
StateData *State::stateData;
State *State::currentState;

void State::setStateData(StateData* stateData)
{
	State::stateData = stateData;
}

void State::pushState(const char* name, State* state)
{
	states[name] = state;
}

void State::removeStates()
{
	for (auto it = states.begin(); it != states.end(); ++it)
		delete it->second;
}

void State::setState(const char* name)
{
	currentState = states[name];
}

State* State::getState()
{
	return currentState;
}

void State::updateMousePosition()
{
	mousePosWindow = sf::Mouse::getPosition(*stateData->window);
	mousePosView = stateData->window->mapPixelToCoords(mousePosWindow);
}

bool State::isKeyPressedOnce(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Unknown)
		return false;
	
	bool result = false;
	
	if(pressedKeys[key] == false)
	{
		if (sf::Keyboard::isKeyPressed(key))
		{
			pressedKeys[key] = true;
			result = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(key)) pressedKeys[key] = false;
	
	return result;
}
