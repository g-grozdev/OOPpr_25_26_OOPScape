#pragma once
#include "Enemy.h"

class Giant : public Enemy
{
public:
	Giant(int x, int y, const int& m_c);
	~Giant() override = default;

	bool move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction) override;
	Weapon attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int direction) override;
};

