#include "User.h"

#include <map>
#include <string>
#include <utility>

/*
Constructor for the User struct.
*/
User::User(const std::string &emailAddress,
		   const int id,
		   const std::string &role)
	: emailAddress(emailAddress), id(id), role(role)
{ }

/*
Member function to serialise the User into a map.
*/
std::map<std::string, std::string> User::toMap() const
{
	auto result = std::map<std::string, std::string>();
	result["email"] = emailAddress;
	result["id"] = std::to_string(id);
	result["role"] = role;
	
	return result;
}
