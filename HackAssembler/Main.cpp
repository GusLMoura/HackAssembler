#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
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

	std::string inputFileName(argv[1]);
	size_t delimiterposition = inputFileName.find('.');
	if (delimiterposition != std::string::npos)
	{
		std::string inputFileNameStepLeftPart = inputFileName.substr(0, delimiterposition);
		std::string outputFileName = inputFileNameStepLeftPart + ".hack";
		outputFile.open(outputFileName, std::ios::out);
	}

	if (inputFile.is_open() && outputFile.is_open())
	{
		std::string line;
		std::vector<std::string> binaryCommands;

		while (std::getline(inputFile, line)) 
		{
			std::string lineWithoutComments = Command::remove_comments(line);
			std::string lineWithoutCommentsAndSpaces = Command::remove_spaces(lineWithoutComments);

			if (!lineWithoutCommentsAndSpaces.empty()) 
			{
				std::unique_ptr<Command> ptr = std::make_unique<Command>(line);
				binaryCommands.push_back(ptr->GetCommandBinaryCode());
			}
		}

		for (size_t i = 0; i < binaryCommands.size(); ++i) 
		{
			outputFile << binaryCommands[i];
			if (i < binaryCommands.size() - 1) 
			{ 
				outputFile << '\n';
			}
			std::cout << "Binary Code: " << binaryCommands[i] << std::endl;
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