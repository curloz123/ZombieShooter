#include "Player.h"
#include "ZombieArena.h"
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "textureHolder.h"
#include "Bullet.h"
int main()
{
	textureHolder texture;

	enum class STATE {PLAYING, GAME_OVER , PAUSED , LEVELLING_UP};
	STATE state = STATE::GAME_OVER;

	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(resolution.x , resolution.y) , 
			"Zombie Shooter" , sf::Style::Fullscreen);

	sf::View mainView(sf::FloatRect(0,0,resolution.x , resolution.y));

	sf::Clock clock;
	sf::Time gameTime;

	sf::Vector2f MOUSE_worldPosition;
	sf::Vector2i MOUSE_screenPosition;

	Player player;

	sf::IntRect arena;

	sf::VertexArray backGround;
	sf::Texture bgTexture;
	bgTexture.loadFromFile("graphics/background_sheet.png");

	int numZombies;
	zombie* zombies = nullptr;

	bullet bullets[100];
	int bulletSpare = 24;
	int bulletsinClip = 6;
	int clipSize = 6;
	int currentBullet = 0;
	int rateofFire = 1;
	sf::Time lastPressed;
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Return && state == STATE::PLAYING)
				{
					state = STATE::PAUSED;
				}
				else if(event.key.code == sf::Keyboard::Return && state == STATE::PAUSED)
				{
					state = STATE::PLAYING;
					clock.restart();
				}
				else if(event.key.code == sf::Keyboard::Return && state == STATE::GAME_OVER)
				{
					state = STATE::LEVELLING_UP;
				}
				if(state == STATE::PLAYING)
				{
					if(event.key.code == sf::Keyboard::R)
					{
						//Reloading
						if(bulletSpare >= clipSize )
						{ 
							bulletsinClip = clipSize;	
							bulletSpare -= clipSize;
						}
						else if(bulletSpare > 0 && bulletsinClip !=clipSize)
						{
							bulletsinClip = bulletSpare;
							bulletSpare = 0;
						}
						else
						{

						}
					}//end of Reloading if
				}//end of state = playing
			}//End of if Key Pressed

		}//End of Event loop
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		if(state == STATE::PLAYING)
		{

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.moveLeft();;
			}
			else
			{
				player.stopLeft();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.moveDown();
			}
			else
			{		
				player.stopDown();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.moveRight();;
			}
			else
			{
				player.stopRight();
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if(gameTime.asMilliseconds() - lastPressed.asMilliseconds() > 1000 && bulletsinClip>0)
				{
					bullets[currentBullet].mf_shoot(player.getCenter().x , player.getCenter().y ,
							MOUSE_worldPosition.x , MOUSE_worldPosition.y);
					++currentBullet;
					if(currentBullet > 100)
					{
						currentBullet = 0;
					}
					--bulletsinClip;
				}
			}
		}//End of isPlaying if block
		
		if(state == STATE::LEVELLING_UP)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num3)
			{	
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num4)
			{
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num5)
			{
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num6)
			{
				state = STATE::PLAYING;
			}
			
			if(state == STATE::PLAYING)
			{
				//Preparing the level
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				int tileSize = createBackground(backGround , arena );
				player.spawn(arena , resolution , tileSize);

				numZombies = 10;
				delete[] zombies;
				zombies = createHorde(numZombies , arena);
				clock.restart();


			}
		}//End of levelling up state
		 
		if(state == STATE::PLAYING)
		{
			sf::Time dt = clock.restart();
			gameTime += dt;
			float dtasSeconds = dt.asSeconds();
			MOUSE_screenPosition = sf::Mouse::getPosition();
			MOUSE_worldPosition = window.mapPixelToCoords(sf::Mouse::getPosition() , mainView);
			player.update(dtasSeconds , sf::Mouse::getPosition());

			sf::Vector2f playerPosition(player.getCenter());
			mainView.setCenter(player.getCenter());

			for(int i=0;i<numZombies;++i)
			{
				if(zombies[i].Alive())
				{
					zombies[i].update(dt.asSeconds() , playerPosition);
				}
			}

			for(int j=0;j<100;++j)
			{
				bullets[j].update(dt.asSeconds());
			}
		}

	
		if(state == STATE::PLAYING)
		{
			window.clear();
			window.setView(mainView);
			window.draw(backGround , &bgTexture );
			window.draw(player.getSprite());
			
			for(int i=0;i<numZombies;++i)
			{
				window.draw(zombies[i].getSprite());
			}
			for(int j=0;j<100;++j)
			{
				if(bullets[j].mf_inAir())
				{
					window.draw(bullets[j].getShape());
				}
			}
		}

		window.display();
	}//End of Game loop
	 

	delete[] zombies;

	return 0;
}
