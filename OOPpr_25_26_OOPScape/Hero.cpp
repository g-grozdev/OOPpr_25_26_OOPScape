#include "Hero.h"

Hero::Hero(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, int ac) : 
	Character(_hp, _mhp, _x, _y, dmg, rng, aoe, _pierce), ability_cooldown(ac), last_used_ability(-1) { }

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
