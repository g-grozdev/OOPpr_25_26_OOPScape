#include "Wizard.h"

bool Wizard::is_within_teleportation_range(int _x, int _y)
{
	int dx = x - _x;
	int dy = y - _y;
	return dx * dx + dy * dy <= teleportation_range;
}

Wizard::Wizard(int x, int y) : Hero(100, 100, x, y, 20, 4, 2, false, 8), teleportation_range(6) { }

bool Wizard::ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int _x = -1, int _y = -1)
{
	if (!is_within_teleportation_range(_x, _y)) return false;

	int n = tiles.size();
	if (_x < 0 || _x >= n || _y < 0 || _y >= n) return false;

	if (!tiles[_x][_y].get_walkability()) return false;

	if (last_used_ability != -1 && move_counter - last_used_ability <= ability_cooldown) return false;

	set_x(_x);
	set_y(_y);

	tile_effect(tiles[x][y], tar, hero);

	last_used_ability = move_counter;

	return true;
}
