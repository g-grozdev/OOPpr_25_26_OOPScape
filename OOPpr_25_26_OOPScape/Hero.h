#pragma once
#include <iostream>
#include <string>
#include <queue>
#include "Character.h"
#include "Tile.h"

class Hero : public Character
{
protected:
	int ability_cooldown;
	int last_used_ability;
	void tile_effect(const Tile& tile, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero);

public:
	Hero(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, int ac, const int& m_c, char d_c);
	~Hero() override = default;

	Weapon attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero);
	virtual bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero) = 0;
	virtual void get_affected_by_ability_tiles(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar,
		const std::shared_ptr<Hero>& hero, std::queue<Position>& affected_tiles);
	bool move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero) override;
	void print() override;
};

