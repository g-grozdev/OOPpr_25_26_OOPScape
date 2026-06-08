#pragma once
#include "Knight.h"
#include "Wizard.h"
#include "Archer.h"
#include "GameFileCharacterException.h"

class HeroFactory
{
public:
	static std::shared_ptr<Hero> create_hero(char hero_type, int x, int y, const int& m_c);
};

