#pragma once
class PictureMap
{
private:	
	std::vector<std::vector<sf::Sprite>> sprites;
	std::vector<std::vector<sf::Texture>> textures;
	void loadSprite(int i, int j, int sizeX, int sizeY, int s_sizeX, int s_sizeY, std::string path);
public:
	PictureMap(int sizeX, int sizeY, int s_sizeX, int s_sizeY, std::string path);
	void draw(sf::RenderWindow* window);
};

