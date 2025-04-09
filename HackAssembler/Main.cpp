#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Command.h"

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 2)
	{
		std::cout << "Invalid Parameter Number: maximum parameter number is 1." << argc << std::endl;
		return -1;
	}

	//Eliminate spaces and commented code + save symbols in the symbol table
	std::fstream inputFile;
	std::fstream outputFile;

	inputFile.open(argv[1], std::ios::in);
	outputFile.open("output.asm", std::ios::out);
	if (inputFile.is_open() && outputFile.is_open())
	{
		std::string line;
		while (getline(inputFile, line))
		{
			std::string lineWithoutComments = Command::remove_comments(line);
			std::string lineWithoutCommentsAndSpaces = Command::remove_spaces(lineWithoutComments);
			if (!lineWithoutCommentsAndSpaces.empty())
			{
				Command* ptr = new Command(line);
				std::string newBinaryCommand = ptr->GetCommandBinaryCode();
				std::cout << "Binary Code." << newBinaryCommand << std::endl;
			}
		}
		inputFile.close();
		outputFile.close();
	}
	else
	{
		std::cout << "Could not find or read the input File." << argc << std::endl;
		return -1;
	}


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