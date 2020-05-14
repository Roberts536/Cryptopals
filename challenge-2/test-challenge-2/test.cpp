#include "gtest/gtest.h"
#include "HexXor.h"

TEST(TestHexXor, Challenge) {
	const std::string s1{ "1c0111001f010100061a024b53535009181c" };
	const std::string s2{ "686974207468652062756c6c277320657965" };
	const std::string s3{ "746865206b696420646f6e277420706c6179" };
	EXPECT_EQ(HexXor(s1, s2), s3);
}

TEST(TestHexXor, OddLengthHex) {
	const std::string s1{ "abc" };
	const std::string s2{ "def" };
	const std::string s3{ "753" };
	EXPECT_EQ(HexXor(s1, s2), s3);
}

TEST(TestHexXor, EvenLengthHex) {
	const std::string s1{ "abc1" };
	const std::string s2{ "def2" };
	const std::string s3{ "7533" };
	EXPECT_EQ(HexXor(s1, s2), s3);
}

TEST(TestHexXor, EmptyStringInput) {
	const std::string s1{ "" };
	const std::string s2{ "" };
	const std::string s3{ "" };
}

TEST(TestHexXor, DifferentStringLengths)
{
	const std::string s1{ "ABC" };
	const std::string s2{ "ABCD" };
	EXPECT_ANY_THROW(HexXor(s1, s2));
}
