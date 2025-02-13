#include "Zombie.h"
#include "textureHolder.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include<ctime>
#include<cstdlib>
#include<cmath>

void zombie::spawn(float startX , float startY , int type )
{
	srand(time(0));
	switch (type)
	{
		case 0:
			//bloater
			m_Sprite.setTexture(textureHolder::getTexture("graphics/bloater.png"));
			m_Speed = BLOATER_SPEED;
			m_Health = BLOATER_HEALTH;
			break;

		case 1:
			//crawler
			m_Sprite.setTexture(textureHolder::getTexture("graphics/crawler.png"));
			m_Speed = CRAWLER_SPEED;
			m_Health = CRAWLER_HEALTH;
			break;
		case 2:
			//bloater
			m_Sprite.setTexture(textureHolder::getTexture("graphics/chaser.png"));
			m_Speed = CHASER_SPEED;
			m_Health = CHASER_HEALTH;
			break;
	}

	float random = rand()%4;
	m_Speed = m_Speed*(1-random/10.0f);

	m_Position = sf::Vector2f(startX , startY);
	m_Sprite.setOrigin(25,25);


}
	

bool zombie::Hit()
{
	--m_Health;
	if(m_Health<=0)
	{
		m_Alive = false;
		m_Sprite.setTexture(textureHolder::getTexture("graphics/blood.png"));
		return true;
	}
	return false;
}


bool zombie::Alive()
{
	return m_Alive;
}

sf::Sprite zombie::getSprite()
{
	return m_Sprite;
}

sf::FloatRect zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


void zombie::update(float deltaTime , sf::Vector2f playerPosition)
{
	if(m_Position.x < playerPosition.x)
	{
		m_Position.x += m_Speed*deltaTime;
	}
	else if(m_Position.x > playerPosition.x)
	{
		m_Position.x -= m_Position.x*deltaTime;
	}
	
	if(m_Position.y < playerPosition.y)
	{
		m_Position.y += m_Speed*deltaTime;
	}
	else if(m_Position.y > playerPosition.y)
	{
		m_Position.y -= m_Position.y*deltaTime;
	}

	float angle = atan2(m_Position.y - playerPosition.y , m_Position.x - playerPosition.x) * (180/3.141);
	m_Sprite.setRotation(angle);
}
