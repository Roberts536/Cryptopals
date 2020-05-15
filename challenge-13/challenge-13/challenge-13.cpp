#include <cstdlib>
#include <iostream>
#include <string>

#include "Parsing.h"
#include "User.h"

std::string profileFor(std::string emailAddress)
{
	// Random IDs is sufficient for this challenge
	auto user = User(emailAddress, std::rand(), "user");
	std::string serialised = Parsing::serialise(user.toMap());
	return serialised;
}

int main()
{
	std::string emailAddress{ "myName@myDomain.com" };
	
	std::cout << "Email address: " << emailAddress
		<< "\nSerialised: " << profileFor(emailAddress) << std::endl;
}
