#pragma once
#include "Hero.h"

class Archer : public Hero
{
public:
	Archer(int x, int y, const int& m_c);
	~Archer() override = default;

	bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero) override; 
	void get_affected_by_ability_tiles(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar,
		const std::shared_ptr<Hero>& hero, std::queue<Position>& affected_tiles) override;
};

