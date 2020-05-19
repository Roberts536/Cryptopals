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

}
