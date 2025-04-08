#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 2)
	{
		std::cout << "Invalid Parameter Number: maximum parameter number is 1." << argc << std::endl;
		return -1;
	}

	std::fstream inputFile;
	inputFile.open(argv[1], std::ios::in);
	if (inputFile.is_open())
	{
		std::string line;
		while (getline(inputFile, line))
		{
			std::cout << line << std::endl;
		}
		inputFile.close();
	}
	else
	{
		std::cout << "Could not find or read the input File." << argc << std::endl;
		return -1;
	}

	std::cout << "argc: " << argc << std::endl;
}