#include "stdafx.h"
#include "VectorMath.h"

float vectorLength(sf::Vector2f vec)
{
    return hypot(vec.x, vec.y);
}

float vectorDistance(sf::Vector2f from, sf::Vector2f to)
{
    return hypot(to.x - from.x, to.y - from.y);
}

float vectorAngle(sf::Vector2f vec)
{
    return atan2(vec.y, vec.x);
}

sf::Vector2f vectorNormalized(sf::Vector2f vec)
{
    return vec / hypot(vec.x, vec.y);
}

float radToDeg(float angle)
{
    return angle * 180 / PI;
}

float degToRad(float angle)
{
    return angle * PI / 180;
}
