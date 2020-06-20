#include "gtest/gtest.h"
#include "Pkcs7Padder.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace CPals
{

TEST(Pkcs7Padder, Pad_CalledWithBlockSizeOfZero_ThrowsInvalidArgumentException)
{
	Pkcs7Padder padder;
	ASSERT_THROW(padder.Pad(0, Buffer(1)), std::invalid_argument);
}

TEST(Pkcs7Padder, Pad_CalledWithInputNotMultipleOfBlockSize_ReturnsCorrectResult)
{
	const std::string message = "Hello world";
	Buffer input(std::cbegin(message), std::cend(message));

	auto comparison(input);
	std::fill_n(std::back_inserter(comparison), 5, 5);

	Pkcs7Padder padder;
	padder.Pad(16, input);

	ASSERT_EQ(comparison, input);
}

TEST(Pkcs7Padder, Pad_CalledWithInputMultipleOfBlockSize_ReturnsCorrectResult)
{
	const std::string message = "Hello world, hi!";
	Buffer input(std::cbegin(message), std::cend(message));

	auto comparison(input);
	std::fill_n(std::back_inserter(comparison), 16, 16);

	Pkcs7Padder padder;
	padder.Pad(16, input);

	ASSERT_EQ(comparison, input);
}

TEST(Pkcs7Padder, Strip_CalledWithEmptyArgument_ThrowsInvalidArgumentException)
{
	Pkcs7Padder padder;
	EXPECT_THROW(padder.Strip(Buffer(0)), std::invalid_argument);
}

TEST(Pkcs7Padder, Strip_CalledWithBufferTooSmall_ThrowsInvalidArgumentException)
{
	Pkcs7Padder padder;
	Buffer input{ 1, 4 };
	EXPECT_THROW(padder.Strip(input), std::invalid_argument);
}

TEST(Pkcs7Padder, Strip_CalledWithInvalidPadding_ThrowsInvalidArgumentException)
{
	Pkcs7Padder padder;
	Buffer input{ 0, 0, 0, 0, 1, 4 };
	EXPECT_THROW(padder.Strip(input), std::invalid_argument);
}

TEST(Pkcs7Padder, Strip_CalledWithValidArguments_ReturnsCorrectResult)
{
	Pkcs7Padder padder;
	Buffer input{ 1, 2, 3, 4, 2, 2 };
	Buffer expected{ 1, 2, 3, 4 };

	padder.Strip(input);

	EXPECT_EQ(expected, input);
}

}
