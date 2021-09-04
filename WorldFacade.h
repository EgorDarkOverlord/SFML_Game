#pragma once
#include "World.h"

class WorldFacade
{
private:
	World* world;
public:
	WorldFacade() {}
	WorldFacade(World* world) : world(world) {};
	
	Player* getPlayer() { return world->player; }
	std::vector<BlockEntity*>& getBlockEntities() { return world->blockEntities; }
	std::vector<BonusEntity*>& getBonusEntities() { return world->bonusEntities; }
	std::vector<Bot*>& getBots() { return world->bots; }
	std::vector<Bullet*>& getBullets() { return world->bullets; }

	std::map<std::string, sf::Texture>& getTextures() { return world->textures; }
	std::map<std::string, sf::SoundBuffer>& getBuffers() { return world->buffers; }

	void playSound(sf::SoundBuffer* buffer, sf::Vector2f listenerPos, sf::Vector2f sourcePos, float minDistance, float attenuation);
};