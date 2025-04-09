#pragma once
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

	//Command Without Spaces
	std::string commandWithoutComments;

	//Command Without Comments
	std::string commandWithoutSpacesAndComments;

	//Command Binary Code
	std::string commandInBinary;


	//ACommand member
	std::string address;

	//CCommand member
	std::string destination;
	std::string computation;
	std::string jump;

	CommandType VerifyCommandType(const std::string& input);
	bool is_number(const std::string& stringToVerify);
	std::string StringAssembly2StringBinaryCode(const std::string& input);
	void breakCommandCParts(const std::string& input);
	
public:
	Command( const std::string& commandLine);
	static std::string remove_spaces(const std::string& input);
	static std::string remove_comments(const std::string& input);
	std::string GetCommandBinaryCode();
	
};