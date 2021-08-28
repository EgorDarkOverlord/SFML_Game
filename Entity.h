#pragma once
#include "MovementComponent.h"
#include "HitboxComponent.h"

class Entity
{
protected:
	sf::RectangleShape rect;
	MovementComponent* movementComponent = NULL;
	HitboxComponent* hitboxComponent = NULL;
public:
	Entity();

	MovementComponent* getMovementComponent();
	HitboxComponent* getHitboxComponent();
	
	sf::Vector2f getPosition();
	sf::Vector2f getRectPosition();
	sf::FloatRect getRect();
	sf::Vector2f getMovementDirection();
	float getMovementSpeed();

	void setPosition(float x, float y);
	void setMovementDirection(sf::Vector2f direction);
	void setMovementSpeed(float speed);
	void rotateRect(float rotation);
	void rotateRectByVector(sf::Vector2f vector);

	virtual ~Entity();
	virtual void update(float etime) = 0;
	virtual void draw(sf::RenderWindow* window);
};

