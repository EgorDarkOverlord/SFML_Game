#pragma once
#include "GraphicsSettings.h"
#include "World.h"

class StateData
{
public:	
	sf::RenderWindow* window;
	World* world;
	sf::Vector2f mousePos;
	GraphicsSettings gfxSettings;
	void updateMousePosition();
};

class State
{
private:
	static std::map<std::string, State*> states;
	static State* currentState;
	std::vector<bool> pressedKeys;
protected:
    static StateData* stateData;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
public:
	State();
	
	static void setStateData(StateData* stateData);
	static void pushState(const char* name, State* state);
	static void removeStates();
	static void setState(const char* name);
	static State* getState();
	
	void updateMousePosition();

	bool isKeyPressedOnce(sf::Keyboard::Key key);
	
	virtual ~State() {};
	virtual void updateEvent() {};
	virtual void update(float etime) = 0;
	virtual void draw() = 0;
};

