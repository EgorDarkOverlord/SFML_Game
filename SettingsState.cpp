#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::resetGUI()
{
	resolutionLabel.setString(std::to_string(resolution.width) + "X" + std::to_string(resolution.height));
	for (modeNum = 0; modeNum < videoModes.size(); modeNum++)
		if (resolution == videoModes[modeNum])
			break;
	fullscreenButton = (stateData->gfxSettings.fullscreen)? 
		Button(250, 150, "Checkbox_Checked", "", "Checkbox"):
		Button(250, 150, "Checkbox_Unchecked", "", "Checkbox");
}

SettingsState::SettingsState() : videoModes(stateData->gfxSettings.videoModes), resolution(stateData->gfxSettings.resolution)
{
	notice = false;
	fullscreen = stateData->gfxSettings.fullscreen;
	gui.emplace("Settings", Label(50, 50, "Настройки"));
	gui.emplace("Settings", Label(50, 100, "Разрешение:"));
	gui.emplace("Settings", Label(50, 150, "Полный экран:"));
	gui.emplace("Settings", Button(50, 200, "Standard", "Применить", "Apply"));
	gui.emplace("Settings", Button(50, 300, "Standard", "Отмена", "MainMenu"));
	gui.emplace("Notice", Label(50, 50, "Изменения вступят после перезагрузки игры"));
	gui.emplace("Notice", Button(50, 100, "Standard", "Ок", "MainMenu"));
	gui.setMenuActive("Settings");

	resolutionLabel = Label(300, 100);
	leftButton = Button(250, 100, "Button_Left", "", "Left");
	rightButton = Button(450, 100, "Button_Right", "", "Right");
	fullscreenButton = Button(250, 150, "Checkbox_Unchecked", "", "Checkbox");
	resetGUI();
}

void SettingsState::updateEvent()
{
	gui.updateButtons((sf::Vector2f)mousePosWindow);

	std::string command = gui.getActiveButton();
	if (command == "MainMenu")
	{
		resetGUI();
		notice = false;
		gui.setMenuActive("Settings");
		setState("MainMenuState");
	}
	if (command == "Apply")
	{
		resolution = videoModes[modeNum];
		stateData->gfxSettings.fullscreen = fullscreen;
		stateData->gfxSettings.saveToFile("Config/Graphics.ini");
		notice = true;
		gui.setMenuActive("Notice");
	}

	if (notice) return;
	
	leftButton.updateState((sf::Vector2f)mousePosWindow);
	rightButton.updateState((sf::Vector2f)mousePosWindow);
	fullscreenButton.updateState((sf::Vector2f)mousePosWindow);

	if (leftButton.isActive())
	{
		modeNum--;
		if (modeNum < 0) modeNum = videoModes.size() - 1;
		resolutionLabel.setString(std::to_string(videoModes[modeNum].width) + "X" + std::to_string(videoModes[modeNum].height));
	}

	if (rightButton.isActive())
	{
		modeNum++;
		if (modeNum >= videoModes.size()) modeNum = 0;
		resolutionLabel.setString(std::to_string(videoModes[modeNum].width) + "X" + std::to_string(videoModes[modeNum].height));
	}

	if (fullscreenButton.isActive())
	{
		fullscreen = !fullscreen;
		fullscreenButton = (fullscreen) ?
			Button(250, 150, "Checkbox_Checked", "", "Checkbox") :
			Button(250, 150, "Checkbox_Unchecked", "", "Checkbox");
	}
}

void SettingsState::update(float etime)
{
	updateMousePosition();
}

void SettingsState::draw()
{
	gui.draw(stateData->window);
	if (notice) return;
	leftButton.draw(stateData->window);
	rightButton.draw(stateData->window);
	fullscreenButton.draw(stateData->window);
	resolutionLabel.draw(stateData->window);
}
