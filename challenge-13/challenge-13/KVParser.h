#pragma once

#include <string>
#include <map>

/*
A K-V parser designed to accept input of the form:

foo=bar&baz=qux&zap=zazzle

and produce a map of the form:

{
  foo: 'bar',
  baz: 'qux',
  zap: 'zazzle'
}
*/
class KVParser
{
public:
	/*
	Constructor
	*/
	KVParser();

	/*
	Parse an input string and produce a map.

	Parameters:
		input: the input string to parse.

	Returns:
		A map of keys and values parsed from the input string.
	*/
	std::map<std::string, std::string> parse(const std::string input);
};


