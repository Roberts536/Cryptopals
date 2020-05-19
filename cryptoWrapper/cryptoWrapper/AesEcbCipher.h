#pragma once

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::byte;
#include "cryptlib.h"
using CryptoPP::Exception;
#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
#include "aes.h"
using CryptoPP::AES;
#include "modes.h"
using CryptoPP::ECB_Mode;

#include "Buffer.h"
#include "ICipher.h"

namespace CPals
{
class AesEcbCipher : public ICipher
{
public:
	// Default is sufficient
	~AesEcbCipher() = default;

	/*
	Constructor.
		
	Parameters:
		padder:	The padder with which to pad the input.
	*/
	AesEcbCipher(std::unique_ptr<IPadder> padder);

	/*
	Encrypt a buffer using AES in ECB mode.

	Parameters:
		buf:	The buffer to encrypt.
		key:	The key to encrypt with.
	*/
	Buffer Encrypt(
		Buffer buf,
		const Buffer &key);

	/*
	Encrypt a buffer using AES in ECB mode.

	Parameters:
		buf:	The buffer to encrypt.
		key:	The key to encrypt with.
		IV:		Not used.

	Throws:
		std::invalid_argument: If the input buffer is a not a multiple of
			the block size.
	*/
	Buffer Encrypt(Buffer buf, const Buffer &key, const Buffer &IV) override;

	/*
	Encrypt a decrypt using AES in ECB mode.

	Parameters:
		buf:	The buffer to decrypt.
		key:	The key to decrypt with.
	*/
	Buffer Decrypt(
		Buffer buf,
		const Buffer &key);

	/*
	Decrypt a buffer using AES in ECB mode.

	Parameters:
		buf:	The buffer to decrypt.
		key:	The key to decrypt with.
		IV:		Not used.

	Throws:
		std::invalid_argument: If the input buffer is a not a multiple of
			the block size.
		std::runtime_error: If the decryption failed or the padding could not
			be stripped from the decrypted buffer.
	*/
	Buffer Decrypt(Buffer buf, const Buffer &key, const Buffer &IV) override;

private:
	// The padder which will be used to pad the input
	std::unique_ptr<IPadder> m_padder;
};

}