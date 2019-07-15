/*********************************************************************************************
*	Name		: testCaseList.cpp
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#include <iostream> //std::cout

#include "testCaseList.h"
#include "testCase.h"



void TestCaseList::addCase (const char * caseName, TestCase * casePtr)
{
	TestCaseCollection & col = TestCaseList::staticCases ();
	col [caseName] = std::unique_ptr<TestCase> (casePtr);
}


//TODO: random run, multithread run, exclusions, etc...
void TestCaseList::runAllTests ()
{
	for (auto const& testCAse : TestCaseList::staticCases ())
	{
		try
		{
			//TODO: in need to configure Messages of Debug
			std::cout << "Entering " << testCAse.first << std::endl;
			testCAse.second->runTest ();
		}
		catch (int i)
		{
			
		}
	}
}

TestCaseCollection & TestCaseList::staticCases ()
{
	static TestCaseCollection collection;
	return collection;
}

