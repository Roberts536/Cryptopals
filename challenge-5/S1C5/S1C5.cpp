#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ios>
#include <fstream>
#include <iomanip>

#include "repeating_key_xor.h"

// Code for Cryptopals Set 1, Challenge 5
// Implement repeating key XOR
// Also contains an optional LINE_WISE mode
// Which encrypts each line separately
int main()
{
	const std::string KEY{ "ICE" };

	// Enable to perform XOR line-by line. In this mode, key is reset 
	// at the beginning of each line and the newline is not encrypted
	const bool LINE_WISE{ false };

	// Set up the input filestream
	std::string in_filename = "input.txt";
	std::ifstream inf(in_filename);
	// If we couldn't open the the filestream for reading
	if (!inf)
	{
		// Print an error and exit
		std::cerr << "Could not open file " << in_filename
			<< " for reading." << std::endl;
		exit(1);
	}

	// Set up the OUTPUT filestream
	std::string out_filename = "output.txt";
	std::ofstream outf(out_filename);
	// If we couldn't open the filestream for writing
	if (!outf)
	{
		// Print an error and exit
		std::cerr << "Could not open file " << out_filename
			<< " for writing." << std::endl;
		exit(1);
	}

	// If we want to perform encryption line-by-line
	if (LINE_WISE)
	{
		// While we can keep extracting lines from the file
		for (std::string line; std::getline(inf, line);)
		{
			// Encrypt the line
			std::string line_xor{ repeating_key_xor(line, KEY) };

			// Write it to the file as hex
			for (int i = 0; i < line_xor.length(); i++)
			{
				int letter_int{ static_cast<int>(line_xor[i]) };
				outf << std::setw(2) << std::setfill('0')
					<< std::hex << letter_int;
			}

			// Start a new line
			outf << std::endl;
		}
	}

	// Else we encrypt a continuous string of characters, including \n
	else
	{
		// While we can keep extracting character from file
		// Read off a number of characters equal to the key length (+1 for \0)
		// Delimiter is 0 (null char) so won't be held up at line feeds
		for (char in_chars[sizeof(KEY) + 1]; inf.get(in_chars, KEY.length() + 1, 0);)
		{
			// Convert the char array to a string
			std::string in_string{ in_chars };

			// Perform the repeating key XOR
			std::string out_string = repeating_key_xor(in_string, KEY);

			// Write to file as hex - no newlines
			for (int i = 0; i < out_string.length(); i++)
			{
				int letter_int{ static_cast<int>(out_string[i]) };
				outf << std::setw(2) << std::setfill('0') << std::hex << letter_int;
			}

		}
	}

	return 0;
}
