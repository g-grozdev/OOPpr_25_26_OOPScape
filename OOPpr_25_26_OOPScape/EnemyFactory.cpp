#include "EnemyFactory.h"

std::unique_ptr<Enemy> EnemyFactory::create_enemy(char enemy_type, int x, int y, const int& m_c)
{
	std::unique_ptr<Enemy> result = nullptr;

	switch (enemy_type) 
	{
	case 'g':
		result = std::make_unique<Giant>(x, y, m_c);
		break;
	case 't':
		result = std::make_unique<Thief>(x, y, m_c);
		break;
	case 's':
		result = std::make_unique<Skeleton>(x, y, m_c);
		break;
	default:
		throw GameFileException("labyrinth has invalid enemy type");
		break;
	}

	return result;
}
