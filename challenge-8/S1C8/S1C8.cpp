//#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main()
{
	std::cout << "Searching for lines with a repeated 16 byte block...\n";

    // Set up the input filestream
	std::string filename{ "8.txt" };
	std::ifstream inf(filename, std::ifstream::in);
	if (!inf)
	{
		std::cerr << "Could not open file "
			<< filename << " for reading.\n";
	}

	int lineNumber{ 0 };
	while (inf)
	{
		// Pull a line of ciphertext from input file
		std::string line;
		getline(inf, line);

		// Separate line into 16-byte blocks (32 hex characters)
		std::vector<std::string> blocks;
		bool repeatedBlock{ false };
		for (int i = 0; i < line.length(); i+=32)
		{
			blocks.push_back(line.substr(i, 32));
		}

		// Check whether any two blocks are the same
		int i{ 0 };
		while (i < blocks.size() && !repeatedBlock)
		{
			for (int j = 0; j < i; j++)
			{
				if (blocks[i] == blocks[j])
				{
					repeatedBlock = true;
					std::cout << "Line " << lineNumber
						<< " has a repeated block!\n";
					break;
				}
			}
			i++;
		}
		
		lineNumber++;
	}

	return 0;
}