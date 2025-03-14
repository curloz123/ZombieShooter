#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class zombie
{
	const int BLOATER_SPEED = 30;
	const int CHASER_SPEED = 80;
	const int CRAWLER_SPEED = 40;

	const int BLOATER_HEALTH = 15;
	const int CHASER_HEALTH = 3;
	const int CRAWLER_HEALTH = 5;

	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	
	float m_Health;
	float m_Speed;

	bool m_Alive;


	public:
	
	bool Hit();
	bool Alive();
	void spawn(float startX , float startY ,int type);
	sf::Vector2f getPos();
	sf::Sprite getSprite();
	void update(float deltaTime , sf::Vector2f playerPosition);
	void upgrade();

};


#endif
