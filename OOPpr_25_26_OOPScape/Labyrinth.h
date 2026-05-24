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
	std::queue<Position> attacked;
	int move_counter;

	bool create_from_character(char character, int x, int y, int row);
	void create_prev_and_visited(int size);
	int convert_coordinates(int x, int y, int n);
	int convert_x_coordinate(int c, int n);
	int convert_y_coordinate(int c, int n);
	void reset_prev(int n);

	int play_game_state();
	void get_player_action();
	int check_state();
	void apply_attack(const Weapon& wp, bool hero_or_enemy);
	bool is_in_bounds(int x, int y, int n);
	void apply_AOE(Position impact, const Weapon& wp, bool hero_or_enemy);
	bool hits_an_oponent(Position pos, bool hero_or_enemy);
	bool is_within_AOE(int x1, int y1, int x2, int y2, int AOE);
	void damage_oponents(Position pos, const Weapon& wp, bool hero_or_enemy);

	void clear_enemies();
	void print();

public:
	Labyrinth(const char* file_name);
	int play();
};

