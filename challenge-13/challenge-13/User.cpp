#include "User.h"

#include <map>
#include <string>
#include <utility>

/*
Member function to serialise the User into a map.
*/
std::map<std::string, std::string> User::toMap()
{
	auto result = std::map<std::string, std::string>();
	result.insert(std::make_pair("email", emailAddress));
	result.insert(std::make_pair("id", std::to_string(id)));
	result.insert(std::make_pair("role", role));
	
	return result;
}
