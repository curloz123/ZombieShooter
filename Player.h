#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include<cmath>

class Player{
private:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
	sf::Vector2f m_Position;
	float startHealth = 100.0f;
	float startSpeed = 200.0f;
	sf::Vector2f m_Resolution;
	sf::IntRect m_arenaSize;
	int m_tileSize;

	bool m_KEYPRESSED_UP;
	bool m_KEYPRESSED_DOWN;
	bool m_KEYPRESSED_LEFT;
	bool m_KEYPRESSED_RIGHT;

	int m_Health;
	int m_maxHealth;
	float m_Speed;
	float m_lastHit;

public:
	Player();
	void spawn(sf::IntRect arena , sf::Vector2f resolution , int tileSize);
	void ResetPlayerStats();
	bool hit(sf::Time timeHit);
	// sf::Time getLasthittime();
	sf::Vector2f getPos();
	sf::Vector2f getCenter();
	float getRotation();
	sf::Sprite getSprite();
	void setHealth(int health);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	void update(float elapsedTime , sf::Vector2i mousePosition);
	void upgradeSpeed();
	void recoverHealth();
	void increaseMaxHealth();
	int getHealth();

};
