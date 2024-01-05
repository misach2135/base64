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
		if (base64Sym == NULL_BYTE) return 0; // Так має бути, бо інакше не працює)
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

	std::string decode(std::ifstream& input, std::ofstream& output)
	{
		if (!input.is_open()) return "";
		if (!output.is_open()) return "";
		std::vector<char> buffer(std::istreambuf_iterator<char>(input), {});
		std::string res;

		if (buffer.size() % 4 != 0)
		{
			std::cerr << "Size of encoded text must divide by 4" << std::endl;
			return "";
		}

		for (size_t i = 0; i < buffer.size(); i += 4)
		{
			if (!is_base64(buffer[i]) && !is_base64(buffer[i + 1]) && !is_base64(buffer[i + 2]) && !is_base64(buffer[i + 3]))
			{
				std::cerr << "Quarter " << i << ": it is not base64 symbol." << std::endl;
				return "";
			}

			const char y_1 = findIndex(buffer[i]);
			const char y_2 = findIndex(buffer[i + 1]);
			const char y_3 = findIndex(buffer[i + 2]);
			const char y_4 = findIndex(buffer[i + 3]);


			const char x_1 = (y_1 << 2) | ((y_2 & 0b00110000) >> 4);
			const char x_2 = ((y_2 & 0b00001111) << 4) | ((y_3 & 0b00111100) >> 2);
			const char x_3 = (((y_3 & 0b00000011) << 6) | y_4);

			res.push_back(x_1);
			res.push_back(x_2);
			res.push_back(x_3);

		}

		output << res;

		return res;

	}
		
	
}

#endif
