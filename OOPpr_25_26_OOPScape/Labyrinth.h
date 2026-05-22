#pragma once
#include <iostream>
#include <fstream>
#include <string>
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

	bool create_from_character(char character, int x, int y, int row);

	int play_game_state();
	int get_player_movement();
	void get_player_action();
	void get_player_attack();
	int check_state();

public:
	Labyrinth(const char* file_name);
	int play();
};

