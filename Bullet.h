#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class bullet
{
	private:
	
	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	
	bool m_inAir;
	int m_Speed = 1000;

	float m_VELOCITY_X;
	float m_VELOCITY_Y;

	// float m_maxX;
	// float m_maxY;

	
	public:
		
	bullet();

	void stop();
	void shoot(float startX , float startY ,
							 float targetX , float targetY);

	bool inAir();
	sf::Vector2f getPos();

	sf::Sprite getShape();
	void update(float deltaTime, sf::IntRect arena);
};
