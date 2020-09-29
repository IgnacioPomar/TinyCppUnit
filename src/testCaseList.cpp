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
	results.initResults ();
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		TestCaseList::runTest (testCase.first, testCase.second.get (), results);
	}

	results.endResults ();
	results.showResults ();
}


void TestCaseList::runSingleTest (const char * caseName, TestResults& results)
{
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		if (0 == testCase.first.compare (caseName))
		{
			TestCaseList::runTest (testCase.first, testCase.second.get (), results);
			break;
		}
	}
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

void TestResults::initResults ()
{
	this->start = std::chrono::high_resolution_clock::now ();
}

void TestResults::endResults ()
{
	this->end = std::chrono::high_resolution_clock::now ();
}


void TestResults::showResults ()
{
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->start).count ();

	std::cout << std::endl << std::endl;
	std::cout << "========== TEST FINISHED ========== " << std::endl;
	std::cout << "Test Cases: " << this->testCases << std::endl;
	std::cout << "Empty Cases: " << this->emptyCases << std::endl;
	std::cout << "Successful tests: " << this->successfulTests << std::endl;
	std::cout << "Failed tests: " << this->failedTests << std::endl;
	std::cout << "Duration: " << ((double)millis / 1000.) << " seconds" << std::endl;
	std::cout << "=================================== " << std::endl;
}
