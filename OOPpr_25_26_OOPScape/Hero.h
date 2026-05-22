#pragma once
#include "Character.h"
#include "Tile.h"

class Hero : public Character
{
protected:
	int ability_cooldown;
	int last_used_ability;
	void tile_effect(const Tile& tile, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero);

public:
	Hero(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, int ac, const int& m_c);
	~Hero() override = default;

	virtual bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int x = -1, int y = -1) = 0;
	bool move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction = -1) override;
};

