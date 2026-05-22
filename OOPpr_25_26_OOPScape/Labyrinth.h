#pragma once
#include <fstream>
#include "HeroFactory.h"
#include "EnemyFactory.h"
#include "TileFactory.h"

class Labyrinth
{
	std::vector<std::vector<Tile>> tiles;
	std::shared_ptr<Hero> hero;
	std::shared_ptr<Target> target;
	std::vector<std::unique_ptr<Enemy>> enemies;
	int move_counter;

public:
	Labyrinth(const char* file_name);

	bool create_from_character(char character, int x, int y, int row);
};

