#include "Wizard.h"

bool Wizard::is_within_teleportation_range(int _x, int _y)
{
	int dx = x - _x;
	int dy = y - _y;
	return dx * dx + dy * dy <= teleportation_range * teleportation_range;
}

Wizard::Wizard(int x, int y, const int& m_c) : Hero(100, 100, x, y, 20, 4, 2, false, 8, m_c, 'W'), teleportation_range(6) {}

bool Wizard::ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
{
	if (last_used_ability != -1 && move_counter - last_used_ability <= ability_cooldown) return false;

	int n = tiles.size();
	int _x = -1, _y = -1;
	std::cout << "enter x and y coordinate for where you want to teleport (must be within " << teleportation_range << " tile radius)\n";
	std::cin >> _x >> _y;
	while (std::cin.fail() || !is_within_teleportation_range(_x, _y) || (_x < 0 || _x >= n || _y < 0 || _y >= n) || 
		!tiles[_x][_y].get_walkability())
	{
		std::cout << "invalid input please try again\n";
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> _x >> _y;
	}

	set_x(_x);
	set_y(_y);

	tile_effect(tiles[x][y], tar, hero);

	last_used_ability = move_counter;

	return true;
}
