#include "Labyrinth.h"

bool Labyrinth::create_from_character(char character, int x, int y, int row)
{
	bool has_end = false;
	if (character == 'F')
	{
		has_end = true;
		tiles[row].push_back(TileFactory::create_tile(character, x, y));
	}
	else if (character >= 'A' && character <= 'Z')
	{
		if (hero != nullptr)
		{
			// throw exception of invalid file;
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

int Labyrinth::play_game_state()
{
	print();

	bool successful_movement = true;
	do
	{
		if (!successful_movement) 
		{
			std::cout << "invalid movement please try again\n";
		}
		successful_movement = (*hero.get()).move(tiles, target, hero);
	} while (!successful_movement);

	print();

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

	// apply player attack
	get_player_action();

	print();

	Sleep(1000);

	for (int i = 0; i < enemies.size(); i++) 
	{
		// apply enemy attack
		apply_attack((*enemies[i].get()).attack(tiles, target, hero), false);
	}

	print();

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

void Labyrinth::get_player_action()
{
	std::cout << "Enter a command for an action : X (attack) ; A (ability)\n";
	std::string command = "";
	std::getline(std::cin, command);
	while (command != "X" && command != "A")
	{
		std::cout << "Invalid command please try again\n";
		std::getline(std::cin, command);
	}

	if (command == "X") 
	{
		apply_attack((*hero.get()).attack(tiles, target, hero), true);
	}
	else if (command == "A") 
	{
		(*hero.get()).ability(tiles, target, hero);
	}
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

void Labyrinth::apply_attack(const Weapon& wp, bool hero_or_enemy)
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
				apply_AOE(Position(attack_x, attack_y), wp, hero_or_enemy);
			}
			break;
		}
		if (hits_an_oponent(Position(attack_x, attack_y), hero_or_enemy))
		{
			apply_AOE(Position(attack_x, attack_y), wp, hero_or_enemy);
			if (!wp.get_pierce())
			{
				break;
			}
			prev = true;
		}
		else 
		{
			prev = false;
		}

		if (i == wp.get_range() && !prev)
		{
			apply_AOE(Position(attack_x, attack_y), wp, hero_or_enemy);
		}

		attack_x += dir[direction][0];
		attack_y += dir[direction][1];
	}

	clear_enemies();
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
		attacked.push(Position(init_x, init_y));
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
					attacked.push(Position(new_x, new_y));
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
			}

			if (!wp.get_pierce()) return;
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
			if (!wp.get_pierce()) return;
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
	std::vector<std::vector<char>> display;
	std::vector<std::vector<bool>> colored;
	for (int i = 0; i < tiles.size(); i++) 
	{
		display.push_back(std::vector<char>());
		colored.push_back(std::vector<bool>());
		for (int j = 0; j < tiles.size(); j++)
		{
			colored[i].push_back(false);
			display[i].push_back(tiles[i][j].get_display_char());
		}
	}

	while (!attacked.empty()) 
	{
		int x = attacked.front().get_x();
		int y = attacked.front().get_y();
		colored[x][y] = true;
		attacked.pop();
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

	print(display, colored);
}

void Labyrinth::print(std::vector<std::vector<char>> display, std::vector<std::vector<bool>> colored)
{
	std::cout << "   ";
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
	}
	std::cout << "\n   ";
	for (int i = 0; i < tiles.size(); i++) std::cout << "__";
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
				std::cout << ' ' << "\033[48;2;235;75;12m" << display[i][j] << "\033[0m";
			}
			else 
			{
				std::cout << ' ' << display[i][j];
			}
		}
		std::cout << '\n';
	}
	(*hero.get()).print();
}

Labyrinth::Labyrinth(const char* file_name) : move_counter(0)
{
	Skeleton::reset_bonus_count();
	
	std::fstream file(file_name, std::ios::in);

	if (!file.is_open()) 
	{
		// throw exception of being unable to open file;
	}
	
	int size = -1;
	if (file.eof()) 
	{
		// throw exception of invalid file;
	}
	else 
	{
		file >> size;
		file.get();
	}
	Position::set_max(size);

	if (size < 2 || size > 64) 
	{
		// throw exception of invalid file;
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
				// throw exception of invalid file;
			}
			else
			{
				file.get(current);
			}
			has_end |= create_from_character(current, i, j, i);
		}
		file.get();
	}

	if (!has_end || hero == nullptr || !file.eof()) 
	{
		// throw exception of invalid file;
	}

	create_prev_and_visited(size);

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
