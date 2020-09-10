
#include "CommandLineParser.h"
#include "testCaseList.h"
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
		TestCaseList::runAllTests ();
	}
	else if (cmdLine.hasOption ("selected"))
	{
		TestResults results;
		results.initResults ();
		int numTests = cmdLine.getNumOptionValues ("selected");
		for (int i = 0; i < numTests; i++)
		{
			TestCaseList::runSingleTest (cmdLine.getOptionValue ("selected", i), results);
		}
		results.endResults ();
		results.showResults ();

	}
	else
	{
		TestCaseList::runAllTests ();
	}



	return 0;
}


//TODO: allow working as a dll 
bool ModuleMain::dllMain (void * hDllHandle, unsigned long nReason, void * reserved)
{
	return false;
}
