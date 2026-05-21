#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{
	std::shared_ptr<int> bonus_count;
	int last_bonus_applied;

	void apply_bonus();

public:
	Skeleton(int x, int y, const int& m_c);
	~Skeleton() override = default;

	void take_damage(int dmg) override;
	Weapon attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int direction) override;
};

