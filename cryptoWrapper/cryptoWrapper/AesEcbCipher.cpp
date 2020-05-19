#include <exception>
#include <memory>
#include <iterator>
#include <string>
#include <utility>

#include "AesEcbCipher.h"
#include "Buffer.h"
#include "IPadder.h"

namespace
{
	constexpr unsigned int AesBlockSize = 16;
	constexpr unsigned int AesKeySize = 16;
}

namespace CPals
{

AesEcbCipher::AesEcbCipher(std::unique_ptr<IPadder> padder)
	: m_padder(std::move(padder))
{ }

Buffer AesEcbCipher::Encrypt(Buffer buf, const Buffer &key)
{
	if (buf.size() % AesBlockSize != 0)
	{
		throw std::invalid_argument(
			"Input buffer must be a multiple of the block size (" 
			+ std::to_string(AesBlockSize) + ")");
	}

	if (key.size() != AesKeySize)
	{
		throw std::invalid_argument(
			"The key size must be " + std::to_string(AesKeySize));
	}

	m_padder->Pad(AesBlockSize, buf);

	ECB_Mode<AES>::Encryption encryption(key.data(), AES::DEFAULT_KEYLENGTH);

	Buffer plaintextBlock(AES::BLOCKSIZE);
	Buffer ciphertextBlock(AES::BLOCKSIZE);
	Buffer ciphertext;

	auto pos = std::begin(buf);
	while (pos < std::end(buf))
	{
		std::copy_n(pos, AES::BLOCKSIZE, std::begin(plaintextBlock));
		pos += AES::BLOCKSIZE;

		encryption.ProcessData(
			ciphertextBlock.data(),
			plaintextBlock.data(),
			AES::BLOCKSIZE);

		ciphertext.insert(
			std::cend(ciphertext),
			std::cbegin(ciphertextBlock),
			std::cend(ciphertextBlock));
	}

	return ciphertext;
}

Buffer AesEcbCipher::Encrypt(
	Buffer buf,
	const Buffer &key,
	const Buffer &IV)
{
	return Encrypt(buf, key);
}

Buffer AesEcbCipher::Decrypt(Buffer buf, const Buffer &key)
{
	if (buf.size() % AesBlockSize != 0 || buf.size() == 0)
	{
		throw std::invalid_argument(
			"Input buffer must be a multiple of the block size ("
			+ std::to_string(AesBlockSize) + ") and not empty");
	}

	if (key.size() != AesKeySize)
	{
		throw std::invalid_argument(
			"The key size must be " + std::to_string(AesKeySize));
	}

	ECB_Mode<AES>::Decryption decryption(key.data(), AES::DEFAULT_KEYLENGTH);
	Buffer ciphertextBlock(AES::BLOCKSIZE);
	Buffer plaintextBlock(AES::BLOCKSIZE);
	Buffer plaintext;

	auto pos = std::begin(buf);
	while (pos < std::end(buf))
	{
		std::copy_n(pos, AES::BLOCKSIZE, std::begin(ciphertextBlock));
		pos += AES::BLOCKSIZE;

		try
		{
			decryption.ProcessData(
				plaintextBlock.data(),
				ciphertextBlock.data(),
				AES::BLOCKSIZE);
		}
		catch (const CryptoPP::Exception& e)
		{
			std::throw_with_nested(std::runtime_error("Decryption failed"));
		}

		plaintext.insert(
			std::cend(plaintext),
			std::cbegin(plaintextBlock),
			std::cend(plaintextBlock));
	}

	try
	{
		m_padder->Strip(plaintext);
	}
	catch (const std::invalid_argument &e)
	{
		std::throw_with_nested(std::runtime_error(
			"Could not strip padding from decrypted buffer"));
	}

	return plaintext;
}

Buffer AesEcbCipher::Decrypt(
	Buffer buf,
	const Buffer &key,
	const Buffer &iv)
{
	return Decrypt(buf, key);
}

}
