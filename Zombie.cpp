#include "stdafx.h"
#include "Zombie.h"

Zombie::Zombie(float x, float y, sf::Texture* texture, Entity* player) : Bot(x, y, texture)
{
	rect.setSize(sf::Vector2f(100, 60));
	rect.setOrigin(50, 30);
	battlePoint = sf::Vector2f(80, 30);

	movementComponent = new MovementComponent(&rect, 200);
	aiComponent = new AIFollow(this, player);
	battleComponent = new BattleComponent(10, 100, 2000);
	hitboxComponent = new HitboxComponent(&rect, -20, -20, 40, 40);
	attributeComponent = new AttributeComponent(100);
}
