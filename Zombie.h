#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class zombie
{
	const int BLOATER_SPEED = 30;
	const int CHASER_SPEED = 80;
	const int CRAWLER_SPEED = 50;

	const int BLOATER_HEALTH = 5;
	const int CHASER_HEALTH = 1;
	const int CRAWLER_HEALTH = 3;
	
	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	
	float m_Health;
	float m_Speed;

	bool m_Alive;


	public:
	
	bool Hit();
	bool Alive();
	void spawn(float startX , float startY ,int type, int speed);
	sf::FloatRect getPosition();
	sf::Sprite getSprite();
	void update(float deltaTime , sf::Vector2f playerPosition);

};
