#pragma once

#include "cryptoUtils/cryptoUtils.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

void test_encryption()
{
	std::vector<byte> plaintext{
		'H', 'E', 'L', 'L', 'O',
		'W', 'O', 'R', 'L', 'D',
		'H', 'E', 'L', 'L', 'O',
		'W' };
	byte key[AES::DEFAULT_KEYLENGTH]{
		'Y', 'E', 'L', 'L', 'O', 'W', ' ',
		'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E' };
	byte IV[AES::BLOCKSIZE]{
		'1', '1', '1', '1', '1', '1', '1', '1',
		'1', '1', '1', '1', '1', '1', '1', '1'
	};

	std::vector<byte> ciphertext{
		AesEncrypt(AES_CBC, plaintext, key, IV) };

	// byte hexOutput[AES::BLOCKSIZE * 2 + 1];

	std::stringstream ret;
	for (byte b : ciphertext)
	{
		ret << std::hex << std::setfill('0') << std::setw(2)
			<< static_cast<unsigned>(b);
	}

	std::cout << "\nCiphertext:\t" << ret.str() << std::endl;
}
