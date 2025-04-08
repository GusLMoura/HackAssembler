#pragma once
#include <memory> // Para std::unique_ptr
#include <string>

enum class CommandType : char
{
	Undefined,
	ACommand,
	CCommand,
	label
};

class Command
{
private:
	CommandType type;

	//ACommand member
	std::unique_ptr<std::string> address;

	//CCommand member
	std::unique_ptr<std::string> destination;
	std::unique_ptr<std::string> computation;
	std::unique_ptr<std::string> jump;
	
public:
	Command(const char* line);
	CommandType VerifyCommandType(const char* line);
	std::string GetBinaryCode();
};