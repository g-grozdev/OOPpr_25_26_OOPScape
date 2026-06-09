#pragma once
#include <iostream>
#include <fstream>
#include <string>
// for clearing screen
#include <stdlib.h>
//for sleeping thread so attacks can be seen
#include <windows.h>
#include "HeroFactory.h"
#include "EnemyFactory.h"
#include "TileFactory.h"
#include "GameFileException.h"
#include "GameFileDimensionsException.h"
#include "GameFileLayoutException.h"

class Labyrinth
{
	std::vector<std::vector<Tile>> tiles;
	std::shared_ptr<Hero> hero;
	std::shared_ptr<Target> target;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::shared_ptr<std::vector<std::vector<int>>> prev;
	std::shared_ptr<std::queue<int>> visited;
	std::queue<Position> affected_tiles;
	std::vector<std::vector<char>> display;
	std::vector<std::vector<bool>> colored;
	std::string affected_tiles_color;
	const std::string affected_tiles_color_reset;
	int move_counter;

	bool create_from_character(char character, int x, int y, int row, bool has_end_already);
	void create_prev_and_visited(int size);
	void create_display_and_colored(int size);
	int convert_coordinates(int x, int y, int n);
	int convert_x_coordinate(int c, int n);
	int convert_y_coordinate(int c, int n);
	void reset_prev(int n);
	void reset_display_and_colored(int n);
	void reset_affected_tiles_color();
	void set_affected_tiles_color_attack();
	void set_affected_tiles_color_ability();
	void get_display(int n);

	int play_game_state();
	int get_player_action();
	int check_state();
	bool apply_attack(const Weapon& wp, bool hero_or_enemy);
	bool is_in_bounds(int x, int y, int n);
	void apply_AOE(const Position& impact, const Weapon& wp, bool hero_or_enemy);
	bool hits_an_oponent(const Position& pos, bool hero_or_enemy);
	bool is_within_AOE(int x1, int y1, int x2, int y2, int AOE);
	void damage_oponents(const Position& pos, const Weapon& wp, bool hero_or_enemy);

	void clear_enemies();
	void print();
	void print_to_console();

public:
	Labyrinth(const char* file_name);
	int play();
};

