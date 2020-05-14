#include "gtest/gtest.h"
#include "cryptoUtils/cryptoUtils.h"
#include "RandomUtils/randomUtils.h"

#include <ctime>
#include <random>

TEST(Tests, test2)
{
	//CryptoPP::StringSink sink;
	ASSERT_TRUE(true);
}

TEST(TestGetRandomByte, TestResultsInRange)
{
	std::mt19937 mersenne{
		static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	for (size_t i = 0; i < 10000; i++)
	{
		byte b{ GetRandomByte(mersenne) };
		EXPECT_LE(b, 255);
		EXPECT_GE(b, 0);
	}
}

TEST(TestWriteRandomBytes, TestWriteTakesPlace)
{
	std::mt19937 mersenne{
		static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	constexpr size_t size{ 100 };
	byte bytes[size]{ 0 };
	WriteRandomBytes(bytes, size, mersenne);

	int total{ 0 };
	for (size_t i = 0; i < size; i++)
	{
		total += bytes[i];
	}

	// The chances of all the array entries being zero are vanishingly
	// small, 1 / 256**100
	ASSERT_GT(total, 0);
	ASSERT_LE(total, 256 * 100);
}
