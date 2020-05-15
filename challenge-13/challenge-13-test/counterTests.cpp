#include "gtest/gtest.h"
#include "Counter.h"

TEST(Counter, next_calledOnce_returnsZero)
{
	auto counter = Counter();
	EXPECT_EQ(0, counter.next());
}

TEST(Counter, next_calledTwice_returnsIncreasingNumbers)
{
	auto counter = Counter();
	auto val1 = counter.next();
	auto val2 = counter.next();
	EXPECT_EQ(val1 + 1, val2);
}
