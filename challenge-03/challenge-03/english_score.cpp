// Code for Set 1, Challenge 1 in Cryptopals
// Single-byte XOR cipher
#include "english_score.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>

float english_score(std::string plaintext_input) {

	// Strip to alphabet characters only; make lowercase
	std::stringstream stripped_input_stream;
	for (int i=0; i<plaintext_input.length(); i++) {
		unsigned char letter = plaintext_input[i];
		if (isalpha(letter)) {
			unsigned char lower_char = tolower(letter);
			stripped_input_stream << lower_char;
		}
	}
	std::string stripped_input = stripped_input_stream.str();

	// Calculate frequencies of each character
	int char_freqs[26] = { 0 };
	for (int i=0; i<stripped_input.length(); i++) {
		unsigned char letter = stripped_input[i];
		char_freqs[letter-97]++;	// a=97 in ASCII
	}

	// Calculate the expected letter frequencies
	float english_freqs[26] = { 
		8.34, 1.54, 2.73, 4.14, 12.60,
		2.03, 1.92, 6.11, 6.71, 0.23,
		0.87, 4.24, 2.53, 6.80, 7.70,
		1.66, 0.09, 5.68, 6.11, 9.37,
		2.85, 1.06, 2.34, 0.20, 2.04, 0.06 };
	float expected_freqs[26];
	for (int i=0; i<26; i++) {
		expected_freqs[i] = english_freqs[i] / 100;
		expected_freqs[i] *= stripped_input.length();
	}

	// Calculate Chi-Squared statistic
	float chi_squared = 0;
	for (int j=0; j<26; j++) {
		float to_add = char_freqs[j] - expected_freqs[j];
		to_add = pow(to_add, 2);
		to_add /= expected_freqs[j];
		chi_squared += to_add;
	}

	return chi_squared;

}

