/*********************************************************************************************
*	Name		: module.cpp
*	Description	: Entry point for the tester
*	Copyright	(C) 2020 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/


#include "CommandLineParser.h"
#include "testRunner.h"
#include "testModule.h"



//TODO: read parameters here
int ModuleMain::main (int argc, char * argv[])
{
	CommandLineParser cmdLine;
	cmdLine.addOption ("a", "all", "Run all tests (default option)", false);
	cmdLine.addOption ("s", "selected", "Run selected cases", false, -1);


	cmdLine.parse (argc, (const char **)argv);

	if (cmdLine.hasOption ("all"))
	{
		TestRunner::runAllTests ();
	}
	else if (cmdLine.hasOption ("selected"))
	{
		TestRunner runner;

		int numTests = cmdLine.getNumOptionValues ("selected");
		for (int i = 0; i < numTests; i++)
		{
			runner.runSingleTest (cmdLine.getOptionValue ("selected", i));
		}
		runner.endAndShowResults ();


	}
	else
	{
		TestRunner::runAllTests ();
	}



	return 0;
}


//TODO: allow working as a dll 
bool ModuleMain::dllMain (void * hDllHandle, unsigned long nReason, void * reserved)
{
	return false;
}
