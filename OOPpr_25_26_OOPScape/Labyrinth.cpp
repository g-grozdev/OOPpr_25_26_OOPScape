#include "Labyrinth.h"

bool Labyrinth::create_from_character(char character, int x, int y, int row, bool has_end_already)
{
	if (character == '\n' || character == '\0')
	{
		throw GameFileLayoutException("labyrinth layout does not fit dimensions", x, y);
	}
	bool has_end = false;
	if (character == 'F')
	{
		if (has_end_already) 
		{
			throw GameFileException("labyrinth has more than one exit");
		}
		has_end = true;
		tiles[row].push_back(TileFactory::create_tile(character, x, y));
	}
	else if (character >= 'A' && character <= 'Z')
	{
		if (hero != nullptr)
		{
			throw GameFileException("labyrinth has more than one hero");
		}
		hero = HeroFactory::create_hero(character, x, y, move_counter);
		target = hero;
		tiles[row].push_back(TileFactory::create_tile(' ', x, y));
	}
	else if (character >= 'a' && character <= 'z')
	{
		enemies.push_back(EnemyFactory::create_enemy(character, x, y, move_counter));
		tiles[row].push_back(TileFactory::create_tile(' ', x, y));
	}
	else
	{
		tiles[row].push_back(TileFactory::create_tile(character, x, y));
	}
	return has_end;
}

void Labyrinth::create_prev_and_visited(int size)
{
	std::shared_ptr<std::vector<std::vector<int>>> prev_AOE;
	prev_AOE = std::make_shared<std::vector<std::vector<int>>>();
	std::shared_ptr<std::queue<int>> visited_AOE;
	visited_AOE = std::make_shared<std::queue<int>>();

	prev = std::make_shared<std::vector<std::vector<int>>>();
	visited = std::make_shared<std::queue<int>>();

	for (int i = 0; i < size; i++) 
	{
		(*prev.get()).push_back(std::vector<int>());
		(*prev_AOE.get()).push_back(std::vector<int>());
		for (int j = 0; j < size; j++) 
		{
			(*prev.get())[i].push_back(-1);
			(*prev_AOE.get())[i].push_back(-1);
		}
	}

	for (int i = 0; i < enemies.size(); i++) 
	{
		(*enemies[i].get()).set_prev(prev);
		(*enemies[i].get()).set_prev_AOE(prev_AOE);
		(*enemies[i].get()).set_visited(visited);
		(*enemies[i].get()).set_visited_AOE(visited_AOE);
	}
}

void Labyrinth::create_display_and_colored(int size)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		display.push_back(std::vector<char>());
		colored.push_back(std::vector<bool>());
		for (int j = 0; j < tiles.size(); j++)
		{
			colored[i].push_back(false);
			display[i].push_back('\0');
		}
	}
}

int Labyrinth::convert_coordinates(int x, int y, int n)
{
	return x * n + y;
}

int Labyrinth::convert_x_coordinate(int c, int n)
{
	return c / n;
}

int Labyrinth::convert_y_coordinate(int c, int n)
{
	return c % n;
}

void Labyrinth::reset_prev(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(*prev.get())[i][j] = -1;
		}
	}
}

void Labyrinth::reset_display_and_colored(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			colored[i][j] = false;
			display[i][j] = '\0';
		}
	}
}

void Labyrinth::reset_affected_tiles_color()
{
	affected_tiles_color = "\033[48;2;0;0;0m";
}

void Labyrinth::set_affected_tiles_color_attack()
{
	affected_tiles_color = "\033[48;2;224;55;29m";
}

void Labyrinth::set_affected_tiles_color_ability()
{
	affected_tiles_color = "\033[48;2;10;130;44m";
}

void Labyrinth::get_display(int n)
{
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			display[i][j] = tiles[i][j].get_display_char();
		}
	}
}

int Labyrinth::play_game_state()
{
	print();
	reset_affected_tiles_color();

	bool success = true;
	do
	{
		if (!success) 
		{
			std::cout << "invalid movement please try again\n";
		}
		success = (*hero.get()).move(tiles, target, hero);
	} while (!success);

	print();
	reset_affected_tiles_color();

	if (check_state() == 1) 
	{
		return 1;
	}
	else if (check_state() == -1) 
	{
		return -1;
	}

	for (int i = 0; i < enemies.size(); i++) 
	{
		(*enemies[i].get()).move(tiles, target, hero);
	}

	print();
	reset_affected_tiles_color();

	// apply player action
	success = true;
	do
	{
		if (!success)
		{
			print();
			reset_affected_tiles_color();
			std::cout << "invalid action please try again\n";
		}
		success = get_player_action();
	} while (!success);

	Sleep(650);

	print();
	reset_affected_tiles_color();

	Sleep(1000);

	for (int i = 0; i < enemies.size(); i++) 
	{
		// apply enemy attack
		set_affected_tiles_color_attack();
		apply_attack((*enemies[i].get()).attack(tiles, target, hero), false);
	}

	print();
	reset_affected_tiles_color();

	Sleep(1000);

	if (check_state() == 1)
	{
		return 1;
	}
	else if (check_state() == -1)
	{
		return -1;
	}

	return 0;
}

bool Labyrinth::get_player_action()
{
	std::cout << "Enter a command for an action : X (attack) ; A (ability) ; S (skip action)\n";
	std::string command = "";
	std::getline(std::cin, command);
	while (command != "X" && command != "A" && command != "S")
	{
		std::cout << "Invalid command please try again\n";
		std::getline(std::cin, command);
	}

	if (command == "X") 
	{
		set_affected_tiles_color_attack();
		affected_tiles_color = "\033[48;2;224;55;29m";
		return apply_attack((*hero.get()).attack(tiles, target, hero), true);
	}
	else if (command == "A") 
	{
		set_affected_tiles_color_ability();
		(*hero.get()).get_affected_by_ability_tiles(tiles, target, hero, affected_tiles);
		print();
		//Sleep(650);
		return (*hero.get()).ability(tiles, target, hero);
	}
	else if (command == "S") 
	{
		reset_affected_tiles_color();
		return true;
	}

	return false;
}

int Labyrinth::check_state()
{
	if (target != nullptr && (*target.get()).get_hp() == 0) 
	{
		target = hero;
	}

	if ((*hero.get()).get_hp() == 0)
	{
		return -1;
	}
	else if (tiles[(*hero.get()).get_x()][(*hero.get()).get_y()].get_is_end())
	{
		return 1;
	}
	return 0;
}

bool Labyrinth::apply_attack(const Weapon& wp, bool hero_or_enemy)
{
	int attack_x = wp.get_start().get_x();
	int attack_y = wp.get_start().get_y();
	int direction = wp.get_direction();

	int n = tiles.size();
	int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
	bool prev = false;
	for (int i = 0; i <= wp.get_range() && is_in_bounds(attack_x, attack_y, n); i++)
	{
		if (!tiles[attack_x][attack_y].get_walkability())
		{
			if (!prev) 
			{
				attack_x -= dir[direction][0];
				attack_y -= dir[direction][1];
				// if attacks have a AOE (explode) once they reach their max range they explode
				if (wp.get_AOE() != 0)
				{
					apply_AOE(Position(attack_x, attack_y), wp, hero_or_enemy);
				}
			}
			break;
		}

		prev = false;

		if (hits_an_oponent(Position(attack_x, attack_y), hero_or_enemy))
		{
			apply_AOE(Position(attack_x, attack_y), wp, hero_or_enemy);
			if (!wp.get_pierce())
			{
				break;
			}
			prev = true;
		}

		if (i == wp.get_range() && !prev)
		{
			// if attacks have a AOE (explode) once they reach their max range they explode
			if (wp.get_AOE() != 0) 
			{
				apply_AOE(Position(attack_x, attack_y), wp, hero_or_enemy);
			}
		}

		attack_x += dir[direction][0];
		attack_y += dir[direction][1];
	}

	clear_enemies();

	return true;
}

bool Labyrinth::is_in_bounds(int x, int y, int n)
{
	return x > -1 && x < n && y > -1 && y < n;
}


void Labyrinth::apply_AOE(const Position& impact, const Weapon& wp, bool hero_or_enemy)
{
	int n = tiles.size();
	int AOE = wp.get_AOE();
	reset_prev(n);

	int init_x = impact.get_x();
	int init_y = impact.get_y();

	if (is_within_AOE(init_x, init_y, init_x, init_y, AOE))
	{
		(*visited.get()).push(convert_coordinates(init_x, init_y, n));
		(*prev.get())[init_x][init_y] = 0;
		damage_oponents(Position(init_x, init_y), wp, hero_or_enemy);
		affected_tiles.push(Position(init_x, init_y));
	}

	int dir[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

	while (!(*visited.get()).empty())
	{
		for (int i = (*visited.get()).size(); i > 0; i--)
		{
			int ind = (*visited.get()).front();
			int temp_x = convert_x_coordinate(ind, n);
			int temp_y = convert_y_coordinate(ind, n);
			int new_x = -1;
			int new_y = -1;
			for (int j = 0; j < 4; j++)
			{
				new_x = temp_x + dir[j][0];
				new_y = temp_y + dir[j][1];
				if (!is_in_bounds(new_x, new_y, n)) continue;
				if (tiles[new_x][new_y].get_walkability() && (*prev.get())[new_x][new_y] == -1
					&& is_within_AOE(new_x, new_y, init_x, init_y, AOE))
				{
					(*visited.get()).push(convert_coordinates(new_x, new_y, n));
					(*prev.get())[new_x][new_y] = 0;
					damage_oponents(Position(new_x, new_y), wp, hero_or_enemy);
					affected_tiles.push(Position(new_x, new_y));
				}
			}
			(*visited.get()).pop();
		}
	}
}

bool Labyrinth::hits_an_oponent(const Position& pos, bool hero_or_enemy)
{
	if (hero_or_enemy) 
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if ((*enemies[i].get()).get_x() == pos.get_x() && (*enemies[i].get()).get_y() == pos.get_y())
			{
				return true;
			}
		}
	}
	else 
	{
		if (((*target.get()).get_x() == pos.get_x() && (*target.get()).get_y() == pos.get_y())
			|| ((*hero.get()).get_x() == pos.get_x() && (*hero.get()).get_y() == pos.get_y()))
		{
			return true;
		}
	}
	return false;
}

bool Labyrinth::is_within_AOE(int x1, int y1, int x2, int y2, int AOE)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	return dx * dx + dy * dy <= AOE * AOE;
}

void Labyrinth::damage_oponents(const Position& pos, const Weapon& wp, bool hero_or_enemy)
{
	if (hero_or_enemy) 
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if ((*enemies[i].get()).get_x() == pos.get_x() && (*enemies[i].get()).get_y() == pos.get_y())
			{
				(*enemies[i].get()).take_damage(wp.get_damage());

				if (!wp.get_pierce() && wp.get_AOE() == 0) return;
			}
		}
	}
	else 
	{
		if (target.get() != hero.get()) 
		{
			if ((*target.get()).get_x() == pos.get_x() && (*target.get()).get_y() == pos.get_y())
			{
				(*target.get()).take_damage(wp.get_damage());
			}
			if (!wp.get_pierce() && wp.get_AOE() == 0) return;
			if ((*hero.get()).get_x() == pos.get_x() && (*hero.get()).get_y() == pos.get_y())
			{
				(*hero.get()).take_damage(wp.get_damage());
			}
		}
		else 
		{
			if ((*hero.get()).get_x() == pos.get_x() && (*hero.get()).get_y() == pos.get_y())
			{
				(*hero.get()).take_damage(wp.get_damage());
			}
		}
	}
}

void Labyrinth::clear_enemies()
{
	enemies.erase
	(
		std::remove_if(enemies.begin(), enemies.end(),
			[](const std::unique_ptr<Enemy>& enemy)
			{
				return (*enemy.get()).get_hp() == 0;
			}),
		enemies.end()
	);
}

void Labyrinth::print()
{
	std::system("CLS");

	reset_display_and_colored(tiles.size());

	get_display(tiles.size());

	while (!affected_tiles.empty()) 
	{
		int x = affected_tiles.front().get_x();
		int y = affected_tiles.front().get_y();
		colored[x][y] = true;
		affected_tiles.pop();
	}

	int x = -1;
	int y = -1;
	char d_c = '\0';

	if (target != nullptr) 
	{
		x = (*target.get()).get_x();
		y = (*target.get()).get_y();
		d_c = (*target.get()).get_display_char();
		display[x][y] = d_c;
	}

	for (int i = 0; i < enemies.size(); i++) 
	{
		int x = (*enemies[i].get()).get_x();
		int y = (*enemies[i].get()).get_y();
		char d_c = (*enemies[i].get()).get_display_char();
		display[x][y] = d_c;
	}

	x = (*hero.get()).get_x();
	y = (*hero.get()).get_y();
	d_c = (*hero.get()).get_display_char();
	display[x][y] = d_c;

	print_to_console();
}

void Labyrinth::print_to_console()
{
	std::cout << "   ";
	for (int i = 0; i < tiles.size(); i++)
	{
		std::cout << ' ';
		if (i < 10)
		{
			std::cout << i << ' ';
		}
		else
		{
			std::cout << i;
		}
	}
	std::cout << "\n   ";
	for (int i = 0; i < tiles.size(); i++) std::cout << "___";
	std::cout << '\n';
	for (int i = 0; i < tiles.size(); i++)
	{
		if (i < 10)
		{
			std::cout << ' ' << i;
		}
		else
		{
			std::cout << i;
		}
		std::cout << '|';
		for (int j = 0; j < tiles.size(); j++)
		{
			if (colored[i][j]) 
			{
				std::cout << ' ' << affected_tiles_color << display[i][j] << affected_tiles_color_reset << ' ';
			}
			else 
			{
				std::cout << ' ' << display[i][j] << ' ';
			}
		}
		std::cout << '\n';
	}

	std::cout << "-------\n";
	(*hero.get()).print();

	if (hero.get() != target.get()) 
	{
		std::cout << "-------\n";
		std::cout << "target hp: ";
		(*target.get()).print();
	}

	for (int i = 0; i < enemies.size(); i++) 
	{
		std::cout << "-------\n";
		(*enemies[i].get()).print();
	}
	std::cout << "-------\n";
}

Labyrinth::Labyrinth(const char* file_name) : move_counter(0), affected_tiles_color("\033[48;2;0;0;0m"), affected_tiles_color_reset("\033[0m")
{
	Skeleton::reset_bonus_count();

	std::fstream file(file_name, std::ios::in);

	if (!file.is_open())
	{
		throw GameFileException("file does not exist");
	}

	int size = -1;
	if (file.eof())
	{
		throw GameFileException("file does not contain dimensions of labyrinth");
	}
	else
	{
		file >> size;
		if (file.get() != '\n') 
		{
			throw GameFileLayoutException("labyrinth layout does not fit dimensions", 0, 0);
		}
	}
	Position::set_max(size);

	if (size < 2 || size > 64)
	{
		throw GameFileDimensionsException("dimensions of labyrinth are out of the allowed bounds", size);
	}

	bool has_end = false;
	for (int i = 0; i < size; i++)
	{
		tiles.push_back(std::vector<Tile>());
		for (int j = 0; j < size; j++)
		{
			char current = '\0';
			if (file.eof())
			{
				throw GameFileLayoutException("labyrinth layout does not fit dimensions", i, j);
			}
			else
			{
				file.get(current);
			}
			has_end |= create_from_character(current, i, j, i, has_end);
		}
		if (i != size - 1 && file.get() != '\n')
		{
			throw GameFileLayoutException("labyrinth layout does not fit dimensions", i, size);
		}
	}

	// to read last character so EOF gets recognized
	file.get();

	if (!has_end)
	{
		throw GameFileException("labyrinth does not have target destination");
	}

	if (hero == nullptr) 
	{
		throw GameFileException("labyrinth does not have a hero");
	}

	if (!file.eof()) 
	{
		throw GameFileLayoutException("labyrinth layout does not fit dimensions", size, 0);
	}

	create_prev_and_visited(size);

	create_display_and_colored(size);

	file.close();
}

int Labyrinth::play()
{
	int res = 0;
	do
	{
		res = play_game_state();
		move_counter++;
	} while (res == 0);
	return res;
}
