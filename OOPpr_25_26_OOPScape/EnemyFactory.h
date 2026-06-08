#pragma once
#include "Giant.h"
#include "Thief.h"
#include "Skeleton.h"
#include "GameFilecharacterException.h"

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy> create_enemy(char enemy_type, int x, int y, const int& m_c);
};

