#include <cstring>
#include <exception>
#include <sstream>
#include <string>
#include <map>
#include <utility>

#include "Parsing.h"

namespace CPals
{

std::map<std::string, std::string> KVParse(const std::string &input)
{
	std::map<std::string, std::string> result;

	auto offset = 0;
	auto equalsPos = 0;
	auto andPos = 0;
	do
	{
		// Find the next key
		equalsPos = input.find('=', offset);
		if (equalsPos == std::string::npos)
		{
			throw std::invalid_argument("Could not parse next key");
		}
		auto key = input.substr(offset, equalsPos - offset);
		if (key.size() == 0)
		{
			throw std::invalid_argument("Parsed an empty key");
		}

		// Find the next value
		andPos = input.find('&', equalsPos);
		const auto value = input.substr(equalsPos + 1,
										andPos - equalsPos - 1);
		if (value.size() == 0)
		{
			throw std::invalid_argument("Parsed an empty value");
		}

		result.insert(std::make_pair(key, value));
		offset = andPos + 1;
	} 
	while (andPos != std::string::npos);

	return result;
}

std::string KVSerialise(const std::map<std::string, std::string> &map)
{
	std::stringstream stream;

	bool isFirst = true;
	for (const auto pair : map)
	{
		if (isFirst)
		{
			isFirst = false;
		}
		else
		{
			stream << '&';
		}
			
		stream << pair.first << '=' << pair.second;
	}

	return stream.str();
}
}
