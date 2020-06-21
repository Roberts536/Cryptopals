#pragma once
#include <string>

/*
A function to convert hex encoding to Base64 encoding.
Does not pad the result with '=' characters.

The input must have even length because Base64 operates on bytes,
and each hex character is only half a byte.

Parameters:
	input:	A hex-encoded input string of even length.

Returns:
	result:	The Base64 encoded version of the data in the input string, 
			without padding.

Throws:
			std::invalid_argument if the input string has odd length.
*/
std::string HexToBase64(const std::string &input);
