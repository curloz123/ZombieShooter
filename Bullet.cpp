#include "Bullet.h"
#include <SFML/Graphics/Texture.hpp>
#include<cmath>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "textureHolder.h"

bullet::bullet()
{
	m_Sprite.setTexture(textureHolder::getTexture("graphics/ammo.png"))	;
	m_Sprite.setOrigin(4,19);
	m_inAir = false;
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
	return m_Sprite.getGlobalBounds();
}

sf::Sprite bullet::getShape()
{
	return m_Sprite;
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

	m_Sprite.setRotation(atan2((targetY-startY),(targetX-startX))*(180/3.141) + 90);
	m_Sprite.setPosition(m_Position);
}


void bullet::update(float deltaTime, sf::IntRect arena)
{
	m_Position.x += m_VELOCITY_X * deltaTime;
	m_Position.y += m_VELOCITY_Y * deltaTime;
	if(m_Position.x < -3000 || m_Position.x > 3000
			|| m_Position.y < -3000 || m_Position.y > 3000)
	{
		m_inAir = false;
	}
	m_Sprite.setPosition(m_Position);

}
