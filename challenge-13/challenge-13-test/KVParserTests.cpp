#include "KVParser.h"
#include "gtest/gtest.h"

#include <exception>
#include <string>
#include <map>
#include <vector>

TEST(KVParser, parse_calledOnEmptyString_throwsInvalidArgument) {
	EXPECT_THROW(Parsing::parse(std::string()), std::invalid_argument);
}

TEST(KVParser, parse_calledOnStringWithoutEqualsCharacter_throwsInvalidArgument)
{
	const std::string input{ "test string" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(KVParser, parse_calledOnStringWithEmptyKeyWithEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&=qux" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(KVParser, parse_calledOnStringWithEmptyKeyWithoutEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(KVParser, parse_calledOnStringWithEmptyValueWithoutEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&baz" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(KVParser, parse_calledOnStringWithEmptyValueWithEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&baz=" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(KVParser, parse_calledOnStringWithSingleKeyValuePair_returnsCorrectMap)
{
	const std::string input{ "foo=bar" };
	std::map<std::string, std::string> result = Parsing::parse(input);
	EXPECT_EQ("bar", result.at("foo"));
}

TEST(KVParser, parse_calledOnStringWithMultipleKeyValuePairs_returnsCorrectMap)
{
	const std::string input{ "foo=bar&baz=qux&zap=zazzle" };
	std::map < std::string, std::string> result = Parsing::parse(input);
	EXPECT_EQ("bar", result.at("foo"));
	EXPECT_EQ("qux", result.at("baz"));
	EXPECT_EQ("zazzle", result.at("zap"));
}

// Test: empty key and value contents, e.g. =&=&=
