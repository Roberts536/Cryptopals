#include "gtest/gtest.h"
#include "HexToBase64.h"

#include <string>

TEST(TestHexToBase64, HexToBase64_CalledWithTwoChars_ReturnsCorrectResult)
{
	const std::string input{ "a4" };
	const std::string answer{ "pA" };

	EXPECT_EQ(HexToBase64(input), answer);
}

TEST(TestHexToBase64, HexToBase64_CalledWithFourChars_ReturnsCorrectResult)
{
	const std::string input{ "A4B1" };
	const std::string answer{ "pLE" };

	EXPECT_EQ(HexToBase64(input), answer);
}

TEST(TestHexToBase64, HexToBase64_CalledWithSixChars_ReturnsCorrectResult)
{
	const std::string input{ "A34FD1" };
	const std::string answer{ "o0/R" };

	EXPECT_EQ(HexToBase64(input), answer);
}

TEST(TestHexToBase64, HexToBase64_CalledWithChallenge1Input_ReturnsCorrectResult)
{
	const std::string input{ "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" };
	const std::string answer{ "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t" };

	EXPECT_EQ(HexToBase64(input), answer);
}

TEST(TestHexToBase64, HexToBase64_CalledWithOddLengthInputInput_ThrowsException)
{
	const std::string input{ "AB4" };
	
	EXPECT_ANY_THROW(HexToBase64(input));
}
