#pragma once
#include<SFML/System.hpp>
#include<math.h>

float vectorLength(sf::Vector2f vec);
float vectorDistance(sf::Vector2f from, sf::Vector2f to);
float vectorAngle(sf::Vector2f vec);
sf::Vector2f vectorNormalized(sf::Vector2f vec);
float radToDeg(float angle);
float degToRad(float angle);