#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	gui.emplace("MainMenu", Button(50, 50, "Standard", "Играть", "Play"));
	gui.emplace("MainMenu", Button(50, 150, "Standard", "Настройки", "Settings"));
	gui.emplace("MainMenu", Button(50, 250, "Standard", "Выход", "To_Exit"));
	gui.emplace("ExitMenu", Button(50, 100, "Standard", "Нет", "To_Main"));
	gui.emplace("ExitMenu", Button(50, 200, "Standard", "Да", "Exit"));
	gui.emplace("ExitMenu", Label(50, 50, "Вы точно хотите выйти?"));
	gui.emplace("LoadMenu", Label(50, 50, "Загрузка... Пожалуйста, подождите"));
	gui.setMenuActive("MainMenu");
}

void MainMenuState::updateEvent()
{
	gui.updateButtons((sf::Vector2f)mousePosWindow);

	std::string command = gui.getActiveButton();
	if (command == "Play") 
	{
		gui.setMenuActive("LoadMenu"); //Отрисовка загрузочного экрана	
		stateData->window->clear();
		gui.draw(stateData->window);
		stateData->window->display();
		gui.setMenuActive("MainMenu");
		
		stateData->world->loadWorld();
		setState("GameState");
	}
	
	if (command == "Settings")
		setState("SettingsState");

	if (command == "To_Exit") 
		gui.setMenuActive("ExitMenu");

	if (command == "To_Main") 
		gui.setMenuActive("MainMenu");
	
	if (command == "Exit") stateData->window->close();
}

void MainMenuState::update(float etime)
{
	updateMousePosition();
}

void MainMenuState::draw()
{
	gui.draw(stateData->window);
}
