#pragma once
#include "Hero.h"

class Archer : public Hero
{
public:
	Archer(int x, int y, const int& m_c);
	~Archer() override = default;

	bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int x, int y) override;
};

