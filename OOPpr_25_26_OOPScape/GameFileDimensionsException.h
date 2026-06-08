#pragma once
#include "GameFileException.h"

class GameFileDimensionsException : public GameFileException
{
	int size;
	const int MIN;
	const int MAX;

public:
	explicit GameFileDimensionsException(const std::string& msg, int _size);

	int get_size() const;
	int get_MIN() const;
	int get_MAX() const;
};

