#pragma once
#include "Enemy.h"

class Thief : public Enemy
{

public:
	Thief(int x, int y, const int& m_c);
	~Thief() override = default;

	bool move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero) override;
};

