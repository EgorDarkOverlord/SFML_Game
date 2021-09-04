#pragma once
#include "AIComponent.h"
class TerroristAI : public AIComponent
{
public:
	TerroristAI(Bot* self, WorldFacade* worldFacade);
	virtual void update() override;
};

