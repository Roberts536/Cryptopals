#include <algorithm>
#include <iomanip>
#include <sstream>

#include "Buffer.h"

namespace CPals
{

Buffer StringToBuffer(const std::string &input)
{
	return Buffer(input.cbegin(), input.cend());
}

std::string BufferToHex(const Buffer &buf)
{
	std::stringstream stream;
	stream << std::hex;

	for (const auto b : buf)
	{
		stream << std::setw(2) << std::setfill('0') << b;
	}

	return stream.str();
}

Buffer HexToBuffer(const std::string &hexString)
{
	if (!std::all_of(
		std::cbegin(hexString),
		std::cend(hexString),
		::isxdigit)
		|| hexString.size() % 2 != 0)
	{
		throw std::invalid_argument("The input string is not valid hex");
	}

	CPals::Buffer outputBuffer;

	for (std::size_t i = 0; i < hexString.size(); i += 2)
	{
		const auto hexChar = hexString.substr(i, 2);
		auto dataPoint =
			static_cast<std::uint8_t>(std::stoi(hexChar, nullptr, 16));
		outputBuffer.push_back(dataPoint);
	}

	return outputBuffer;
}

}
