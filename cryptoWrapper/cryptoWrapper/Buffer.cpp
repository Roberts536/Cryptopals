#include "Buffer.h"

namespace CPals
{

Buffer StringToBuffer(const std::string &input)
{
	return Buffer(input.cbegin(), input.cend());
}

}
