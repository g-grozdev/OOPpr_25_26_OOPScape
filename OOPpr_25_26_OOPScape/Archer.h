#pragma once
#include "Hero.h"

class Archer : public Hero
{
public:
	Archer(int x, int y);
	~Archer() override = default;

	bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int current_move, int x, int y) override;
};

