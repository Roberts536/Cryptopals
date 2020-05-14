#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include <math.h>
#include <vector>
#include <iomanip>

#include "hamming_distance.h"
#include "base64.h"
#include "decode_sc_xor.h"
#include "english_score.h"
#include "repeating_key_xor.h"

/*
Main function for Set 1, Challenge 6 of Cryptopals.
Challenge is to break the repeating-key XOR cipher.
*/

// Function to replace unprintables in a string with a (printable) substitutes
std::string replace_unprintables(std::string input_string, char sub_char)
{
	// Warn the user if the substitute character is itself unprintable
	if (!isprint(sub_char))
	{
		std::cerr << "Warning: replacing unprintables with other unprintables\n";
	}

	// Make the substitution
	for (int i = 0; i < input_string.length(); i++)
	{
		// Don't replace line feeds, though
		if (!isprint(input_string[i]) && input_string[i] != 10)
			input_string[i] = sub_char;
	}

	return input_string;
}

int main()
{

	// Open the input filestream
	std::string in_filename{ "6.txt" };
	std::ifstream inf(in_filename);
	// If there's a problem opening the ifstream
	if (!inf)
	{
		// Tell the user the problem, and exit
		std::cerr << "Could not open file "
			<< in_filename << " for reading\n";
		return 1;
	}

	// Keep track of the best hamming distance and keysize
	double best_hamming_score{ std::numeric_limits<double>::max() };
	int best_keysize;

	// Loop over different possible key sizes
	for (int keysize = 2; keysize < 41; keysize++)
	{
		// Take the first four keysize worth of bytes
		std::string first_bytes = "";

		// Keep pulling from input file until we have enough
		while (first_bytes.length() < 10 * keysize && inf.good())
		{
			// Pull a line off the input filestream
			std::string line;
			std::getline(inf, line);

			// Decrypt (uses 3rd party stuff) and add to stream
			first_bytes += base64_decode(line);
		}

		// Check there wasn't an error while extracting
		if (!inf)
		{
			std::cerr << "Error reading from file "
				<< in_filename << "\n";
			return 1;
		}

		// Put the stream back to the beginning of the file
		inf.seekg(0, inf.beg);

		// Compute the normalised Hamming distance between pairs of strings
		// Compute the average
		double av_hamming_score{ 0 };
		for (int i = 0; i < 9; i++)
		{
				// Increment the total score by the normalised hamming score
			av_hamming_score += hamming_distance(
				first_bytes.substr(i*keysize, keysize),
				first_bytes.substr((i + 1)*keysize, keysize));
		}
		// Divide the total score by the number of comparisons to get average
		av_hamming_score /= static_cast<double>(9*keysize); 

		// Compare to the current best score; replace if needed
		if (av_hamming_score < best_hamming_score)
		{
			best_hamming_score = av_hamming_score;
			best_keysize = keysize;
		}

	}

	std::cout << "The lowest normalised Hamming distance is: "
		<< best_hamming_score << "\nfrom a keysize of: "
		<< best_keysize << "\n";

	// Prepare a vector of strings to store the ciphertexts
	std::vector<std::string> ciphertexts;
	ciphertexts.resize(best_keysize);

	// Keep track of which letter we're talking about (0-indexed)
	int letter_count{ 0 };

	// While we can keep extracting from the file
	while (inf.good())
	{
		// Extract and decrypt a line
		std::string line;
		std::getline(inf, line);
		line = base64_decode(line);

		// For each character in the resulting string
		for (int i = 0; i < line.length(); i++)
		{
			// Write the character to the correct ciphertext
			ciphertexts[letter_count % best_keysize] += line[i];
			letter_count++;
		}
	}

	// Break single-character XOR on each ciphertext string
	std::cout << "\nBreaking single-character XOR on ciphertexts... ";
	std::string key{ "" };
	for (int i = 0; i < ciphertexts.size(); i++)
	{
		// Represent ciphertext i as hex
		std::stringstream ciph_stream;
		for (int j = 0; j < ciphertexts[i].length(); j++)
		{
			int letter{ static_cast<int>(ciphertexts[i][j]) };
			ciph_stream << std::hex << std::setw(2) 
				<< std::setfill('0') << letter;
		}
		
		// Brute-force the single-character XOR to find the best plaintext
		key += decode_sc_xor(ciph_stream.str());
	}

	// Replace unprintable characters in key with substitute character
	char sub_char{ 126 }; // 126 = ~
	key = replace_unprintables(key, sub_char);

	std::cout << "done. The key is:\n" << key << "\n";

	// Interleave ciphertexts to get one ciphertext string
	std::string full_ciphertext = "";
	for (int i = 0; i < ciphertexts[0].length(); i++)
	{
		for (int text_num = 0; text_num < best_keysize; text_num++)
		{
			// Check we can take a character off
			// (Needed since later plaintexts may be 1 shorter)
			if (i < ciphertexts[text_num].length())
				full_ciphertext += ciphertexts[text_num][i];
			else
				break;
		}
	}

	// Perform repeating-key XOR do reverse the cipher; replace unprintables
	std::string plaintext{ repeating_key_xor(full_ciphertext, key) };
	plaintext = replace_unprintables(plaintext, sub_char);

	std::cout << "\nThe final plaintext is:\n\n" << plaintext << "\n";

	return 0;
}
