#include "Zombie.h"
#include "textureHolder.h"
#include <SFML/System/Vector2.hpp>
#include<ctime>
#include<cstdlib>

void zombie::spawn(float startX , float startY , int type , int speed)
{
	srand(time(0));
	switch (type)
	{
		case 0:
			//bloater
			m_Sprite.setTexture(textureHolder::getTexture("graphics/bloater.png:"));
			m_Speed = BLOATER_SPEED;
			m_Health = BLOATER_HEALTH;
			break;

		case 1:
			//crawler
			m_Sprite.setTexture(textureHolder::getTexture("graphics/crawler.png:"));
			m_Speed = CRAWLER_SPEED;
			m_Health = CRAWLER_HEALTH;
			break;
		case 2:
			//bloater
			m_Sprite.setTexture(textureHolder::getTexture("graphics/chaser.png:"));
			m_Speed = CHASER_SPEED;
			m_Health = CHASER_HEALTH;
			break;
	}

	float random = rand()%4;
	m_Speed = m_Speed*(1-random/10.0f);

	m_Position = sf::Vector2f(startX , startY);
	m_Sprite.setOrigin(25,25);


}
	

