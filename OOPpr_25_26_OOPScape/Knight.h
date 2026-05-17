#pragma once
#include "Hero.h"

class Knight : public Hero
{
	int shield_hp;
	const int MAX_SHIELD_HP;

public:
	Knight(int x, int y);
	~Knight() override = default;

	void take_damage(int dmg) override;
	bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int current_move, int x, int y) override;
};

