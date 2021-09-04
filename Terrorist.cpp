#include "stdafx.h"
#include "Terrorist.h"

Terrorist::Terrorist(float x, float y, sf::Texture* texture) : Bot(x, y, texture)
{
	rect.setSize(sf::Vector2f(80, 60));
	rect.setOrigin(25, 25);
	battlePoint = sf::Vector2f(80, 25);

	movementComponent = new MovementComponent(&rect, 250);
	battleComponent = new BattleComponent(10, 600, 100);
	aiComponent = new TerroristAI(this, worldFacade);
	hitboxComponent = new HitboxComponent(&rect, -20, -20, 40, 40);
	attributeComponent = new AttributeComponent(100);
}
