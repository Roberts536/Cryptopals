/*
The Cryptopals Challenges
Challenge 1: Convert hex to Base64
*/
#include "HexToBase64.h"

#include <iostream>
#include <string>

int main()
{
	const std::string input{ "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" };
	std::cout << "Cryptopals Challenge 1: Convert hex to Base64\n"
		<< "Input:\t" << input << "\nResult:\t"
		<< HexToBase64(input) << std::endl;

	return 0;
}
