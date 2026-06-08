#pragma once
#include "GameFileException.h"

class GameFileLayoutException : public GameFileException
{
	int rows;
	int cols;

public:
	explicit GameFileLayoutException(const std::string& msg, int _rows, int _cols);

	int get_rows() const;
	int get_cols() const;
};

