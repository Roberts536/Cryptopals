#pragma once

#include <string>
#include <map>

#include "KVParser.h"

namespace Parsing
{

/*
Parse an input string and produce a map. Accepts input of the form:

foo=bar&baz=qux&zap=zazzle

and produces a map of the form:

{
	foo: 'bar',
	baz: 'qux',
	zap: 'zazzle'
}

Parameters:
	input: the input string to parse.

Returns:
	A map of keys and values parsed from the input string.
*/
std::map<std::string, std::string> parse(const std::string &input);

}
