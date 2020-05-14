#include "gtest/gtest.h"
#include "pad_pkcs7.h"

#include <string>

TEST(TestPadPkcs7, Challenge) {
	const std::string s1{ "YELLOW SUBMARINE" };
	const std::string s2{ "YELLOW SUBMARINE\x04\x04\x04\x04" };
	EXPECT_EQ(pad_pkcs7(20, s1), s2);
}

TEST(TestPadPkcs7, MessageIsMultipleOfBlockSize) {
	const std::string s1{ "YesYesYes" };
	const std::string padding{ "\x03\x03\x03" };
	EXPECT_EQ(pad_pkcs7(3, s1), s1 + padding);
}