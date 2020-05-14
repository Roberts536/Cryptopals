/*
Cryptopals Challenges
Challenge 7: Decrypt AES in ECB mode with a known key
*/
#include "main.h"

int main(int argc, char* argv[])
{
	const std::string in_filename{ "7.txt" };
	const std::string binary_filename{ "raw.bin" };

	byte key[AES::DEFAULT_KEYLENGTH];
	std::memcpy(&key, "YELLOW SUBMARINE", 16);
	
	std::string cipher, recovered;

	std::ifstream inf(in_filename);
	if (!inf)
	{
		std::cerr << "Could not open file: "
			<< in_filename << " for reading.\n";
		std::exit(1);
	}
	std::ofstream binf(binary_filename, 
		std::ios_base::out | std::ios_base::binary);
	if (!binf)
	{
		std::cerr << "Could not open file: "
			<< binary_filename << " for reading.\n";
		std::exit(1);
	}

	while (inf)
	{
		string line;
		getline(inf, line);

		const std::string decoded{ base64_decode(line) };
		cipher += decoded;
		binf << decoded;
	}

	try
	{
		ECB_Mode< AES >::Decryption d;
		d.SetKey(key, sizeof(key));

		StringSource s(cipher, true,
			new StreamTransformationFilter(d,
				new StringSink(recovered)
			)
		);

		cout << "Recovered text: " << recovered << endl;
	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		std::exit(1);
	}

	return 0;
}
