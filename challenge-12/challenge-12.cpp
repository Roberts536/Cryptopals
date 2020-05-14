#include "cryptoUtils/cryptoUtils.h"
#include "cpp-base64/base64.h"

#include <ctime>
#include <iostream>
#include <string>

typedef unsigned char byte;

int main()
{
	std::mt19937 mt_prng{
		static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	AES_MODE mode{ 
		DetectAesMode(Challenge12Oracle, mt_prng, AES::BLOCKSIZE) };

	if (mode == AES_ECB)
	{
		std::cout << "The oracle is using ECB mode!\n";

		const size_t blockSize{ 
			FindEcbBlockSize(Challenge12Oracle, mt_prng) };

		std::cout << "The block size is: " << blockSize << '\n';

		bytevec addendum{
			FindAddendumFromEcbOracle(
				Challenge12Oracle,
				mt_prng,
				AES::BLOCKSIZE) };

		std::cout << "The addendum is:\n\n";
		for (byte b : addendum)
		{
			std::cout << b;
		}
		std::cout << "\nLength: " << addendum.size() << std::endl;
	}

}
