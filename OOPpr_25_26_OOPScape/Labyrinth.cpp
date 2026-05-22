#include "Labyrinth.h"

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
