#pragma once
#include "BlockEntity.h"
#include "BonusEntity.h"
#include "Zombie.h"
#include "Terrorist.h"
#include "Player.h"

template <class T>
class SpawnSystem
{
protected:
	sf::Clock spawnTime;
	float spawnTimeMax;
	int countMax;
	sf::FloatRect worldRect;

	std::map<std::string, sf::Texture>* textures;
	std::vector<T*>* objects;
	std::vector<BlockEntity*>* blockEntities;
	Player* player;
public:
	SpawnSystem(int countMax, float spawnTimeMax, sf::FloatRect worldRect, std::map<std::string, sf::Texture>* textures, std::vector<T*>* objects, std::vector<BlockEntity*>* blockEntities, Player* player);
	bool entityFree(Entity* entity);
	bool spawnReady();

	void addSpawnObject();
	void deleteSpawnObject(int index);
	void update();
};

//----------------------------------------------------------------------------------------------------------

template <class T>
SpawnSystem<T>::SpawnSystem(int countMax, float spawnTimeMax, sf::FloatRect worldRect,
	std::map<std::string, sf::Texture>* textures, std::vector<T*>* objects, std::vector<BlockEntity*>* blockEntities, Player* player) :
	countMax(countMax), spawnTimeMax(spawnTimeMax), worldRect(worldRect), textures(textures), objects(objects), blockEntities(blockEntities), player(player)
{
}

template <class T>
bool SpawnSystem<T>::entityFree(Entity* entity)
{
	for (auto* i : *blockEntities)
		if (i->getRect().intersects(entity->getRect()))
			return false;
	return true;
}

template <class T>
bool SpawnSystem<T>::spawnReady()
{
	return (spawnTime.getElapsedTime().asMilliseconds() >= spawnTimeMax) && objects->size() < countMax;
}

template <class T>
void SpawnSystem<T>::addSpawnObject()
{
}

template <class T>
void SpawnSystem<T>::deleteSpawnObject(int index)
{
	delete objects[index];
	objects->erase(objects->begin() + index);
}

template <class T>
void SpawnSystem<T>::update()
{
	if (spawnReady())
	{
		addSpawnObject();
		spawnTime.restart();
	}
}

template<>
inline void SpawnSystem<Bot>::addSpawnObject()
{
	Bot* bot;
	
	if (rand() % 20 == 0)
		bot = new Terrorist(0, 0, &textures->at("Terrorist"));
	else
		bot = new Zombie(0, 0, &textures->at("Zombie"));

	bot->setHealthMax(bot->getHealthMax() * (1 + player->getLevel() / 10.f));
	bot->setDamage(bot->getDamage() * (1 + player->getLevel() / 10.f));

	bot->setPosition(rand() % int(worldRect.width - bot->getRect().width), rand() % int(worldRect.height - bot->getRect().height));
	while (!entityFree(bot))
		bot->setPosition(rand() % int(worldRect.width - bot->getRect().width), rand() % int(worldRect.height - bot->getRect().height));

	objects->push_back(bot);
}

template<>
inline void SpawnSystem<BonusEntity>::addSpawnObject()
{
	const int TYPE_COUNT = 5;
	BonusEntity* bonusEntity = NULL;
	int type = rand() % TYPE_COUNT;
	switch (type)
	{
	case 0: bonusEntity = new BonusEntity(0, 0, &textures->at("Heal"), BonusEntity::Heal); break;
	case 1: bonusEntity = new BonusEntity(0, 0, &textures->at("MaxHealthUp"), BonusEntity::MaxHealthUp); break;
	case 2: bonusEntity = new BonusEntity(0, 0, &textures->at("IncreaseDamage"), BonusEntity::IncreaseDamage); break;
	case 3: bonusEntity = new BonusEntity(0, 0, &textures->at("IncreaseScore"), BonusEntity::IncreaseScore); break;
	case 4: bonusEntity = new BonusEntity(0, 0, &textures->at("SpawnSoldier"), BonusEntity::SpawnSoldier); break;
	}

	bonusEntity->setPosition(rand() % int(worldRect.width - bonusEntity->getRect().width), rand() % int(worldRect.height - bonusEntity->getRect().height));
	while (!entityFree(bonusEntity))
		bonusEntity->setPosition(rand() % int(worldRect.width - bonusEntity->getRect().width), rand() % int(worldRect.height - bonusEntity->getRect().height));

	objects->push_back(bonusEntity);
}