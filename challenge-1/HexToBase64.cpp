#include <string>

constexpr char BASE64_LOOKUP[64] {
		'A', 'B', 'C', 'D', 'E',
		'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O',
		'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y',
		'Z', 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's',
		't', 'u', 'v', 'w', 'x',
		'y', 'z', '0', '1', '2',
		'3', '4', '5', '6', '7',
		'8', '9', '+', '/' };

std::string HexToBase64(const std::string &input)
/*
A function to convert hex encoding to Base64 encoding.
Does not pad the result with '=' characters.

The input must have even length because Base64 operates on bytes,
and each hex character is only half a byte.

Parameters:
	input:	(std::strin) a hex-encoded input string of even length.

Returns:
	result:	(std::string) the Base64 encoded version of the data in
			the input string, without padding.

Throws:
			(std::invalid_argument) if the input string has odd length.
*/
{
	if (input.length() % 2 != 0)
	{
		throw std::invalid_argument("Input string must have even length.");
	}

	std::string result{ "" };
	
	// We work on 24 bit blocks, i.e. 6 hex chars, 4 base64 chars
	constexpr int BLOCK_SIZE{ 6 };
	constexpr int BITS_PER_B64_CHAR{ 6 };
	const int num_blocks{ (int) ceilf(input.size() / (float)BLOCK_SIZE) };

	for (int i = 0; i < num_blocks; i++)
	{
		const std::string block{input.substr(i*BLOCK_SIZE, BLOCK_SIZE)};
		std::int_fast32_t block_bits = std::stol(block, nullptr, 16);

		// If contents doesn't fill a multiple of 6 bits, left-shift
		block_bits <<= (2 * (block.size() % 3));

		const int num_chars = (int) ceilf(4 * block.size() / (float)BLOCK_SIZE);
		for (int j = 0; j < num_chars; j++)
		{
			constexpr std::int_fast32_t bitmask{ 0x3F };	// 0x3F = 0b111111
			const std::int_fast32_t index{
				block_bits >> (num_chars - j - 1) * BITS_PER_B64_CHAR
				& bitmask };
			result += BASE64_LOOKUP[index];
		}
	}

	return result;
}
