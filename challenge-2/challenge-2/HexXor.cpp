#include "HexXor.h"

#include <sstream>
#include <iomanip>

std::string HexXor(const std::string &string1, const std::string &string2)
{
	const std::size_t len{ string1.length() };
	if (string2.length() != len)
	{
		throw std::invalid_argument("Input strings must be the same length");
	}

	std::stringstream resultStream;
	resultStream << std::setfill('0') << std::setw(2) << std::hex;

	for (std::size_t i = 0; i < len; i += 2)
	{
		const int int1{ std::stoi(string1.substr(i, 2), nullptr, 16) };
		const int int2{ std::stoi(string2.substr(i, 2), nullptr, 16) };
		resultStream << (int1 ^ int2);
	}

	return resultStream.str();
}