#include "Command.h"
#include <iostream>
#include <bitset>


Command::Command(const char* line)
{
	type = VerifyCommandType(line);
}

CommandType Command::VerifyCommandType(const char* line)
{
	if (line[0] == '@')
	{
		return CommandType::ACommand;
	}
	else if (line[0] == '(')
	{
		return CommandType::label;
	}
	else
	{
		return CommandType::CCommand;
	}
}

std::string Command::GetBinaryCode()
{
	if (type == CommandType::ACommand)
	{

		std::string value = std::bitset<15>(128).to_string();
	}
	return std::string();
}
