#include "Bullet.h"
#include<cmath>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

bullet::bullet()
{
	m_bullettShape.setSize(sf::Vector2f(8,8));
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
	
	m_VELOCITY_Y= m_Speed/pow((1+(gradient*gradient)),0.5);
	m_VELOCITY_X = m_VELOCITY_Y * gradient;

	if(targetX < startX)
	{
		m_VELOCITY_X *= -1;
	}
	if(targetY < startY)
	{
		m_VELOCITY_Y *= -1;
	}

	m_bullettShape.setPosition(m_Position);
}


void bullet::update(float deltaTime, sf::IntRect arena)
{
	m_Position.x += m_VELOCITY_X * deltaTime;
	m_Position.y += m_VELOCITY_Y * deltaTime;
	if(m_Position.x < arena.left || m_Position.x > arena.width
			|| m_Position.y < arena.top || m_Position.y >arena.height)
	{
		m_inAir = false;
	}
	m_bullettShape.setPosition(m_Position);

}
