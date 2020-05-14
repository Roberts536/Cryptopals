#include <iostream>
#include <string>

#include "repeating_key_xor.h"

/*
Implement a repeating key XOR on the input text
Input text should be ASCII
The key starts at position 'start'.
*/
std::string repeating_key_xor(const std::string text, const std::string key)
{
	// Make a stringstream to store the output
	std::string output_string;

	// Loop through the characters in the text
	for (std::string::size_type i = 0; i < text.length(); i++)
	{
		// Perform the XOR with the right part of the key
		char xor_result = text[i] ^ key[i % key.length()];

		// Append the result to the output stream
		output_string += xor_result;
	}

	return output_string;
}