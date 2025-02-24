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
	m_Alive = true;
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

	float random = rand()%15;
	m_Speed += random;
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
	float	X_POS = playerPosition.x;
	float Y_POS = playerPosition.y;
	if(m_Position.x < X_POS)
	{
		m_Position.x += m_Speed*deltaTime;
	}
	if(m_Position.x > X_POS)
	{
		m_Position.x -= m_Speed*deltaTime;
	}
	
	if(m_Position.y < Y_POS)
	{
		m_Position.y += m_Speed*deltaTime;
	}
	if(m_Position.y > Y_POS)
	{
		m_Position.y -= m_Speed*deltaTime;
	}


	float angle = atan2(playerPosition.y - m_Position.y , playerPosition.x - m_Position.x) * (180/3.141);

	m_Sprite.setPosition(m_Position);
	m_Sprite.setRotation(angle);
}
