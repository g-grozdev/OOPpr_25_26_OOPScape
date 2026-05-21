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
		tar = hero;
		break;
	}
}

Hero::Hero(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, int ac, const int& m_c) :
	Character(_hp, _mhp, _x, _y, dmg, rng, aoe, _pierce, m_c), ability_cooldown(ac), last_used_ability(-1) { }

bool Hero::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction = -1)
{
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
	default:
		break;
	}
	if (temp_x < 0 || temp_x >= n || temp_y < 0 || temp_y >= n || !tiles[temp_x][temp_y].get_walkability()) return false;
	set_x(temp_x);
	set_y(temp_y);
	tile_effect(tiles[temp_x][temp_y], tar, hero);
	return true;
}
