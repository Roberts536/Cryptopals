#include <algorithm>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "AesEcbCipher.h"
#include "Buffer.h"
#include "gtest/gtest.h"
#include "IPadder.h"
#include "Pkcs7Padder.h"

namespace
{
constexpr unsigned int AesBlockSize = 16;
constexpr unsigned int AesKeySize = 16;

/*
Convert a hex string to a buffer.

Parameters:
	hexString:	A hex string.

Returns:
	outputBuffer:	A buffer of the bytes represented by hexString.

Throws:
	std::invalid_argument: If hexString is not valid hex.
*/
CPals::Buffer HexToBuffer(const std::string &hexString)
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

namespace CPals
{

TEST(AesEcbEncrypt, Encrypt_CalledWithWrongSizeKey_ThrowsInvalidArgumentException)
{
	auto padderPtr = std::make_unique<Pkcs7Padder>();
	AesEcbCipher cipher(std::move(padderPtr));
	auto input = Buffer(AesBlockSize);
	auto key = Buffer(AesKeySize + 1);

	EXPECT_THROW(cipher.Encrypt(input, key), std::invalid_argument);
}

TEST(AesEcbEncrypt, Encrypt_CalledWithValidArgumentsMultipleOfBlockSize_ReturnsCorrectResult)
{
	// Test vectors from NIST Algorithmic Validation programme:
	// https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program
	// Expected output adjusted to take into account padding

	auto padderPtr = std::make_unique<Pkcs7Padder>();
	AesEcbCipher cipher(std::move(padderPtr));
	auto input = HexToBuffer("6bc1bee22e409f96e93d7e117393172a");
	auto key = HexToBuffer("2b7e151628aed2a6abf7158809cf4f3c");
	auto expected = HexToBuffer(
		"3ad77bb40d7a3660a89ecaf32466ef97a254be88e037ddd9d79fb6411c3f9df8");

	EXPECT_EQ(expected, cipher.Encrypt(input, key));
}

TEST(AesEcbEncrypt, Encrypt_CalledWithValidArgumentsNotMultipleOfBlockSize_ReturnsCorrectResult)
{
	// Test vectors from NIST Algorithmic Validation programme:
	// https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program
	// Expected output adjusted to take into account padding

	auto padderPtr = std::make_unique<Pkcs7Padder>();
	AesEcbCipher cipher(std::move(padderPtr));
	auto input = HexToBuffer("6bc1bee22e409f96e93d7e11739317");
	auto key = HexToBuffer("2b7e151628aed2a6abf7158809cf4f3c");
	auto expected = HexToBuffer("21ea2ba3e445a0ef710a7c26618d1975");

	EXPECT_EQ(expected, cipher.Encrypt(input, key));
}

TEST(AesEcbDecrypt, Decrypt_CalledWithBufferNotMultipleOfBlockSize_ThrowsInvalidArgumentException)
{
	auto padderPtr = std::make_unique<Pkcs7Padder>();
	AesEcbCipher cipher(std::move(padderPtr));
	Buffer input(AesBlockSize + 1);
	Buffer key(AesKeySize);
	
	EXPECT_THROW(cipher.Decrypt(input, key), std::invalid_argument);
}

TEST(AesEcbDecrypt, Decrypt_CalledWithEmptyBuffer_ThrowsInvalidArgumentException)
{
	auto padderPtr = std::make_unique<Pkcs7Padder>();
	AesEcbCipher cipher(std::move(padderPtr));
	Buffer input(0);
	Buffer key(AesKeySize);

	EXPECT_THROW(cipher.Decrypt(input, key), std::invalid_argument);
}

TEST(AesEcbDecrypt, Decrypt_CalledWithKeyNotMultipleOfBlockSize_ThrowsInvalidArgumentException)
{
	auto padderPtr = std::make_unique<Pkcs7Padder>();
	AesEcbCipher cipher(std::move(padderPtr));
	Buffer input(AesBlockSize);
	Buffer key(AesKeySize + 1);

	EXPECT_THROW(cipher.Decrypt(input, key), std::invalid_argument);
}

TEST(AesEcbDecrypt, Decrypt_CalledWithValidArguments, ReturnsCorrectResult)
{
	auto padderPtr = std::make_unique<Pkcs7Padder>();
	AesEcbCipher cipher(std::move(padderPtr));
	auto input = HexToBuffer(
		"3ad77bb40d7a3660a89ecaf32466ef97a254be88e037ddd9d79fb6411c3f9df8");
	auto key = HexToBuffer("2b7e151628aed2a6abf7158809cf4f3c");
	auto expected = HexToBuffer("6bc1bee22e409f96e93d7e117393172a");

	EXPECT_EQ(expected, cipher.Decrypt(input, key));
}

}
