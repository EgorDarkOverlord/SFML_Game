#include "stdafx.h"
#include "PictureMap.h"

void PictureMap::loadSprite(int i, int j, int sizeX, int sizeY, int s_sizeX, int s_sizeY, std::string path)
{
	std::ifstream in;
	
	in.open(path + std::to_string(i * sizeX + j) + ".png");
	if (in.is_open())
		if (!textures[i][j].loadFromFile(path + std::to_string(i * sizeX + j) + ".png"))
	in.close();
	
	in.open(path + std::to_string(i * sizeX + j) + ".jpg");
	if (in.is_open())
		textures[i][j].loadFromFile(path + std::to_string(i * sizeX + j) + ".jpg");
	in.close();
	
	sprites[i][j].setTexture(textures[i][j]);
	sprites[i][j].setPosition(sf::Vector2f(j * s_sizeX, i * s_sizeY));
}

PictureMap::PictureMap(int sizeX, int sizeY, int s_sizeX, int s_sizeY, std::string path)
{
	textures.resize(sizeY);
	sprites.resize(sizeY);
	for (int i = 0; i < sizeY; i++)
	{
		textures[i].resize(sizeX);
		sprites[i].resize(sizeX);
	}
	sf::Clock ck;
	std::vector<std::thread> th(sizeX * sizeY);

	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++)
		{	
			th[i * sizeX + j] = std::thread(&PictureMap::loadSprite, this, i, j, sizeX, sizeY, s_sizeX, s_sizeY, path);
		}

	for (int i = 0; i < th.size(); i++)
		th[i].join();
	std::cout << "\n time:" << ck.getElapsedTime().asMilliseconds() << "\n";
}

void PictureMap::draw(sf::RenderWindow* window)
{
	for (auto& i : sprites)
		for (auto& j : i)
			window->draw(j);
}
