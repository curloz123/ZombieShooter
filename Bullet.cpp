#include "Bullet.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

bullet::bullet()
{
	m_bullettShape.setSize(sf::Vector2f(2,2));
}

void bullet::mf_stop()
{
	m_inAir=false;
}

bool bullet::mf_inAir()
{
	return m_inAir;
}

sf::FloatRect bullet::getPositiion()
{
	return m_bullettShape.getGlobalBounds();
}

sf::RectangleShape bullet::getShape()
{
	return m_bullettShape;
}

void bullet::mf_shoot(float startX , float startY ,float targetX , float targetY)
{
	m_inAir = true;
	m_Position.x = startX;
	m_Position.y = startY;

	float gradient = (targetX - startX)/(targetY - startY);
	if(gradient<0)
	{
		gradient *= -1;
	}
	
	m_VELOCITY_Y= m_Speed/(1+gradient);
	m_VELOCITY_X = m_VELOCITY_Y * gradient;

	if(targetX < startX)
	{
		m_VELOCITY_X *= -1;
	}
	if(targetY < startY)
	{
		m_VELOCITY_X *= -1;
	}

	m_bullettShape.setPosition(m_Position);
}


void bullet::update(float deltaTime)
{
	m_Position.x += m_VELOCITY_X * deltaTime;
	m_Position.y += m_VELOCITY_Y * deltaTime;
	if(m_Position.x < 0 || m_Position.x > 1920 
			|| m_Position.y < 0 || m_Position.y >1080)
	{
		m_inAir = false;
	}

}
