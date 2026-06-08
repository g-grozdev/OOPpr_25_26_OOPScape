#pragma once
#include "Hero.h"

class Knight : public Hero
{
	int shield_hp;
	const int MAX_SHIELD_HP;

public:
	Knight(int x, int y, const int& m_c);
	~Knight() override = default;

	void take_damage(int dmg) override; 
	void get_affected_by_ability_tiles(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar,
		const std::shared_ptr<Hero>& hero, std::queue<Position>& affected_tiles) override;
	bool ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero) override;
	void print() override;
};

