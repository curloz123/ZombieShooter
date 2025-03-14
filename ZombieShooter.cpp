#include "Player.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Err.hpp>
#include<cmath>
#include "ZombieArena.h"
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include<SFML/Audio.hpp>
#include "textureHolder.h"
#include "Bullet.h"
#include "Pickup.h"
#include<iostream>
#include<sstream>
#include<fstream>

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
	int numZombiesAlive;
	zombie* zombies = nullptr;

	bullet bullets[100];
	int bulletSpare = 150;
	int bulletsinClip = 30;
	int clipSize = 30;
	int currentBullet = 0;
	float rateofFire = 1;
	sf::Time lastPressed;

	window.setMouseCursorVisible(false);
	sf::Sprite playerCrosshair;
	playerCrosshair.setTexture(textureHolder::getTexture("graphics/crosshair.png"));
	playerCrosshair.setOrigin(25,25);

	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	int score = 0;
	int highScore = 0;

	std::ifstream inputFile("gamedata/score.txt");
	if(inputFile.is_open())
	{
		inputFile >> highScore;
		inputFile.close();
	}

	sf::Sprite spriteGameOver;
	sf::Texture gameOverTexture = textureHolder::getTexture("graphics/background.png"); 
	spriteGameOver.setTexture(gameOverTexture);
	spriteGameOver.setPosition(0,0);

	sf::View hudView(sf::FloatRect(0,0,resolution.x,resolution.y));

	sf::Sprite spriteAmmoIcon;
	sf::Texture textureAmmoIcon = textureHolder::getTexture("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	sf::Font font;
	font.loadFromFile("fonts/zombiecontrol.ttf");

	sf::Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(sf::Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(250, 850);
	gameOverText.setString("Press Enter to play");

	sf::Text LeveLLingUpText;
	LeveLLingUpText.setFont(font);
	LeveLLingUpText.setCharacterSize(80);
	LeveLLingUpText.setFillColor(sf::Color::White);
	LeveLLingUpText.setPosition(150,250);
	std::stringstream levelUpStream;
	levelUpStream <<
	"1- Increased rate of fire" <<
	"\n2- Increased clip size(next reload)" <<
	"\n3- Increased max health" <<
	"\n4- Increased run speed" <<
	"\n5- More and better health pickups" <<
	"\n6- More and better ammo pickups";
	LeveLLingUpText.setString( levelUpStream.str() );

	// Ammo
	sf::Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setPosition(200, 980);
	
	// Score
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(20, 0);
	// Hi Score
	sf::Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color::White);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;
	s << "Highest Score:" << highScore;
	hiScoreText.setString(s.str());

// Zombies remaining
	sf::Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(sf::Color::White);
	zombiesRemainingText.setPosition(1500, 980);
	zombiesRemainingText.setString("Zombies: 100");
	// Wave number
	int wave = 0;
	sf::Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(sf::Color::White);
	waveNumberText.setPosition(1250, 980);
	waveNumberText.setString("Wave: 0");
	// Health bar
	sf::RectangleShape healthBar;
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setPosition(450, 980);

	float timeSinceLastUpdate = 0;
	int UpdateInterval = 100;

	//Preparing Sounds
	
	sf::SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	sf::Sound Hit;
	Hit.setBuffer(hitBuffer);

	sf::SoundBuffer splatBuffer;
	splatBuffer.loadFromFile("sound/splat.wav");
	sf::Sound Splat;
	Splat.setBuffer(splatBuffer);

	sf::SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sound/shoot.wav");
	sf::Sound Shoot;
	Shoot.setBuffer(shootBuffer);

	sf::SoundBuffer reloadBuffer;
	reloadBuffer.loadFromFile("sound/reload.wav");
	sf::Sound Reload;
	Reload.setBuffer(reloadBuffer);

	sf::SoundBuffer reloadfailedBuffer;
	reloadfailedBuffer.loadFromFile("sound/reload_failed.wav");
	sf::Sound reloadFailed;
	reloadFailed.setBuffer(reloadfailedBuffer);

	sf::SoundBuffer powerupBuffer;
	powerupBuffer.loadFromFile("sound/powerup.wav");
	sf::Sound powerup;
	powerup.setBuffer(powerupBuffer);

	sf::SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("sound/pickup.wav");
	sf::Sound pickup;
	pickup.setBuffer(pickupBuffer);

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
					wave = 0;
					score = 0;
					currentBullet = 0;
					bulletSpare = 150;
					bulletsinClip = 30;
					clipSize = 30;
					rateofFire = 1;

					player.ResetPlayerStats();
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
							Reload.play();
						}
						else if(bulletSpare > 0 )
						{
							bulletsinClip = bulletSpare;
							bulletSpare = 0;
							Reload.play();
						}
						else
						{
							reloadFailed.play();
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
				if(gameTime.asMilliseconds() - lastPressed.asMilliseconds() > 400/rateofFire && bulletsinClip>0)
				{
					Shoot.play();
					bullets[currentBullet].shoot(player.getCenter().x , player.getCenter().y ,
							MOUSE_worldPosition.x , MOUSE_worldPosition.y);
					++currentBullet;
					if(currentBullet > 99)
					{
						currentBullet = 0;
					}
					--bulletsinClip;
					lastPressed = gameTime;
				}
			}
		}//End of isPlaying if block
		
		if(state == STATE::LEVELLING_UP)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				++rateofFire;
				if(rateofFire > 4)
				{
					rateofFire = 4;
				}
				state = STATE::PLAYING;
				
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				clipSize += 5;
				if(clipSize >= 50)
				{
					clipSize = 50;
				}
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num3)
			{	
				player.increaseMaxHealth();
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num4)
			{
				player.upgradeSpeed();
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num5)
			{
				healthPickup.upgrade();
				state = STATE::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num6)
			{
				ammoPickup.upgrade();
				state = STATE::PLAYING;
			}
			
			if(state == STATE::PLAYING)
			{
				//Preparing the level
				++wave;
				arena.width = 250 * (wave+1);
				arena.height = 250 * (wave+1);
				arena.left = 0;
				arena.top = 0;

				
				int tileSize = createBackground(backGround , arena );
				player.spawn(arena , resolution , tileSize);
				score = 0;

				numZombies = 20 * wave;
				// numZombies = 3;
				numZombiesAlive = numZombies;
				delete[] zombies;
				zombies = createHorde(numZombies , arena);
				if(wave!=1)
				{
					for(int i=0;i<numZombies;++i)
					{
						zombies[i].upgrade();
					}
				}
				
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);

				powerup.play();	
				clock.restart();
				//ts << clock timings ko dekhna zara


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
			playerCrosshair.setPosition(MOUSE_worldPosition);


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
				bullets[j].update(dt.asSeconds(),arena);
			}

			healthPickup.update(dt.asSeconds());
			ammoPickup.update(dt.asSeconds());

			for(int i=0;i<100;++i)
			{
				for(int j=0;j<numZombies;++j)
				{
					if(bullets[i].inAir() && zombies[j].Alive())
					{
						int Zom_posX = zombies[j].getPos().x;
						int Zom_posY = zombies[j].getPos().y;
						int Bul_posX = bullets[i].getPos().x;
						int Bul_posY = bullets[i].getPos().y;
						if(pow(pow(Zom_posY-Bul_posY,2)+pow(Zom_posX-Bul_posX,2),0.5)<=40)
						{
							Splat.play();
							bullets[i].stop();
							if(zombies[j].Hit())
							{
								score += 10;
								--numZombiesAlive;
								if(highScore < score)
								{
									highScore = score;
								}
								if(numZombiesAlive == 0)
								{
									state = STATE::LEVELLING_UP;
								}
							}
						}
					}
				}//
				
			}//
			bool registerHit = true;
			for(int i=0;i<numZombies;++i)
			{
				if(zombies[i].Alive())
				{
					int Zom_posX = zombies[i].getPos().x;
					int Zom_posY = zombies[i].getPos().y;
					int Plr_posX = player.getPos().x;
					int Plr_posY = player.getPos().y;

					if(pow(pow(Zom_posY - Plr_posY,2)+pow(Zom_posX - Plr_posX,2),0.5) <= 60 && registerHit)
					{
						registerHit = false;
						if(player.hit())
						{
							Hit.play();
							// std::cout<<player.getHealth()<<std::endl;
						}	
						if(player.getHealth()<=0)
						{
							state=STATE::GAME_OVER;
							std::ofstream outputFile("gamedata/score.txt");
							outputFile << highScore;
							outputFile.close();
						}
					}

				}
			}
			
			if(ammoPickup.isSpawned())
			{
				int amo_Pkp_posX = ammoPickup.getPos().x;
				int amo_Pkp_posY = ammoPickup.getPos().y;
				int Plr_posX = player.getPos().x;
				int Plr_posY = player.getPos().y;
				if(pow(pow(amo_Pkp_posY- Plr_posY,2)+pow(amo_Pkp_posX - Plr_posX,2),0.5) <= 50)
				{
					ammoPickup.gotIt();
					pickup.play();
					bulletSpare += 30;
				}
			}
			if(healthPickup.isSpawned())
			{
				int hlt_Pkp_posX = healthPickup.getPos().x;
				int hlt_Pkp_posY = healthPickup.getPos().y;
				int Plr_posX = player.getPos().x;
				int Plr_posY = player.getPos().y;
				if(pow(pow(hlt_Pkp_posY- Plr_posY,2)+pow(hlt_Pkp_posX - Plr_posX,2),0.5) <= 50)
				{
					healthPickup.gotIt();
					pickup.play();
					player.recoverHealth();
				}
					
			}
			
			healthBar.setSize( sf::Vector2f( player.getHealth() * 3 , 50 ) );
			timeSinceLastUpdate += dtasSeconds*1000.0f;

			std::stringstream ss_Ammo;
			std::stringstream ss_Score;
			std::stringstream ss_Wave;
			std::stringstream ss_aliveZombies;
			std::stringstream ss_hiScore;

			if(timeSinceLastUpdate > UpdateInterval)
			{
				ss_Ammo<<bulletsinClip<<"/"<<bulletSpare;
				ammoText.setString(ss_Ammo.str());

				ss_Score<<"Score: "<<score;
				scoreText.setString(ss_Score.str());

				ss_Wave<<"Wave: "<<wave;
				waveNumberText.setString(ss_Wave.str());

				ss_aliveZombies<<"Zombies Alive: "<<numZombiesAlive;
				zombiesRemainingText.setString(ss_aliveZombies.str());

				ss_hiScore<<"High Score: "<<highScore;
				hiScoreText.setString(ss_hiScore.str());

				timeSinceLastUpdate = 0;
			}
		
		}//End of isPlaying enum Part Update

	
		if(state == STATE::PLAYING)
		{
			window.clear();
			window.setView(mainView);
			window.draw(backGround , &bgTexture );
			window.draw(player.getSprite());
			
			if(ammoPickup.isSpawned())
			{
				window.draw(ammoPickup.getSprite());
			}
			if(healthPickup.isSpawned())
			{
				window.draw(healthPickup.getSprite());
			}
			for(int i=0;i<numZombies;++i)
			{
				window.draw(zombies[i].getSprite());
			}
			for(int j=0;j<100;++j)
			{
				if(bullets[j].inAir())
				{
					window.draw(bullets[j].getShape());
				}
			}

			window.draw(playerCrosshair);

			window.setView(hudView);
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(zombiesRemainingText);
			window.draw(waveNumberText);
			window.draw(healthBar);

		}

		if(state == STATE::LEVELLING_UP)
		{
			window.draw(spriteGameOver);
			window.draw(LeveLLingUpText);
		}
		
		if(state == STATE::PAUSED)
		{
			window.draw(pausedText);
		}

		if(state == STATE::GAME_OVER)
		{
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
		}

			window.display();

	}//End of Game loop
	 

	delete[] zombies;

	return 0;
}

