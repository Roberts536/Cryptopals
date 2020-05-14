#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <vector>
#include <algorithm>

/* 
Code for Set 1, Challenge 4 of Cryptopals.
Challenge: detect which string has had 
repeating-key XOR applied to it, and decrypt it.
*/

// Imports
std::vector<unsigned char> hex_to_vuchar(
	const std::string hex_input);
float english_score(std::string text);
float chisq_stat(
	const std::vector<float> observed,
	const std::vector<float> expected);
std::vector<std::string> decrypt_sb_xor(
	const std::vector<unsigned char> vuchar);

int main()
{
	const std::vector<float> ENGLISH_FREQS{
			8.34, 1.54, 2.73, 4.14, 12.60,
			2.03, 1.92, 6.11, 6.71, 0.23,
			0.87, 4.24, 2.53, 6.80, 7.70,
			1.66, 0.09, 5.68, 6.11, 9.37,
			2.85, 1.06, 2.34, 0.20, 2.04, 0.06 };

	// Read in the list of strings we are given
	std::string filename{ "list.txt" };
	std::ifstream inf(filename);

	// If we couldn't open the output file stream for reading
	if (!inf)
	{
		// Print an error and exit
		std::cerr << "Could not open file " << filename << " for reading";
		std::cerr << std::endl;
		exit(1);
	}

	// Keep track of the best plaintext and score
	float best_score = std::numeric_limits<float>::max();
	std::string best_text;

	// While there are still lines left to read
	while (!inf.eof())
	{
		// Read off a string
		std::string hex_input;
		inf >> hex_input;

		/*
		STAGE 1
		We find out whether the ASCII text is likely
		to be shifted English. Do this by looking at
		the frequencies of the most common 26 ASCII
		characters in the sample and performing a
		Chi-squared test against character frequencies
		for typical English text.

		Only if it passes this test do we bother to try
		to reverse the single-byte XOR.
		*/

		// Convert to a vector of ASCII unsigned chars
		std::vector<unsigned char> vuchar;
		vuchar = hex_to_vuchar(hex_input);

		// Find the frequencies for all 255 ASCII chars
		std::vector<float> char_freqs{};
		char_freqs.resize(256);
		for (int i = 0; i < vuchar.size(); i++)
		{
			char_freqs[vuchar[i]] ++;
		}

		// Sort the list and take the most frequent 26
		std::sort(char_freqs.begin(), char_freqs.end());	// ascending
		std::vector<float> top_freqs;
		top_freqs.resize(26);
		for (int i = 0; i < 26; i++)
		{
			top_freqs[25 - i] = (float)char_freqs[255 - i];
		}

		// Find ascending list of expected frequencies
		std::vector<float> expected_freqs;
		expected_freqs.resize(26);
		for (int i = 0; i < 26; i++) {
			expected_freqs[i] = ENGLISH_FREQS[i] / 100;
			expected_freqs[i] *= vuchar.size();
		}
		std::sort(expected_freqs.begin(), expected_freqs.end());

		// Calculate Chi-Squared statistic
		float chi_squared = chisq_stat(
			top_freqs, expected_freqs);

		// Significance test at 2.5% level, 25df
		if (chi_squared < 13.12) // Use 13.12
		{
			/*
			STAGE 2
			Text might be shifted English, so we
			brute force the single-byte XOR cipher.
			*/

			// Decrypt the single-byte XOR
			std::vector<std::string> printable_texts;
			printable_texts = decrypt_sb_xor(vuchar);

			// For each of the printable texts returned
			for (int i = 0; i < printable_texts.size(); i++)
			{
				// Grab the text
				std::string text = printable_texts[i];

				// See if it's better than the current best
				float score = english_score(text);
				if (score < best_score)
				{
					best_score = score;
					best_text = text;
				}
			}
		}
	}

	std::cout << "The best plaintext was: "
		<< best_text << std::endl;

	return 0;
}
