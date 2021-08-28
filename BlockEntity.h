#pragma once
#include "Entity.h"
class BlockEntity : public Entity
{
public:	
	BlockEntity(float x, float y, float w, float h);
	void updateCollision(Entity* entity, float etime);
	virtual void update(float etime) override;
};

