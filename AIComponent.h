#pragma once
#include "Entity.h"

class Bot;

class AIComponent
{
protected:
	Bot* self;
	WorldFacade* worldFacade;
	float minRadius, maxRadius;

	//Осуществляет нападение на игрока и ботов типа Soldier
	void attackBot();
	//Осуществляет защиту игрока
	void protectBot();
public:
	AIComponent(Bot* self, WorldFacade* worldFacade);
	virtual void update() = 0;
};

