#include"Player.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include<iostream>

Player::Player()
{
	m_Health = startHealth;
	m_Speed = startSpeed;
	m_maxHealth = startHealth;
	m_lastHit = 0;

	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(25,25);
}

void Player::spawn(sf::IntRect arena , sf::Vector2f resolution , int tileSize)
{
	m_Position.x = arena.width/2.0f;
	m_Position.y = arena.height/2.0f;
	
	m_arenaSize.height = arena.height;
	m_arenaSize.width = arena.width;
	m_arenaSize.left = arena.left;
	m_arenaSize.top = arena.top;

	m_tileSize = tileSize;

	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

}

void Player::ResetPlayerStats()
{
	m_Health = startHealth;
	m_Speed = startSpeed;
	m_maxHealth = startHealth;
}

bool Player::hit(sf::Time timeHit )
{
	m_lastHit += timeHit.asSeconds() * 1000.0f;
	if(m_lastHit > 500)
	{
		m_lastHit = 0;
		m_Health -= 10;
		return true;
	}
	return false;
}
 
// sf::Time Player::getLasthittime()
// {
// 	return m_lastHit;
// }

sf::Sprite Player::getSprite()
{
	return m_Sprite;
}

sf::Vector2f Player::getPos()
{
	return m_Sprite.getPosition();
}

sf::Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

int Player::getHealth()
{
	return m_Health;
}

void Player::moveLeft()
{
	m_KEYPRESSED_LEFT = true;
}
void Player::moveRight()
{
	m_KEYPRESSED_RIGHT = true;
}
void Player::moveUp()
{
	m_KEYPRESSED_UP = true;
}
void Player::moveDown()
{
	m_KEYPRESSED_DOWN = true;
}
void Player::stopLeft()
{
	m_KEYPRESSED_LEFT = false;
}
void Player::stopRight()
{
	m_KEYPRESSED_RIGHT = false;
}
void Player::stopUp()
{
	m_KEYPRESSED_UP = false;
}
void Player::stopDown()
{
	m_KEYPRESSED_DOWN = false;
}

void Player::update(float elapsedTime , sf::Vector2i mousePosition)
{
	if(m_KEYPRESSED_UP)
	{
		m_Position.y -= elapsedTime*m_Speed;
	}
	if(m_KEYPRESSED_DOWN)
	{
		m_Position.y += elapsedTime * m_Speed;
	}
	if(m_KEYPRESSED_LEFT)
	{
		m_Position.x -= elapsedTime * m_Speed;
	}
	if(m_KEYPRESSED_RIGHT)
	{
		m_Position.x += elapsedTime * m_Speed;
	}
	
	m_Sprite.setPosition(m_Position);

	if(m_Position.x > m_arenaSize.width - m_tileSize)
	{
		m_Position.x = m_arenaSize.width - m_tileSize;
	}
	if(m_Position.x < m_arenaSize.left + m_tileSize)
	{
		m_Position.x = m_arenaSize.left + m_tileSize;
	}
	if(m_Position.y > m_arenaSize.height - m_tileSize)
	{
		m_Position.y = m_arenaSize.height - m_tileSize;
	}
	if(m_Position.y < m_arenaSize.top + m_tileSize)
	{
		m_Position.y = m_arenaSize.top + m_tileSize;
	}

	float angle = (atan2((mousePosition.y - m_Resolution.y/2) , (mousePosition.x - m_Resolution.x/2))*180)/3.141;
	m_Sprite.setRotation(angle);

}

void Player::upgradeSpeed()
{
	m_Speed += startSpeed*0.2f;
}

void Player::recoverHealth()
{
	m_Health += startHealth * 0.2f;
	if(m_Health > m_maxHealth)
	{
		m_Health = m_maxHealth;
	}
}

void Player::increaseMaxHealth()
{
	m_maxHealth += startHealth * 0.2f;
}

void Player::setHealth(int health)
{
	m_Health = health;
}
