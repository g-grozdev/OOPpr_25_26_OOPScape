#pragma once
#include <iostream>
#include "Damageable.h"
#include "Position.h"

class Target : public Damageable, public Position 
{
protected:
	char display_char;
public:
	Target(int _x, int _y, int _hp, int _mhp, char d_c);
	~Target() override = default;
	char get_display_char() const;
	void set_display_char(char d_c);

	virtual void print();
};

