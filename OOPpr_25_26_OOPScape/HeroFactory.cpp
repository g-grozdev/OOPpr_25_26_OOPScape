#include "HeroFactory.h"

std::shared_ptr<Hero> HeroFactory::create_hero(char hero_type, int x, int y, const int& m_c)
{
	std::shared_ptr<Hero> result = nullptr;
	
	switch (hero_type) 
	{
	case 'K':
		result = std::make_shared<Knight>(x, y, m_c);
		break;
	case 'A':
		result = std::make_shared<Archer>(x, y, m_c);
		break;
	case 'W':
		result = std::make_shared<Wizard>(x, y, m_c);
		break;
	default:
		throw GameFileCharacterException("labyrinth has invalid hero type", "hero", hero_type);
		break;
	}

	return result;
}
