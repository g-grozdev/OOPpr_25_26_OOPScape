#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "HeroFactory.h"
#include "EnemyFactory.h"
#include "TileFactory.h"

class Labyrinth
{
	std::vector<std::vector<Tile>> tiles;
	std::shared_ptr<Hero> hero;
	std::shared_ptr<Target> target;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::shared_ptr<std::vector<std::vector<int>>> prev;
	std::shared_ptr<std::queue<int>> visited;
	int move_counter;

	bool create_from_character(char character, int x, int y, int row);
	void create_prev_and_visited(int size);

	int play_game_state();
	void get_player_action();
	int check_state();
	void print();

public:
	Labyrinth(const char* file_name);
	int play();
};

