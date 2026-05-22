#include "Labyrinth.h"

bool Labyrinth::create_from_character(char character, int x, int y, int row)
{
	bool has_end = false;
	if (character >= 'A' && character <= 'Z')
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
		if (character == 'F')
		{
			has_end = true;
		}
		tiles[row].push_back(TileFactory::create_tile(character, x, y));
	}
	return has_end;
}

int Labyrinth::play_game_state()
{
	print();

	int successful_movement = 1;
	do
	{
		if (successful_movement != 1) 
		{
			std::cout << "invalid movement please try again\n";
		}
		int direction = get_player_movement();
		successful_movement = (*hero.get()).move(tiles, target, hero, direction);
	} while (!successful_movement);

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

	for (int i = 0; i < enemies.size(); i++) 
	{
		// apply enemy attack
		(*enemies[i].get()).attack(tiles, target, hero);
	}

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

int Labyrinth::get_player_movement()
{
	std::cout << "Enter a command to move in a direction : U (up) ; R (right) ; D (down) ; L (left)\n";
	std::string command = "";
	std::getline(std::cin, command);
	while (command != "U" && command != "R" && command != "D" && command != "L") 
	{
		std::cout << "Invalid command please try again\n";
		std::getline(std::cin, command);
	}

	int direction = 0;

	if (command == "U") direction = 0;
	else if (command == "R") direction = 1;
	else if (command == "D") direction = 2;
	else if (command == "L") direction = 3;

	return direction;
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
		get_player_attack();
	}
	else if (command == "A") 
	{
		(*hero.get()).ability(tiles, target, hero);
	}
}

void Labyrinth::get_player_attack()
{
	std::cout << "Enter a command to attack in a direction : U (up) ; R (right) ; D (down) ; L (left)\n";
	std::string command = "";
	std::getline(std::cin, command);
	while (command != "U" && command != "R" && command != "D" && command != "L")
	{
		std::cout << "Invalid command please try again\n";
		std::getline(std::cin, command);
	}

	int direction = 0;

	if (command == "U") direction = 0;
	else if (command == "R") direction = 1;
	else if (command == "D") direction = 2;
	else if (command == "L") direction = 3;

	(*hero.get()).attack(tiles, target, hero, direction);
}

int Labyrinth::check_state()
{
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

void Labyrinth::print()
{
	//std::system("CLS");
	std::vector<std::vector<char>> display;
	for (int i = 0; tiles.size(); i++) 
	{
		display.push_back(std::vector<char>());
		for (int j = 0; j < tiles.size(); j++)
		{
			display[i].push_back(tiles[i][j].get_display_char());
		}
	}

	for (int i = 0; i < enemies.size(); i++) 
	{
		int x = (*enemies[i].get()).get_x();
		int y = (*enemies[i].get()).get_y();
		char d_c = (*enemies[i].get()).get_display_char();
		display[x][y] = d_c;
	}

	int x = (*target.get()).get_x();
	int y = (*target.get()).get_y();
	char d_c = (*target.get()).get_display_char();
	display[x][y] = d_c;

	x = (*hero.get()).get_x();
	y = (*hero.get()).get_y();
	d_c = (*hero.get()).get_display_char();
	display[x][y] = d_c;

	for (int i = 0; tiles.size(); i++)
	{
		for (int j = 0; j < tiles.size(); j++)
		{
			std::cout << display[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

Labyrinth::Labyrinth(const char* file_name) : move_counter(0)
{
	std::ifstream file(file_name);

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
				file >> current;
			}
			has_end |= create_from_character(current, i, j, i);
		}
	}

	if (!has_end || hero == nullptr) 
	{
		// throw exception of invalid file;
	}

	file.close();
}

int Labyrinth::play()
{
	int res = 0;
	do
	{
		res = play_game_state();
	} while (res == 0);
	return res;
}
