#pragma once
#include "Character.h"

class Hero : public Character
{
	int ability_cooldown;
	int last_used_ability;

public:
	Hero(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, int ac);
	~Hero() override = default;

	void tile_effect(const Tile& tile, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero);
	virtual void ability(const std::vector<std::vector<Tile>>& tiles, Target& tar) = 0;
};

