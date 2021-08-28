#pragma once
class HitboxComponent
{
private:
	sf::RectangleShape* rect;
	sf::FloatRect hitbox;
	float offsetX;
	float offsetY;
public:
	HitboxComponent(sf::RectangleShape* rect, float offsetX, float offsetY, float width, float height);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	void setPosition(float x, float y);
};

