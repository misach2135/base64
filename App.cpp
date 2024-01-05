#include <iostream>

#include <direct.h>

#include "Base64.hpp"

int main()
{
	using namespace std;

	ifstream inputFile;
	ofstream outputFile;

	std::string cwd = _getcwd(NULL, 0);

	inputFile.open(cwd + "\\input.txt", std::ios_base::binary | std::ios::in);
	outputFile.open(cwd + "\\output.base64");

	cout << Base64::encode(inputFile, outputFile) << endl;

	inputFile.close();
	outputFile.close();
	return 0;
}