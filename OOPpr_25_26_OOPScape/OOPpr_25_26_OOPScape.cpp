// github link: https://github.com/g-grozdev/OOPpr_25_26_OOPScape

#include <iostream>
#include "Labyrinth.h"

int main()
{
	try 
	{
		int selection = -1;
		while (selection != 5) 
		{
			std::cout << "please select an option:\n1 - Knight\n2 - Archer\n3 - Wizard\n4 - custom\n5 - quit\n";
			std::cin >> selection;
			while (std::cin.fail() || selection < 1 || selection > 5)
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "options are only between 1 and 5\n";
				std::cin >> selection;
			}

			int result = 0;
			// blocked scopes are needed to prevent bypass transfer error (variables may not be initialized, yet used later on, in switch case)
			switch (selection)
			{
			case 1:
			{
				Labyrinth lab("knight.txt");
				result = lab.play();
			}
				break;
			case 2:
			{
				Labyrinth lab("archer.txt");
				result = lab.play();
			}
				break;
			case 3:
			{
				Labyrinth lab("wizard.txt");
				result = lab.play();
			}
				break;
			case 4:
			{
				Labyrinth lab("custom.txt");
				result = lab.play();
			}
				break;
			case 5:
				break;
			default:
				throw GameFileException("game option does not exist");
				break;
			}

			if (result == 1)
			{
				std::cout << "you escaped successfully!\n";
			}
			else if (result == -1)
			{
				std::cout << "you have been defeated!\n";
			}
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
