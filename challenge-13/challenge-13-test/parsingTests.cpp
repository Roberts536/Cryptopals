#include "Parsing.h"
#include "gtest/gtest.h"

#include <exception>
#include <string>
#include <map>
#include <vector>

TEST(Parsing, parse_calledOnEmptyString_throwsInvalidArgument) {
	EXPECT_THROW(Parsing::parse(std::string()), std::invalid_argument);
}

TEST(Parsing, parse_calledOnStringWithoutEqualsCharacter_throwsInvalidArgument)
{
	const std::string input{ "test string" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(Parsing, parse_calledOnStringWithEmptyKeyWithEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&=qux" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(Parsing, parse_calledOnStringWithEmptyKeyWithoutEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(Parsing, parse_calledOnStringWithEmptyValueWithoutEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&baz" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(Parsing, parse_calledOnStringWithEmptyValueWithEquals_throwsInvalidArgument)
{
	const std::string input{ "foo=bar&baz=" };
	EXPECT_THROW(Parsing::parse(input), std::invalid_argument);
}

TEST(Parsing, parse_calledOnStringWithSingleKeyValuePair_returnsCorrectMap)
{
	const std::string input{ "foo=bar" };
	std::map<std::string, std::string> result = Parsing::parse(input);
	EXPECT_EQ("bar", result.at("foo"));
}

TEST(Parsing, parse_calledOnStringWithMultipleKeyValuePairs_returnsCorrectMap)
{
	const std::string input{ "foo=bar&baz=qux&zap=zazzle" };
	std::map < std::string, std::string> result = Parsing::parse(input);
	EXPECT_EQ("bar", result.at("foo"));
	EXPECT_EQ("qux", result.at("baz"));
	EXPECT_EQ("zazzle", result.at("zap"));
}

TEST(Parsing, serialise_calledOnEmptyMap_returnsEmptyString)
{
	std::map<std::string, std::string> input;
	EXPECT_EQ("", Parsing::serialise(input));
}

TEST(Parsing, serialise_calledOnMapWithOneItem_returnsCorrectString)
{
	std::map<std::string, std::string> input;
	input["foo"] = "bar";
	EXPECT_EQ("foo=bar", Parsing::serialise(input));
}

TEST(Parsing, serialise_calledOnMapWithMultipleItems_returnsCorrectString)
{
	std::map<std::string, std::string> input;
	input["foo"] = "bar";
	input["baz"] = "qux";
	input["zap"] = "zazzle";
	// Keys will be sorted alphabetically
	EXPECT_EQ("baz=qux&foo=bar&zap=zazzle", Parsing::serialise(input));
}
