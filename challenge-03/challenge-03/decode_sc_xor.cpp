#include "decode_sc_xor.h"
#include "english_score.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <limits>
#include <cassert>

// Part of Set 1, Challenge 3 in Cryptopals
// Function to decode the single-byte XOR cipher

std::string decode_sc_xor(std::string hex_input) {

	float best_plaintext_score = std::numeric_limits<float>::max();
	std::string key;

	// Check every possible byte as a key i
	for (int i = 0; i < 256; i++) {

		// Stream for output
		std::stringstream plaintext_stream;
		int num_unprintable{ 0 };

		// Reverse the XOR cipher using key i
		for (int j = 0; j < hex_input.length(); j += 2) {
			int letter_int = std::stoi(hex_input.substr(j, 2), nullptr, 16);
			int xor_result = letter_int ^ i;

			// If the result is printable, append it to output stream
			if (isprint(xor_result))
			{
				plaintext_stream << static_cast<unsigned char>(xor_result);
			}
			else {
				num_unprintable++;
			}
		}

		// Score the printable portion of the plaintext
		float score = englishDistanceScore(plaintext_stream.str());

		// Introduce a penalty for unprintables
		unsigned int len{ plaintext_stream.str().length() };
		score *= (len + num_unprintable) / (float)len;
		
		// If the score is better than current best
		if (score < best_plaintext_score) {
			// Update best and return plaintext with unprintables substituted
			best_plaintext_score = score;
			key = static_cast<char>(i);
		}
	}

	return key;
}
