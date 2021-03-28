#include <iostream>
#include <tclap/CmdLine.h>
#include <nlohmann/json.hpp>
#include <yld/chat.h>
// #include <include/core/SkCanvas.h>

using namespace std;

int main(int argc, char** argv)
{
	// Wrap everything in a try block.  Do this every time, 
	// because exceptions will be thrown for problems.
	try {

	// Define the command line object, and insert a message
	// that describes the program. The "Command description message" 
	// is printed last in the help text. The second argument is the 
	// delimiter (usually space) and the last one is the version number. 
	// The CmdLine object parses the argv array based on the Arg objects
	// that it contains. 
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");

	TCLAP::ValueArg<std::string> chatResponseJsonFileArg("i","input","ChatResponses json file",true,"","string");
	cmd.add( chatResponseJsonFileArg );

	TCLAP::ValueArg<std::string> outputFileArg("o","output","Output file path",false,"","string");
	cmd.add( outputFileArg );

	// Parse the argv array.
	cmd.parse( argc, argv );

	std::string chatResponseJsonFile = chatResponseJsonFileArg.getValue();
	std::string outputFile = outputFileArg.getValue();
	
	std::cout << "InputFile: " << chatResponseJsonFile << std::endl;
	std::cout << "OutputFile: " << outputFile << std::endl;

	std::vector<yld::ChatResponse> chatResponses;
	yld::ChatResponse::ReadFileToChatResponses(chatResponseJsonFile, chatResponses);

	} catch (TCLAP::ArgException &e)  // catch exceptions
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
}