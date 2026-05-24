#include "Hero.h"

void Hero::tile_effect(const Tile& tile, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
{
	switch (tile.get_effect())
	{
	case Effect::HEAL:
		heal(5);
		break;
	case Effect::POISON:
		take_damage(5);
		break;
	case Effect::HIDE:
		tar = nullptr;
		break;
	case Effect::NONE:
		if (tar == nullptr) tar = hero;
		break;
	}
}

Hero::Hero(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, int ac, const int& m_c, char d_c) :
	Character(_hp, _mhp, _x, _y, dmg, rng, aoe, _pierce, m_c, d_c), ability_cooldown(ac), last_used_ability(-1) { }

Weapon Hero::attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
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

	return Character::attack(tiles, tar, hero, direction);
}

bool Hero::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero)
{
	std::cout << "Enter a command to move in a direction : U (up) ; R (right) ; D (down) ; L (left) ; S (stay in the same place)\n";
	std::string command = "";
	std::getline(std::cin, command);
	while (command != "U" && command != "R" && command != "D" && command != "L" && command != "S")
	{
		// check for whether actual input was made (sometimes the wizards ability messes with the buffer and causes a false alarm)
		if (command != "")
		{
			std::cout << "Invalid command please try again\n";
		}
		std::getline(std::cin, command);
	}

	int direction = -1;

	if (command == "U") direction = 0;
	else if (command == "R") direction = 1;
	else if (command == "D") direction = 2;
	else if (command == "L") direction = 3;
	else if (command == "S") direction = 4;

	int n = tiles.size();
	int temp_x = x;
	int temp_y = y;
	switch (direction)
	{
	case 0:
		temp_x -= 1;
		break;
	case 1:
		temp_y += 1;
		break;
	case 2:
		temp_x += 1;
		break;
	case 3:
		temp_y -= 1;
		break;
	case 4:
		// stay in same place
		break;
	default:
		return false;
		break;
	}
	if (temp_x < 0 || temp_x >= n || temp_y < 0 || temp_y >= n || !tiles[temp_x][temp_y].get_walkability()) return false;
	set_x(temp_x);
	set_y(temp_y);
	tile_effect(tiles[temp_x][temp_y], tar, hero);
	return true;
}

void Hero::print() 
{

	std::cout << "hero hp: " << hp << '\n';
	if (last_used_ability != -1 && move_counter - last_used_ability <= ability_cooldown)
	{
		std::cout << "ability on cooldown for " << ability_cooldown - (move_counter - last_used_ability) + 1 << " moves\n";
	}
	else
	{
		std::cout << "ability ready\n";
	}
}