#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

#include "AesEcbCipher.h"
#include "Buffer.h"
#include "Parsing.h"
#include "User.h"

namespace CPals
{

std::string profileFor(std::string emailAddress)
{
	// Sanitise
	std::remove(std::begin(emailAddress), std::end(emailAddress), '=');
	std::remove(std::begin(emailAddress), std::end(emailAddress), '&');

	// Random IDs is sufficient for this challenge
	auto user = User(emailAddress, std::rand(), "user");
	std::string serialised = KVSerialise(user.toMap());
	return serialised;
}
}

int main()
{
	auto encodedProfile{ CPals::profileFor("myName@myDomain.com") };
	auto key{ CPals::StringToBuffer("YELLOW SUBMARINE") };

	CPals::AesEcbCipher cipher;
	CPals::Buffer ciphertext{ cipher.Encrypt(CPals::StringToBuffer(encodedProfile), key) };

	CPals::Buffer plaintext{ cipher.Decrypt(ciphertext, key) };
	std::string plaintextString{ plaintext.cbegin(), plaintext.cend() };

	std::map<std::string, std::string> profile{ CPals::KVParse(plaintextString) };
	std::cout << "Decrypted profile:" << std::endl;
	for (const auto pair : profile)
	{
		std::cout << pair.first << " : " << pair.second << std::endl;
	}

	return 0;
}
