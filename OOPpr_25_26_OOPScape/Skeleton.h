#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{
	static std::shared_ptr<int> communal_bonus_count;

	std::shared_ptr<int> bonus_count;
	int last_bonus_applied;

	void apply_bonus();
	int get_damage();

public:
	static void reset_bonus_count();

	Skeleton(int x, int y, const int& m_c);
	~Skeleton() override = default;

	void take_damage(int dmg) override;
	Weapon attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero) override;

	const std::shared_ptr<int>& get_bonus_count() const;
	void set_bonus_count(const std::shared_ptr<int>& _bonus_count);
	void print() override;
};

