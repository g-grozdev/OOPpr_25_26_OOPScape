#pragma once
#include "Damageable.h"
#include "Position.h"

class Target : public Damageable, public Position 
{
public:
	Target(int _x, int _y, int _hp, int _mhp);
	~Target() override = default;
};

