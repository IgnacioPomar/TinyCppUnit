

#include "testCaseList.h"
#include "testModule.h"

//TODO: read parameters here
int ModuleMain::main (int argc, char * argv [])
{
	TestCaseList::runAllTests ();
	return 0;
}


//TODO: allow working as a dll 
bool ModuleMain::dllMain (void * hDllHandle, unsigned long nReason, void * reserved)
{
	return false;
}
