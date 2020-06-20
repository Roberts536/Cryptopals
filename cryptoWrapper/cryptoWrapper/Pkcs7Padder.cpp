#include "Buffer.h"
#include "Pkcs7Padder.h"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <stdexcept>

namespace CPals
{

void Pkcs7Padder::Pad(const std::size_t blockSize, Buffer &input)
{
	if (blockSize == 0)
	{
		throw std::invalid_argument("Block size must be greater than 0");
	}

	const std::size_t padSize = blockSize - (input.size() % blockSize);
	std::fill_n(std::back_inserter(input), padSize, padSize);
}

void Pkcs7Padder::Strip(Buffer &input)
{
	if (input.size() == 0)
	{
		throw std::invalid_argument("Input buffer cannot be empty");
	}

	const auto padSize = input.back();

	if (input.size() < padSize 
		|| std::any_of(input.cend() - padSize, input.cend(),
					   [padSize](auto i) {return i != padSize;}))
	{
		throw std::invalid_argument("Input buffer has invalid padding");
	}

	input.erase(input.cend() - padSize, input.cend());
}

}
