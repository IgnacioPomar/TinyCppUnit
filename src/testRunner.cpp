/*********************************************************************************************
*	Name		: testRunner.cpp
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/


#include <iostream> //std::cout
#include "testCaseList.h"

#include "testRunner.h"

void TestRunner::runTest (std::string caseName, TestCase * testCase)
{
	results.testCases++;
	try
	{
		std::cout << "> " << testCase->getFilename () << " > " << caseName << std::endl;

		//YAGNI: should we call the clock only if isTimedCase?
		auto caseStart = std::chrono::high_resolution_clock::now ();
		testCase->runTest ();
		auto caseEnd = std::chrono::high_resolution_clock::now ();

		if (testCase->successfulTests == 0 && testCase->failedTests == 0)
		{
			std::cout << "\t Empty Test" << std::endl;
			results.emptyCases++;
		}

		if (testCase->isTimedCase)
		{
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(caseEnd - caseStart).count ();
			std::cout << "Execution time: " << ((double)millis / 1000.) << std::endl;
		}


	}
	catch (int) {}
	results.failedTests += testCase->failedTests;
	results.successfulTests += testCase->successfulTests;
}

void TestRunner::runAllTests ()
{
	TestRunner runner;
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		runner.runTest (testCase.first, testCase.second.get ());
	}
	runner.endAndShowResults ();
}

TestRunner::TestRunner ()
{
	results.initResults ();
}

void TestRunner::runSingleTest (const char * caseName)
{
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		if (0 == testCase.first.compare (caseName))
		{
			runTest (testCase.first, testCase.second.get ());
			break;
		}
	}
}


void TestRunner::endAndShowResults ()
{
	results.endResults ();
	results.showResults ();
}
