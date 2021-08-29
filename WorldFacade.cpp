#include "stdafx.h"
#include "WorldFacade.h"

void WorldFacade::playSound(sf::SoundBuffer* buffer, sf::Vector2f listenerPos, sf::Vector2f sourcePos, float minDistance, float attenuation)
{
	world->playSound(buffer, listenerPos, sourcePos, minDistance, attenuation);
}
