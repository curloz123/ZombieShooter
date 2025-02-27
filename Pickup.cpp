#include "Pickup.h"
#include "textureHolder.h"
#include <SFML/System/Vector2.hpp>

Pickup::Pickup(int type)
{
	m_Type = type;

	if(m_Type ==1)
	{
		//Health
		m_Sprite.setTexture(textureHolder::getTexture("graphics/health_pickup.png"));
		m_Value = HEALTH_START_VALUE;
	}
	else
	{
		//Ammo
		m_Sprite.setTexture(textureHolder::getTexture("graphics/ammo_pickup.png"));
		m_Value = AMMO_START_VALUE;
	}

	m_Sprite.setOrigin(25,25);
	m_SecondsToLive = START_SECONDS_TO_LIVE;
	m_SecondsToWait = START_WAIT_TIME;

}

void Pickup::setArena(sf::IntRect arena)
{
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.height = arena.height -50;
	m_Arena.top = arena.top + 50;

	spawn(); //Check this asshole
}

void Pickup::spawn()
{
	srand((int)time(0)*m_Type);
	int x = (rand() % m_Arena.width);
	int y = (rand() % m_Arena.height);

	m_SecondsSinceSpawn = 0;
	m_Spawned = true;
	m_Sprite.setPosition(x,y);
}

sf::Vector2f Pickup::getPos()
{
	return m_Sprite.getPosition();
}
sf::Sprite Pickup::getSprite()
{
	return m_Sprite;
}
bool Pickup::isSpawned()
{
	return m_Spawned;
}

int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

void Pickup::update(float deltaTime)
{
	if(m_Spawned)
	{
		m_SecondsSinceSpawn += deltaTime;
	}
	else
	{
		m_SecondsSinceDeSpawn += deltaTime;
	}

	if(m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}
	if(m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		spawn();
	}

}

void Pickup::upgrade()
{
	if(m_Type == 1)
	{
		m_Value += (HEALTH_START_VALUE * 0.5);
	}
	else
	{
		m_Value += (AMMO_START_VALUE * 0.5);
	}

	m_SecondsToLive += START_SECONDS_TO_LIVE/10.0f;
	m_SecondsToWait -= START_WAIT_TIME/10.0f;
}









