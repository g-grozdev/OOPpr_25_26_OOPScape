#include "Position.h"

int Position::MAX = 64;

Position::Position() : x(-1), y(-1) { }

Position::Position(int _x, int _y) : x(_x), y(_y) { }

int Position::get_x() const
{
	return x;
}

void Position::set_x(int _x)
{
	if (_x < 0 || _x > Position::MAX) return;
	x = _x;
}

int Position::get_y() const
{
	return y;
}

void Position::set_y(int _y)
{
	if (_y < 0 || _y > Position::MAX) return;
	y = _y;
}

int Position::get_max()
{
	return Position::MAX;
}

void Position::set_max(int max)
{
	if (max < 0 || max > 64) return;
	Position::MAX = max;
}
