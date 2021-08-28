#include "stdafx.h"
#include "SpawnSystem.h"



//template<class T>
//SpawnSystem<T>::SpawnSystem(int countMax, float spawnTimeMax, std::map<std::string, sf::Texture>* textures, std::vector<T*>* objects, std::vector<BlockEntity*>* blockEntities, Player* player) :
//	SpawnSystem_Base(countMax, spawnTimeMax, textures, objects, blockEntities, player)
//{
//}
//
//void SpawnSystem<Bot>::addSpawnObject()
//{
//	Bot* bot = new Zombie(0, 0, textures->at("Zombie"), player);
//	bot->getAttributeComponent()->setHealthMax(bot->getAttributeComponent()->getHealthMax() * (1 + player->getAttributeComponent()->getLevel() / 10));
//	bot->getBattleComponent()->setDamage(bot->getBattleComponent()->getDamage() * (1 + player->getAttributeComponent()->getLevel() / 10));
//	bot->setPosition(rand() % 800, rand() % 600);
//	while (!entityFree(bot))
//		bot->setPosition(rand() % 800, rand() % 600);
//	objects->push_back(bot);
//}

//template<>
//void SpawnSystem_Base<Bot>::addSpawnObject()
//{
//
//}
