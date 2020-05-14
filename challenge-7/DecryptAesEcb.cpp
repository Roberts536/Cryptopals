#include "DecryptAesEcb.h"

std::string DecryptAesEcb(
	const std::string &ciphertext,
	const byte *key,
	const std::size_t keySizeBytes)
/*
Decrypt ciphertext which has been encrypted with AES in ECB mode, 
using a known key.

Parameters:
	ciphertex:		The AES-encrypted ciphertext.
	key:			Pointer to non null-terminated AES key.
	keySizeBytes:	The size of the key in bytes.

Returns:
	deciphered:	(std::string) The plaintext.

Throws:
	CryptoPP::Exception
*/
{
	std::string plaintext;

	ECB_Mode< AES >::Decryption d;
	d.SetKey(key, keySizeBytes);

	StringSource s(ciphertext, true,
		new StreamTransformationFilter(d,
			new StringSink(plaintext)
		)
	);
	
	return plaintext;
}
