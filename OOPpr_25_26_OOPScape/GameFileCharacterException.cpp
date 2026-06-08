#include "GameFileCharacterException.h"

GameFileCharacterException::GameFileCharacterException(const std::string& msg, const std::string& _type_char, char _invalid_char)
	: GameFileException(msg), type_character(_type_char), invalid_character(_invalid_char) { }

char GameFileCharacterException::get_invalid_character() const
{
	return invalid_character;
}

const std::string& GameFileCharacterException::get_type_character() const
{
	return type_character;
}
