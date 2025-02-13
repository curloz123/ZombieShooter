#pragma once
#ifndef ZOMBIE_ARENA_H
#define ZOMBIE_ARENA_H

#include <SFML/Config.hpp>
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "Zombie.h"

int createBackground(sf::VertexArray& rVA , sf::IntRect arena);

zombie* createHorde(int numZombies , sf::IntRect arena);


#endif

