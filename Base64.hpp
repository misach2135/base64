#ifndef BASE64ENCODER
#define BASE64ENCODER

#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <bitset>

namespace Base64
{
	static const char* BASE_64_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const char ELEMENT_NOT_FOUND = 65;
	const char NULL_BYTE = '=';

	char findIndex(const char& base64Sym)
	{
		for (char i = 0; i < 64; i++)
		{
			if (base64Sym == BASE_64_ALPHABET[i]) return i;
		}

		return ELEMENT_NOT_FOUND;
	}

	std::string encode(std::ifstream& input, std::ofstream& output)
	{
		if (!input.is_open()) return "";
		if (!output.is_open()) return "";

		std::vector<uint_fast8_t> buffer(std::istreambuf_iterator<char>(input), {});
		std::string res;

		const size_t k = (buffer.size() / 3) * 3;

		for (size_t i = 0; i < k; i += 3)
		{
			const char y_1 = buffer[i] >> 2;
			const char y_2 = ((buffer[i] & 3) << 4) | (buffer[i + 1] >> 4);
			const char y_3 = ((buffer[i + 1] & 15) << 2) | (buffer[i + 2] >> 6);
			const char y_4 = buffer[i + 2] & 63;

			res += BASE_64_ALPHABET[y_1];
			res += BASE_64_ALPHABET[y_2];
			res += BASE_64_ALPHABET[y_3];
			res += BASE_64_ALPHABET[y_4];
		}

		const size_t c = buffer.size() - k;

		switch (c)
		{
		case 0:
			break;
		case 1:
		{
			const char a_1 = buffer[k] >> 2;
			const char a_2 = ((buffer[k] & 3) << 4);

			res += BASE_64_ALPHABET[a_1];
			res += BASE_64_ALPHABET[a_2];
			res += NULL_BYTE;
			res += NULL_BYTE;
		}
			break;
		case 2:
		{
			const char b_1 = buffer[k] >> 2;
			const char b_2 = ((buffer[k] & 3) << 4) | (buffer[k + 1] >> 4);
			const char b_3 = ((buffer[k + 1] & 15) << 2);

			res += BASE_64_ALPHABET[b_1];
			res += BASE_64_ALPHABET[b_2];
			res += BASE_64_ALPHABET[b_3];
			res += NULL_BYTE;
		}
			break;
		}

		output << res;

		return res;
	}

	bool is_base64(unsigned char c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}

	void decode(std::ifstream& input, std::ofstream& output)
	{
		if (!input.is_open()) return;
		if (!output.is_open()) return;
		std::vector<char> buffer(std::istreambuf_iterator<char>(input), {});
	}
		
	
}

#endif
