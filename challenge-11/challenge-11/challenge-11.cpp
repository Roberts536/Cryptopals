#pragma once

#include "cryptoUtils/cryptoUtils.h"

#include <ctime>
#include <iostream>
#include <random>

int main()
{
	std::mt19937 mt_prng{ 
		static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	AES_MODE mode{
		DetectAesMode(EncryptionOracle, mt_prng)
	};

	std::cout << aesModeNames[mode] << std::endl;
	
}
