#include <iostream>
#include <tclap/CmdLine.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <yld/chat.h>

using namespace std;
using json = nlohmann::json;

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

	// Define a value argument and add it to the command line.
	// A value arg defines a flag and a type of value that it expects,
	// such as "-n Bishop".
	TCLAP::ValueArg<std::string> continuationArg("c","continuation","Continuation key of youtube live chat. "
												 "README for more information.",true,"homer","string");

	// Add the argument nameArg to the CmdLine object. The CmdLine object
	// uses this Arg to parse the command line.
	cmd.add( continuationArg );

	TCLAP::ValueArg<std::string> timeStartArg("", "timestart","When to start fetching chat result",false,"homer","int");
	cmd.add( timeStartArg );

	TCLAP::ValueArg<std::string> timeEndArg("","timeend","When to stop fetching chat result",false,"homer","int");
	cmd.add( timeEndArg );

	// Define a switch and add it to the command line.
	// A switch arg is a boolean argument and only defines a flag that
	// indicates true or false.  In this example the SwitchArg adds itself
	// to the CmdLine object as part of the constructor.  This eliminates
	// the need to call the cmd.add() method.  All args have support in
	// their constructors to add themselves directly to the CmdLine object.
	// It doesn't matter which idiom you choose, they accomplish the same thing.
	TCLAP::SwitchArg reverseSwitch("r","reverse","Print name backwards", cmd, false);

	// Parse the argv array.
	cmd.parse( argc, argv );

	// Get the value parsed by each arg. 
	std::string continuation = continuationArg.getValue();
	bool reverseName = reverseSwitch.getValue();

	unsigned long timeStart = timeStartArg.isSet() ? stoi(timeStartArg.getValue()) : 0;
	unsigned long timeEnd = timeEndArg.isSet() ? stoi(timeEndArg.getValue()) : 0;
	
	// Do what you intend.
	if ( reverseName )
	{
		std::reverse(continuation.begin(),continuation.end());
		std::cout << "My name (spelled backwards) is: " << continuation << std::endl;
	}
	else
		std::cout << "Continuation: " << continuation << std::endl;
		std::cout << "TimeStart: " << timeStart << std::endl;
		std::cout << "TimeEnd: " << timeEnd << std::endl;

		yld::Chat kekw{continuation, timeStart, timeEnd};

	} catch (TCLAP::ArgException &e)  // catch exceptions
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
}