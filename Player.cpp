#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y, sf::Texture* texture) : Bot(x, y, texture)
{
	rect.setSize(sf::Vector2f(80, 60));
	rect.setOrigin(25, 25);
	battlePoint = sf::Vector2f(80, 25);

	movementComponent = new MovementComponent(&rect, 300);
	battleComponent = new BattleComponent(10, 600, 100);
	hitboxComponent = new HitboxComponent(&rect, -20, -20, 40, 40);
	attributeComponent = new AttributeComponent(100, 1000);
}

void Player::update(float etime)
{
	movementComponent->update(etime);
}
