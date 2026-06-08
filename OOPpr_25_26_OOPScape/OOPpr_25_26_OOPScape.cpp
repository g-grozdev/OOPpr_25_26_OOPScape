#include <iostream>
#include "Labyrinth.h"

int main()
{
	try 
	{
		Labyrinth lab("test1.txt");
		if (lab.play() == 1)
		{
			std::cout << "you escaped successfully!";
		}
		else
		{
			std::cout << "you have been defeated!";
		}
	}
	catch (const GameFileDimensionsException& ex) 
	{
		std::cout << ex.what() << '\n';
		std::cout << "dimensions listed in the file: " << ex.get_size() << '\n';
		std::cout << "dimensions must be between " << ex.get_MIN() << " and " << ex.get_MAX() << '\n';
	}
	catch (const GameFileLayoutException& ex) 
	{
		std::cout << ex.what() << '\n';
		std::cout << "an error occured when trying to read cell (" << ex.get_rows() << ',' << ex.get_cols() << ")\n";
	}
	catch (const GameFileCharacterException& ex) 
	{
		std::cout << ex.what() << '\n';
		std::cout << ex.get_type_character() << " cannot be " << ex.get_invalid_character() << '\n';
	}
	catch (const GameFileException& ex) 
	{
		std::cout << ex.what() << '\n';
	}
	catch (...) 
	{
		std::cout << "unknown error occured";
	}
}
