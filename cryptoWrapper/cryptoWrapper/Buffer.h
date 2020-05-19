#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace CPals
{
	using Buffer = std::vector<std::uint8_t>;

	/*
	Create a Buffer from a string.

	Parameters:
		input: The string to create a buffer from.

	Returns:
		A buffer containing the contents of the string.
	*/
	Buffer StringToBuffer(const std::string &input);

	/*
	Convert hex-encoded data into a buffer.

	Parameters:
		hexString: The hex data to load into the buffer.

	Returns:
		A buffer containing the data encoded in the given hex string.

	Throws:
		std::invalid_argument: If the argument is not valid hex.
	*/
	Buffer HexToBuffer(const std::string &hexString);

	/*
	Convert a buffer to a hex string.

	Parameters:
		buf: The buffer whose contents should be converted to a string.

	Returns:
		The hex-encoded buffer as a string.
	*/
	std::string BufferToHex(const Buffer &buf);
}
