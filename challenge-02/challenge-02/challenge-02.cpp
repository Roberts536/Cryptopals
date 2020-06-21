/*
The Cryptopals Challenges
Challenge 2: Fixed XOR
*/
#include "HexXor.h"

#include <iostream>

int main()
{
	const std::string s1{ "1c0111001f010100061a024b53535009181c" };
	const std::string s2{ "686974207468652062756c6c277320657965" };
	
	std::cout << "Cryptopals challenge 2: Fixed XOR\n"
		<< "String 1:\t" << s1 << "\n"
		<< "String 2:\t" << s2 << "\n"
		<< "Output:\t\t" << HexXor(s1, s2) << "\n";
}
