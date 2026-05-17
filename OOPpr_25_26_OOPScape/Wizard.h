#pragma once
#include "Hero.h"

class Wizard : public Hero
{
	int teleportation_range;

	bool is_within_teleportation_range(int _x, int _y);

public:
	Wizard(int x, int y);
	~Wizard() override = default;

	bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int x = -1, int y = -1) = 0;
};

