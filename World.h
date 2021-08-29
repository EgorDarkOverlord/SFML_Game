#pragma once
#include "BlockEntity.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "SpawnSystem.h"
#include "PictureMap.h"

class World
{
	friend class WorldFacade;
private:
	Player* player;
	std::vector<BlockEntity*> blockEntities;
	std::vector<BonusEntity*> bonusEntities;
	std::vector<Bot*> enemies;
	std::vector<Bullet*> bullets;
	
	SpawnSystem<Bot>* enemySpawnSystem;
	SpawnSystem<BonusEntity>* bonusEntitySpawnSystem;
	
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> buffers;
	std::vector<sf::Sound> sounds;
	PictureMap* pictureMap;
	sf::FloatRect worldRect;
	
	void updatePlayerInput(sf::Vector2f mousePosView);
	void playSound(sf::SoundBuffer* buffer, sf::Vector2f listenerPos, sf::Vector2f sourcePos, float minDistance, float attenuation);
	void updateCombat();
	void updateBotCollision(float etime);
	void updateBulletsCrashes();
public:
	World();
	~World();
	void loadWorld();
	void unLoadWorld();
	void getGameScore(int& health, int& score);
	void update(float etime, sf::Vector2f mousePosView);
	void updateView(sf::View* view);
	void draw(sf::RenderWindow* window);
};

