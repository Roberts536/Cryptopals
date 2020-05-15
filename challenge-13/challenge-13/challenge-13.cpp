#include <cstdlib>
#include <string>

#include "Parsing.h"
#include "User.h"

int main()
{

}

std::string profileFor(std::string emailAddress)
{
	// Random IDs is sufficient for this challenge
	auto user = User(emailAddress, std::rand(), "user");
	std::string serialised = Parsing::serialise(user.toMap());
	return serialised;
}
