#pragma once

#include <map>
#include <string>

/*
Struct representing a user on a system.
*/
struct User
{
	std::string emailAddress;
	int id;
	std::string role;

	User(const std::string &emailAddress, 
		 const int id,
		 const std::string &role);
	std::map<std::string, std::string> toMap() const;
};
