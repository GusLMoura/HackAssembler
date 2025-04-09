#include "Command.h"
#include <iostream>
#include <bitset>
#include <sstream>
#include <string>


Command::Command(const std::string& commandLine)
{
	type = VerifyCommandType(commandLine);
	std::cout << "CommandLine1: " << commandLine << std::endl;
	commandInBinary = StringAssembly2StringBinaryCode(commandLine);
}

std::string Command::GetCommandBinaryCode()
{
	return commandInBinary;
}

CommandType Command::VerifyCommandType(const std::string& input)
{
	if (input[0] == '@')
	{
		return CommandType::ACommand;
	}
	else if (input[0] == '(')
	{
		return CommandType::label;
	}
	else
	{
		return CommandType::CCommand;
	}
}

std::string Command::remove_spaces(const std::string& input) {
	std::string result = input;
	result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
	return result;
}

std::string Command::remove_comments(const std::string& input) {
	std::string result;
	std::stringstream ss(input);
	std::string line;
	bool in_block_comment = false;

	while (std::getline(ss, line)) {
		size_t pos = 0;

		while (pos < line.size()) {
			if (in_block_comment) {
				size_t end_block = line.find("*/", pos);
				if (end_block != std::string::npos) {
					in_block_comment = false;
					pos = end_block + 2;
				}
				else {
					break;
				}
			}
			else {
				size_t start_single = line.find("//", pos);
				size_t start_block = line.find("/*", pos);

				if (start_single != std::string::npos && (start_block == std::string::npos || start_single < start_block)) {
					result += line.substr(pos, start_single - pos);
					break;
				}
				else if (start_block != std::string::npos) {
					result += line.substr(pos, start_block - pos);
					in_block_comment = true;
					pos = start_block + 2;
				}
				else {
					result += line.substr(pos);
					break;
				}
			}
		}

		if (!in_block_comment) {
			result += '\n';
		}
	}
	return result;
}

bool Command::is_number(const std::string& stringToVerify) {
	std::istringstream iss(stringToVerify);
	double doubleToStoreNumber;
	return (iss >> std::noskipws >> doubleToStoreNumber) && (iss.peek() == EOF);
}

std::string Command::StringAssembly2StringBinaryCode(const std::string& input)
{
	std::string binaryCommand;

	if (type == CommandType::ACommand)
	{
		std::string numberInString = input.substr(1);
		if (is_number(numberInString))
		{
			std::string zero = "0";
			std::string value = std::bitset<15>(std::stoi(numberInString)).to_string();
			binaryCommand = zero + value;
		}
	}
	else if (type == CommandType::CCommand)
	{
		std::string destinationInBinary;
		std::string computationInBinary;
		std::string jumpInBinary;

		breakCommandCParts(input);

		if (destination == "null")
		{
			destinationInBinary = "000";
		}
		else if(destination == "M")
		{
			destinationInBinary = "001";
		}
		else if (destination == "D")
		{
			destinationInBinary = "010";
		}
		else if (destination == "MD")
		{
			destinationInBinary = "011";
		}
		else if (destination == "A")
		{
			destinationInBinary = "100";
		}
		else if (destination == "AM")
		{
			destinationInBinary = "101";
		}
		else if (destination == "AD")
		{
			destinationInBinary = "110";
		}
		else if (destination == "AMD")
		{
			destinationInBinary = "111";
		}
		else
		{
			std::cout << "Error: Destination Error - Destination Code not Found" << std::endl;
		}

		if (computation == "0")
		{
			computationInBinary = "0101010";
		}
		else if (computation == "1")
		{
			computationInBinary = "0111111";
		}
		else if (computation == "-1")
		{
			computationInBinary = "0111010";
		}
		else if (computation == "-1")
		{
			computationInBinary = "0111010";
		}
		else if (computation == "D")
		{
			computationInBinary = "0001100";
		}
		else if (computation == "A")
		{
			computationInBinary = "0110000";
		}
		else if (computation == "!D")
		{
			computationInBinary = "0001101";
		}
		else if (computation == "!A")
		{
			computationInBinary = "0110001";
		}
		else if (computation == "-D")
		{
			computationInBinary = "0001111";
		}
		else if (computation == "-A")
		{
			computationInBinary = "0110011";
		}
		else if (computation == "D+1")
		{
			computationInBinary = "0011111";
		}
		else if (computation == "A+1")
		{
			computationInBinary = "0110111";
		}
		else if (computation == "D-1")
		{
			computationInBinary = "0001110";
		}
		else if (computation == "A-1")
		{
			computationInBinary = "0110010";
		}
		else if (computation == "D+A")
		{
			computationInBinary = "0000010";
		}
		else if (computation == "D-A")
		{
			computationInBinary = "0010011";
		}
		else if (computation == "A-D")
		{
			computationInBinary = "0000111";
		}
		else if (computation == "D&A")
		{
			computationInBinary = "0000000";
		}
		else if (computation == "D|A")
		{
			computationInBinary = "0010101";
		}
		else if (computation == "M")
		{
			computationInBinary = "1110000";
		}
		else if (computation == "!M")
		{
			computationInBinary = "1110011";
		}
		else if (computation == "M+1")
		{
			computationInBinary = "1110111";
		}
		else if (computation == "D+M")
		{
			computationInBinary = "1000010";
		}
		else if (computation == "D-M")
		{
			computationInBinary = "1010011";
		}
		else if (computation == "M-D")
		{
			computationInBinary = "1000111";
		}
		else if (computation == "D&M")
		{
			computationInBinary = "1000000";
		}
		else if (computation == "D|M")
		{
			computationInBinary = "1010101";
		}
		else
		{
			std::cout << "Error: Computation Error - Computation Code not Found" << std::endl;
		}

		if (jump == "null")
		{
			jumpInBinary = "000";
		}
		else if (jump == "JGT")
		{
			jumpInBinary = "001";
		}
		else if (jump == "JEQ")
		{
			jumpInBinary = "010";
		}
		else if (jump == "JGE")
		{
			jumpInBinary = "011";
		}
		else if (jump == "JLT")
		{
			jumpInBinary = "100";
		}
		else if (jump == "JNE")
		{
			jumpInBinary = "101";
		}
		else if (jump == "JLE")
		{
			jumpInBinary = "110";
		}
		else if (jump == "JMP")
		{
			jumpInBinary = "111";
		}
		else
		{
			std::cout << "Error: Jump Error - Jump Code not Found" << std::endl;
		}

		std::string ones = "111";
		binaryCommand = ones + computationInBinary + destinationInBinary + jumpInBinary;
	}
	return binaryCommand;
}

void Command::breakCommandCParts(const std::string& input)
{
	size_t delimiter1position = input.find('=');
	if (delimiter1position != std::string::npos)
	{
		std::string firstStepLeftPart = input.substr(0, delimiter1position);
		destination = firstStepLeftPart;
		std::string firstStepRightPart = input.substr(delimiter1position + 1);
		size_t delimiter2position = firstStepRightPart.find(';');
		if (delimiter2position != std::string::npos)
		{
			std::string secondStepLeftPart = firstStepRightPart.substr(0, delimiter2position);
			computation = secondStepLeftPart;
			std::string secondStepRightPart = firstStepRightPart.substr(delimiter2position + 1);
			jump = secondStepRightPart;
		}
		else
		{
			jump = "null";
			computation = firstStepRightPart;
		}

	}
	else
	{
		destination = "null";
		size_t delimiter2position = input.find(';');
		if (delimiter2position != std::string::npos)
		{
			std::string secondStepLeftPart = input.substr(0, delimiter2position);
			computation = secondStepLeftPart;
			std::string secondStepRightPart = input.substr(delimiter2position + 1);
			jump = secondStepRightPart;
		}
		else
		{
			jump = "null";
			computation = input;
		}
	}
}


