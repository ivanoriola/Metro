#include "metro.hpp"

void clear_screen()
{
	print("\x1B[2J\x1B[H");
}

void	print(std::string text)
{
	std::cout << text;
}

std::string	input(std::string text)
{
	print(text);

	std::string input_text;
	getline(std::cin, input_text);
	std::cin.sync();

	return input_text;
}
