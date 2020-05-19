#pragma once

#include <cstdint>
#include <vector>

#include "Buffer.h"
#include "IPadder.h"

namespace CPals
{
	/*
	Interface for a class performing encryption.
	*/
	class ICipher
	{
	public:
		/*
		Destructor - default is OK.
		*/
		virtual ~ICipher() = default;

		/*
		Encrypt data.

		Parameters:
			buf:	The buffer to encrypt.
			key:	The key to encrypt with.
			IV:		The initialisation vector to encrypt with.

		Throws:
			std::invalid_argument: If the input buffer is a not a multiple of
				the block size.
		*/
		virtual Buffer Encrypt(
			Buffer buf,
			const Buffer &key,
			const Buffer &IV) = 0;

		/*
		Decrypt data.

		Parameters:
			buf:	The buffer to decrypt.
			key:	The key to decrypt with.
			IV:		The initialisation vector to decrypt with.

		Throws:
			std::invalid_argument: If the input buffer is a not a multiple of
				the block size.
			std::runtime_error: If the decryption failed or the padding could 
				not be stripped from the decrypted buffer.
		*/
		virtual Buffer Decrypt(
			Buffer buf,
			const Buffer &key,
			const Buffer &iv) = 0;
	};
}
