/*
The Cryptopals Challenges
Challenge 9: PKCS#7 Padding
*/
#include "cryptoUtils/paddingUtils.h"

#include <iostream>

int main()
{
	std::vector<byte> input {
		'Y', 'E', 'L', 'L', 'O', 'W', ' ',
		'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E' };

	std::cout << "Cryptopals challenge 9: PKCS#7 padding\n"
		<< "Input:\t";
	
	for (byte b : input)
	{
		std::cout << b;
	}

	pad_pkcs7(20, input);

	std::cout << "\nOutput:\t";
	
	for (byte b : input)
	{
		std::cout << b;
	}

	return 0;
}
