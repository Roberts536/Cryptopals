#include "Buffer.h"
#include "IPadder.h"

namespace CPals
{

class Pkcs7Padder : public IPadder
{
public:
	// Default destructor is sufficient.
	~Pkcs7Padder() = default;

	// Default constructor is sufficient.
	Pkcs7Padder() = default;

	/*
	Pad a buffer to a multiple of the specified block size using the PKCS#7
	padding scheme.

	Parameters:
		blockSize:	The block size to pad to.
		input:		The buffer to pad.

	Throws:
		std::invalid_argument:	If the block size is zero.
	*/
	void Pad(const std::size_t blockSize, Buffer &input) override;

	/*
	Strip the padding from a buffer.

	Parameters:
		input:	The buffer to strip the padding from.
	*/
	void Strip(Buffer &input) override;
};

}
