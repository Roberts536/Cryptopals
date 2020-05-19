#pragma once

#include <cstdlib>

#include "Buffer.h"

namespace CPals
{

// Interface for a class performing padding.
class IPadder
{
public:
	// Default destructor is sufficient.
	virtual ~IPadder() = default;

	/*
	Pad a buffer to a multiple of the specified block size.

	Parameters:
		blockSize:	The block size to pad to.
		input:		The buffer to pad.
	*/
	virtual void Pad(const std::size_t blockSize, Buffer &input) = 0;

	/*
	Strip the padding from a buffer.

	Parameters:
		input:	The buffer to strip the padding from.
	*/
	virtual void Strip(Buffer &input) = 0;
};

}
