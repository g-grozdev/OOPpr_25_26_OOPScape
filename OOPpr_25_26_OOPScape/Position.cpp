#include "Position.h"

Position::Position(int _x, int _y) : x(_x), y(_y) { }

const int& Position::get_x() const
{
	return x;
}

void Position::set_x(int _x)
{
	x = _x;
}

const int& Position::get_y() const
{
	return y;
}

void Position::set_y(int _y)
{
	y = _y;
}
