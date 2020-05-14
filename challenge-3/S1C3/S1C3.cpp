#include "decode_sc_xor.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <limits>

// Main code for Set 1, Challenge 3 in Cryptopals
// Brute-force the single-byte XOR cipher

int main() {

	const std::string HEX_INPUT = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

	std::string plaintext{ decode_sc_xor(HEX_INPUT) };

	std::cout << "The best plaintext is: " << plaintext << std::endl;

	return 0;
}
