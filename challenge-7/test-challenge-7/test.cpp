#include "base64.h"
#include "DecryptAesEcb.h"
#include "gtest/gtest.h"

#include <string>

typedef unsigned char byte;

//std::string DecryptAesEcb(
//	const std::string &ciphertext,
//	const byte *key,
//	const std::size_t keySizeBytes);

TEST(TestEcbDecrypt, TestDecryptSingleBlock) {

	//EXPECT_TRUE(true);
	// Plaintext "helloworldhellow", key "YELLOW SUBMARINE"
	std::string ciphertext{
		"MucZD5AsGU53f02KLm+HPcDKWQAVkm0n9G/P7krAepg=" };
	ciphertext = base64_decode(ciphertext);

	byte key[16];
	std::memcpy(&key, "YELLOW SUBMARINE", 16);

	std::string plaintext{
		DecryptAesEcb(ciphertext, key, 16) };

	EXPECT_EQ(plaintext, "helloworldhellow");
}
