#include "ZombieArena.h"
#include "Zombie.h"
#include <SFML/Graphics/Rect.hpp>

zombie* createHorde(int numZombies , sf::IntRect arena)
{
	zombie* zombies = new zombie[numZombies];

	int minY = arena.top + 20;
	int maxY = arena.height -20;
	int minX = arena.left + 20;
	int maxX = arena.width - 20;

	for(int i=0 ; i<numZombies ; ++i)
	{
		int side = rand()%4;
		float x,y;
		switch(side)
		{
			case 0:
				//left
				x = minX;
				y = (rand()%maxY) + minY;
				break;

			case 1:
				//right
				x = maxX;
				y = (rand()%maxY) + minY;
				break;

			case 2:
				//top
				y = minY;
				x = (rand()%maxX) + minX;
				break;

			case 3:
				//bottom
				y = maxY;
				x = (rand()%maxX) + minX;
				break;
		}

		int type = rand()%3;
		zombies[i].spawn(x,y,type);
	}

	return zombies;
}

