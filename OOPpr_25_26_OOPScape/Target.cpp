#include "Target.h"

Target::Target(int _x, int _y, int _hp, int _mhp, char d_c) : Damageable(_hp, _mhp), Position(_x, _y), display_char(d_c) { }

char Target::get_display_char() const
{
	return display_char;
}

void Target::set_display_char(char d_c)
{
	display_char = d_c;
}

void Target::print()
{
	std::cout << hp << '\n';
}
