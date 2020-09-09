/*********************************************************************************************
*	Name		: testCaseList.cpp
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#include <chrono> //MEasure execution time
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
	auto start = std::chrono::high_resolution_clock::now ();
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		TestCaseList::runTest (testCase.first, testCase.second.get (), results);
	}
	auto end = std::chrono::high_resolution_clock::now ();

	results.allCasesDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count ();

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

		std::chrono::time_point<std::chrono::steady_clock> start;
		if (testCase->isTimedCase)
		{
			start = std::chrono::high_resolution_clock::now ();
		}

		testCase->runTest ();

		if (testCase->successfulTests == 0 && testCase->failedTests == 0)
		{
			std::cout << "[Empty Test]" << std::endl;
			results.emptyCases++;
		}

		if (testCase->isTimedCase)
		{
			auto end = std::chrono::high_resolution_clock::now ();
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count ();
			std::cout << "Execution time: " << ((double)millis / 1000.) << std::endl;
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
	std::cout << "Empty Cases: " << this->emptyCases << std::endl;
	std::cout << "Successful tests: " << this->successfulTests << std::endl;
	std::cout << "Failed tests: " << this->failedTests << std::endl;
	std::cout << "Duration: " << ((double)this->allCasesDuration / 1000.) << " seconds" << std::endl;
	std::cout << "=================================== " << std::endl;
}
