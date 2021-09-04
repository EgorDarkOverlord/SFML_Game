#include "stdafx.h"
#include "BonusEntity.h"
#include "WorldFacade.h"

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
    bot->gainHealth(100);
}

void BonusEntity::MaxHealthUp(Bot* bot)
{
    bot->setHealthMax(bot->getHealthMax() * 1.1);
}

void BonusEntity::IncreaseDamage(Bot* bot)
{
    bot->setDamage(bot->getDamage() * 1.1);
}

void BonusEntity::IncreaseScore(Bot* bot)
{
    bot->gainScore(1000);
}

void BonusEntity::SpawnSoldier(Bot* bot)
{
    if (std::count_if(worldFacade->getBots().begin(), worldFacade->getBots().end(),
        [](Bot* i) {return typeid(*i) == typeid(Soldier); }) < 5)
    {
        worldFacade->getBots().push_back(
            new Soldier(bot->getRectPosition().x, bot->getRectPosition().y, &worldFacade->getTextures()["Soldier"])
        );
    }
    else
    {
        for (auto* i : worldFacade->getBots())
            if (typeid(*i) == typeid(Soldier))
                i->gainHealth(100);
    }
}
