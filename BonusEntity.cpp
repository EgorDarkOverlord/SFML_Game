#include "stdafx.h"
#include "BonusEntity.h"

BonusEntity::BonusEntity(float x, float y, sf::Texture* texture, std::function<void(Bot*)> func) : func(func)
{
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(100, 100));
    rect.setTexture(texture);
}

bool BonusEntity::isAlive()
{
    return active;
}

void BonusEntity::Invoke(Bot* bot)
{
    active = false;
    func(bot);
}

void BonusEntity::Heal(Bot* bot)
{
    bot->getAttributeComponent()->gainHealth(100);
}

void BonusEntity::MaxHealthUp(Bot* bot)
{
    bot->getAttributeComponent()->setHealthMax(bot->getAttributeComponent()->getHealthMax() * 1.1);
}

void BonusEntity::IncreaseDamage(Bot* bot)
{
    bot->getBattleComponent()->setDamage(bot->getBattleComponent()->getDamage() * 1.1);
}

void BonusEntity::IncreaseScore(Bot* bot)
{
    bot->getAttributeComponent()->gainScore(1000);
}
