#pragma once

class MovementComponent
{
private:
	float sourceSpeed;
	float rotation;
	sf::Vector2f direction;
	sf::Vector2f dirSpeed;
	sf::RectangleShape* rect;
public:
	MovementComponent(sf::RectangleShape* rect, float speed);
	
	void setDirection(sf::Vector2f dir);
	void setSpeed(float speed);
	
	float getSpeed();
	sf::Vector2f getDirection();
	
	void rotateRect(float rot);
	void rotateRectByVector(sf::Vector2f vec);
	
	void update(float etime);
};

