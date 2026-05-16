#pragma once

class Position
{
	int x;
	int y;

public:
	Position(int _x, int _y);
	virtual ~Position() = default;

	const int& get_x() const;
	void set_x(int _x);
	const int& get_y() const;
	void set_y(int _y);
};

