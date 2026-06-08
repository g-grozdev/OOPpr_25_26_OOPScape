#pragma once
#include "GameFileException.h"

class GameFileCharacterException : public GameFileException
{
	char invalid_character;
	std::string type_character;

public:
	explicit GameFileCharacterException(const std::string& msg, const std::string& _type_char, char _invalid_char);

	char get_invalid_character() const;
	const std::string& get_type_character() const;
};

