#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	title = "DEFAULT";
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	verticalSync = false;
	frameRateLimit = 120;
	contextSettings.antialiasingLevel = 0;
	videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << title << "\n";
		ofs << resolution.width << " " << resolution.height << "\n";
		ofs << fullscreen << "\n";
		ofs << frameRateLimit << "\n";
		ofs << verticalSync << "\n";
		ofs << contextSettings.antialiasingLevel << "\n";
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> resolution.width >> resolution.height;
		ifs >> fullscreen;
		ifs >> frameRateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}

	ifs.close();
}
