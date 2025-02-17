#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class bullet
{
	private:
	
	sf::Vector2f m_Position;
	sf::RectangleShape m_bullettShape;
	
	bool m_inAir;
	int m_Speed = 1000;

	float m_VELOCITY_X;
	float m_VELOCITY_Y;

	// float m_maxX;
	// float m_maxY;

	
	public:
		
	bullet();

	void mf_stop();
	void mf_shoot(float startX , float startY ,
							 float targetX , float targetY);

	bool mf_inAir();
	sf::FloatRect getPositiion();
	sf::RectangleShape getShape();
	void update(float deltaTime);
};
