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

	// Pseudo-random 3-digit IDs are sufficient for this challenge
	const auto id = std::rand() % 900 + 100;
	const auto user = User(emailAddress, id, "user");
	const std::string serialised = KVSerialise(user.toMap());
	return serialised;
}
}

namespace
{
constexpr std::size_t blockSize{ 16 };
}

int main()
{
	const auto key{ CPals::StringToBuffer("YELLOW SUBMARINE") };
	CPals::AesEcbCipher cipher;

	/*
	First we construct a profile whose second 16-byte block will be
	"admin\x00...\x00" i.e. a padded block starting with "admin". Since
	ECB encrypts block by block, the second block of the ciphertex will be the
	encrypted version of this block.
	*/
	std::string email{ "xxxxxxxxxxadmin" };
	for (auto i = 0; i < 11; i++)
	{
		email.push_back(0);
	}
	email.append("@bar.com");

	auto encodedProfile{ CPals::profileFor(email) };
	auto ciphertext{
		cipher.Encrypt(CPals::StringToBuffer(encodedProfile), key) };

	CPals::Buffer adminBlock;
	std::copy_n(ciphertext.cbegin() + blockSize,
				blockSize,
				std::back_inserter(adminBlock));

	/*
	Next we construct a profile which has "user" on its own at the start of
	its final block. This will be padded to "user\x00...\x00", and we can swap
	that encrypted block with the encrypted admin block we just made.

	Let's suppose we know the ids have three digits. We could deduce this by
	submitting progressively longer email addresses until the ciphertext
	overflows into the next block.
	*/
	email = "admin@bar.com";
	encodedProfile = CPals::profileFor(email);
	ciphertext = cipher.Encrypt(CPals::StringToBuffer(encodedProfile), key);
	
	std::copy_n(adminBlock.begin(),
				blockSize,
				ciphertext.end() - blockSize);

	/*
	Suppose the attacker has sent their modified ciphertext to the server. The
	server now decrypts the ciphertext and processes the new profile.
	*/
	const auto plaintext{ cipher.Decrypt(ciphertext, key) };
	const std::string plaintextString{ plaintext.cbegin(), plaintext.cend() };

	const auto profile{ CPals::KVParse(plaintextString) };
	std::cout << "Decrypted profile received by the server:" << std::endl;
	for (const auto pair : profile)
	{
		std::cout << pair.first << " : " << pair.second << std::endl;
	}

	return 0;
}
