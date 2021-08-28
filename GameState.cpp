#include "stdafx.h"
#include "GameState.h"

void GameState::setGameOver()
{
	endgame = true;
	paused = false;
	stateData->window->clear();
	gui.setMenuActive("GameOver");
	
	int record;
	std::ifstream ifs("Config/Record.txt");
	ifs >> record;
	ifs.close();
	
	std::string result;
	result = "Счет: " + std::to_string(score) + "\n" + "Макс. Счет: " + std::to_string(record) + "\n";
	if (score > record)
	{
		remove("Config/Record.txt");
		std::ofstream ofs("Config/Record.txt");
		ofs << score;
		ofs.close();
		result += "Новый рекорд";
	}
	
	endgameLabel.setString(result);
}

GameState::GameState()
{
	world = stateData->world;
	view = stateData->window->getDefaultView();
	stateData->window->setView(view);
	paused = false;
	endgame = false;

	gui.emplace("PauseMenu", Panel(0, 0, stateData->window->getSize().x, stateData->window->getSize().y, "Panel"));
	gui.emplace("PauseMenu", Button(50, 100, "Standard", "Продолжить", "Resume"));
	gui.emplace("PauseMenu", Button(50, 200, "Standard", "Выход", "Endgame"));
	gui.emplace("PauseMenu", Label(50, 50, "Пауза"));
	gui.emplace("GameOver", Label(50, 50, "Игра окончена"));
	gui.emplace("GameOver", Button(50, 150, "Standard", "Выход", "To_Menu"));
	
	panel = Panel(0, 0, 200, 80, "Panel");
	scoreLabel = Label(10, 10);
	endgameLabel = Label(50, 70);
}

void GameState::updateEvent()
{
	if (isKeyPressedOnce(sf::Keyboard::Key::Escape))
		paused = !paused;
	
	if(paused)
		gui.setMenuActive("PauseMenu");

	gui.updateButtons((sf::Vector2f)mousePosWindow);

	std::string command = gui.getActiveButton();
	if (command == "Resume") {
		paused = false;
	}
	if (command == "Exit") stateData->window->close();
	if (command == "Endgame") setGameOver();
	if (command == "To_Menu") 
	{
		world->unLoadWorld();
		paused = false;
		endgame = false;
		stateData->window->clear();
		setState("MainMenuState");
	}
}

void GameState::update(float etime)
{
	updateMousePosition();
	if (paused || endgame) return;
	world->update(etime, mousePosView);
	world->getGameScore(health, score);
	world->updateView(&view);
	stateData->window->setView(view);

	if (health <= 0)
		setGameOver();

	scoreLabel.setString("Здоровье: " + std::to_string(health) + "\n" + "Счет: " + std::to_string(score));
}

void GameState::draw()
{
	if (!endgame)
		world->draw(stateData->window);
	
	if (paused || endgame)
	{
		gui.draw(stateData->window);
		if (endgame)
			endgameLabel.draw(stateData->window);
	}
	else 
	{ 
		panel.draw(stateData->window);
		scoreLabel.draw(stateData->window);
	}
}
