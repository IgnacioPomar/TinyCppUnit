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
	col[caseName] = std::unique_ptr<TestCase> (casePtr);
}


//TODO: random run, multithread run, exclusions, etc...
void TestCaseList::runAllTests ()
{
	TestResults results;
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		TestCaseList::runTest (testCase.first, testCase.second.get (), results);
	}
	results.showResults ();
}

TestCaseCollection & TestCaseList::staticCases ()
{
	static TestCaseCollection collection;
	return collection;
}


void TestCaseList::runTest (std::string  caseName, TestCase* testCase, TestResults & results)
{
	results.testCases++;
	try
	{
		std::cout << "*** Entering " << caseName << std::endl;
		testCase->runTest ();

		if (testCase->successfulTests == 0 && testCase->failedTests == 0)
		{
			std::cout << "[Empty Test]" << std::endl;
		}

	}
	catch (int) {}
	results.failedTests += testCase->failedTests;
	results.successfulTests += testCase->successfulTests;
}

void TestResults::showResults ()
{
	std::cout << std::endl << std::endl;
	std::cout << "========== TEST FINISHED ========== " << std::endl;
	std::cout << "Test Cases: " << this->testCases << std::endl;
	std::cout << "Successful tests: " << this->successfulTests << std::endl;
	std::cout << "Failed tests: " << this->failedTests << std::endl;
	std::cout << "=================================== " << std::endl;
}
