#pragma once

#include <string>
#include <map>

#include "parsing.h"

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

/*
Undo the parsing operation by serialising a map into a string.

Takes a map of the form:

{
	foo: 'bar',
	baz: 'qux',
	zap: 'zazzle'
}

and produces a string of the form:

foo=bar&baz=qux&zap=zazzle

Input:
	map: The map to serialise.
*/
std::string serialise(std::map<std::string, std::string> map);

}
