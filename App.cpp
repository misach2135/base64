#include <iostream>

#include <direct.h>

#include "Base64.hpp"

static const char* inputFilePath = "\\test_data\\file3.txt";
static const char* encodedFilePath = "\\test_data\\file3Encoded.base64";
static const char* decodedFilePath = "\\test_data\\file3Decoded.txt";

int main()
{
	using namespace std;

	ifstream inputFile;
	ofstream outputFile;

	std::string cwd = _getcwd(NULL, 0);

	inputFile.open(cwd + inputFilePath, std::ios_base::binary | std::ios::in);
	outputFile.open(cwd + encodedFilePath);
	cout << "Encode: " << std::endl;
	cout << Base64::encode(inputFile, outputFile) << endl;

	inputFile.close();
	outputFile.close();

	inputFile.open(cwd + encodedFilePath);
	outputFile.open(cwd + decodedFilePath, ios::binary);

	cout << "Decode: " << std::endl;
	cout << Base64::decode(inputFile, outputFile) << endl;

	inputFile.close();
	outputFile.close();

	return 0;
}