#include "stdafx.h"
#include "World.h"

World::World()
{
	player = NULL;
	pictureMap = NULL;
}

void World::loadWorld()
{
	srand(time(0));

	textures["Player"].loadFromFile("Images/Player.png");
	textures["Zombie"].loadFromFile("Images/Zombie.png");
	textures["Bullet"].loadFromFile("Images/Bullet.png");
	textures["BulletTransparent"].loadFromFile("Images/BulletTransparent.png");
	textures["Heal"].loadFromFile("Images/Heal.png");
	textures["MaxHealthUp"].loadFromFile("Images/MaxHealthUp.png");
	textures["IncreaseDamage"].loadFromFile("Images/IncreaseDamage.png");
	textures["IncreaseScore"].loadFromFile("Images/IncreaseScore.png");

	buffers["PlayerAttack"].loadFromFile("Sounds/AK.wav");
	buffers["Bonus"].loadFromFile("Sounds/Bonus.wav");
	buffers["MonsterDead"].loadFromFile("Sounds/MonsterDead.ogg");
	buffers["BulletDamage"].loadFromFile("Sounds/BulletDamage.ogg");
	buffers["Kick"].loadFromFile("Sounds/Kick.ogg");

	pictureMap = new PictureMap(2, 2, 5000, 5000, "Images/Map/");
	worldRect = sf::FloatRect(0, 0, 10000, 10000);

	player = new Player(200, 300, &textures["Player"]);
	
	enemies.push_back(new Zombie(500, 0, &textures["Zombie"], player));
	enemies.push_back(new Zombie(0, 0, &textures["Zombie"], player));
	enemySpawnSystem = new SpawnSystem<Bot>(500, 20, worldRect, &textures, &enemies, &blockEntities, player);
	bonusEntitySpawnSystem = new SpawnSystem<BonusEntity>(50, 1000, worldRect, &textures, &bonusEntities, &blockEntities, player);

	std::ifstream ifs("Config/blockEntities.txt");
	std::string ss;
	while (std::getline(ifs, ss))
	{
		std::vector<std::string> sp;
		std::istringstream iss(ss);
		while (iss)
		{
			std::string subs;
			iss >> subs;
			sp.push_back(subs);
		}
		blockEntities.push_back(new BlockEntity(atof(sp[0].c_str()), atof(sp[1].c_str()), atof(sp[2].c_str()), atof(sp[3].c_str())));
		sp.clear();
	}
	ifs.close();
}

void World::unLoadWorld()
{
	delete player;
	for (auto* i : enemies)
		delete i;
	for (auto* i : bullets)
		delete i;
	for (auto* i : blockEntities)
		delete i;
	for (auto* i : bonusEntities)
		delete i;
	delete enemySpawnSystem;
	delete bonusEntitySpawnSystem;
	delete pictureMap;
	
	enemies.clear();
	bullets.clear();
	blockEntities.clear();
	bonusEntities.clear();
	buffers.clear();
	sounds.clear();

	player = NULL;
	enemySpawnSystem = NULL;
	bonusEntitySpawnSystem = NULL;
	pictureMap = NULL;
}

void World::getGameScore(int& health, int& score)
{
	health = player->getHealth();
	score = player->getScore();
}

void World::updatePlayerInput(sf::Vector2f mousePosView)
{
	sf::Vector2f dir(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1;
	player->setMovementDirection(dir);

	player->rotateRectByVector(mousePosView - player->getRectPosition());
	player->setBattleDirection(mousePosView - player->getRectPosition());
}

void World::playSound(sf::SoundBuffer* buffer, sf::Vector2f listenerPos, sf::Vector2f sourcePos, float minDistance, float attenuation)
{
	sf::Sound sound(*buffer);
	float gain = 100 * minDistance / (minDistance + attenuation * (vectorDistance(listenerPos, sourcePos) - minDistance));
	if (gain > 100) gain = 100;
	if (gain > 1)
	{
		sound.setVolume(gain);
		auto i = std::find_if(sounds.begin(), sounds.end(), [](sf::Sound& sound) {return sound.getStatus() != sf::Sound::Playing; });
		if (i != sounds.cend())
		{
			*i = sound;
			i->play();
		}
		else
		{
			sounds.push_back(sound);
			(sounds.end() - 1)->play(); 
		}
	}
}

void World::updateCombat()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->isReadyToAttack())
	{
		player->resetAttack();
		bullets.push_back(new Bullet(player, &textures["Bullet"]));
		playSound(&buffers["PlayerAttack"], player->getRectPosition(), player->getBattlePoint(), 1000, 1);
	}

	for (auto* i : enemies)
		if (i->attacked())
		{
			i->resetAttack();
			bullets.push_back(new Bullet(i, &textures["BulletTransparent"]));
		}
}

void World::updateBotCollision(float etime)
{
	for (auto* i : blockEntities)
	{
		i->updateCollision(player, etime);
		for (auto* j : enemies)
			i->updateCollision(j, etime);
	}
}

void World::updateBulletsCrashes()
{
	for (auto* i : bullets)
	{
		if (i->isAlive() && i->getRect().intersects(player->getRect()) && (i->getOwnerType() == typeid(Zombie).name()))
		{
			i->crashTo(player);
			playSound(&buffers["Kick"], player->getRectPosition(), player->getRectPosition(), 500, 1);
		}
		for (auto* j : enemies)
			if (i->isAlive() && i->getRect().intersects(j->getRect()) && (i->getOwnerType() == typeid(Player).name()))
			{
				i->crashTo(j);
				playSound(&buffers["BulletDamage"], player->getRectPosition(), player->getRectPosition(), 500, 1);
			}
		for (auto* j : blockEntities)
			if (i->getRect().intersects(j->getRect()))
				i->crash();
	}
}

World::~World()
{
	unLoadWorld();
}

void World::update(float etime, sf::Vector2f mousePosView)
{
	updatePlayerInput(mousePosView);

	player->update(etime);

	enemySpawnSystem->update();
	bonusEntitySpawnSystem->update();

	for (auto* i : enemies)
		i->update(etime);

	//updateBotCollision(etime);

	for (auto* i : blockEntities)
		i->update(etime);

	updateCombat();

	for (auto* i : bullets)
		i->update(etime);

	//updateBulletsCrashes();

	for (auto* i : bonusEntities)
		if (i->getRect().intersects(player->getRect()))
		{
			i->Invoke(player);
			playSound(&buffers["Bonus"], player->getRectPosition(), player->getRectPosition(), 1000, 1);
		}

	for (int i = 0; i < enemies.size(); i++)
		if (!enemies[i]->isAlive())
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			player->gainScore(100);
			playSound(&buffers["MonsterDead"], player->getRectPosition(), player->getRectPosition(), 1000, 1);
		}
	
	for (int i = 0; i < bullets.size(); i++)
		if (!bullets[i]->isAlive())
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}

	for (int i = 0; i < bonusEntities.size(); i++)
		if (!bonusEntities[i]->isAlive())
		{
			delete bonusEntities[i];
			bonusEntities.erase(bonusEntities.begin() + i);
		}
}

void World::updateView(sf::View* view)
{
	view->setCenter(player->getRectPosition());
	
	if (view->getCenter().x - view->getSize().x / 2 < worldRect.left)
		view->setCenter(worldRect.left + view->getSize().x / 2, view->getCenter().y);
	
	if (view->getCenter().x + view->getSize().x / 2 > worldRect.left + worldRect.width)
		view->setCenter(worldRect.left + worldRect.width - view->getSize().x / 2, view->getCenter().y);
	
	if (view->getCenter().y - view->getSize().y / 2 < worldRect.top)
		view->setCenter(view->getCenter().x, worldRect.top + view->getSize().y / 2);
	
	if (view->getCenter().y + view->getSize().y / 2 > worldRect.top + worldRect.height)
		view->setCenter(view->getCenter().x, worldRect.top + worldRect.height - view->getSize().y / 2);

}

void World::draw(sf::RenderWindow* window)
{
	pictureMap->draw(window);

	//for (auto* i : blockEntities)
	//	i->draw(window);

	for (auto* i : bonusEntities)
		i->draw(window);

	player->draw(window);

	for (auto* i : enemies)
		i->draw(window);

	for (auto* i : bullets)
		i->draw(window);
}