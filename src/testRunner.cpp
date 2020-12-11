/*********************************************************************************************
*	Name		: testRunner.cpp
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/


#include <iostream> //std::cout
#include "testCaseList.h"

#include "testRunner.h"



/**
 * Finds the size of the longest common path of all the tests
 */
void TestRunner::setBasePathSize ()
{
	std::string basePath;
	size_t maxCommonChars = -1;
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		std::string caseName (testCase.second->file);
		size_t slashPos = caseName.find_last_of ("/\\");
		caseName.erase (slashPos + 1);

		if (maxCommonChars == -1)
		{
			basePath = caseName;
			maxCommonChars = slashPos;
		}
		else
		{
			if (maxCommonChars > slashPos)
			{
				maxCommonChars = slashPos;
			}

			for (size_t i = 0; i <= maxCommonChars; i++)
			{
				if (basePath.at (i) != caseName.at (i))
				{
					maxCommonChars = i;
					break;
				}
			}
			if (maxCommonChars == 0) break;
		}
	}


	basePathSize = maxCommonChars;

}

/**
 * Shows the file path and the name of the case
 *
 * \param [in] caseName		Name of the case to run
 * \param [in] testCase		Pointer to the case
 */
void TestRunner::echoCaseIdentifier (std::string caseName, TestCase * testCase)
{
	std::string caseFile (testCase->file);
	caseFile.erase (0, basePathSize);

	std::cout << "." << caseFile << "\t> " << caseName << std::endl;
}

/**
 * Run the case
 *
 * \param [in] caseName		Name of the case to run
 * \param [in] testCase		Pointer to the case
 */
void TestRunner::runTest (std::string caseName, TestCase * testCase)
{
	results.testCases++;
	try
	{
		echoCaseIdentifier (caseName, testCase);

		//YAGNI: should we call the clock only if isTimedCase?
		auto caseStart = std::chrono::high_resolution_clock::now ();
		testCase->runTest ();
		auto caseEnd = std::chrono::high_resolution_clock::now ();

		if (testCase->successfulTests == 0 && testCase->failedTests == 0)
		{
			std::cout << "\t* Empty Test" << std::endl;
			results.emptyCases++;
		}

		if (testCase->isTimedCase)
		{
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(caseEnd - caseStart).count ();
			std::cout << "\t* Execution time: " << ((double)millis / 1000.) << std::endl;
		}


	}
	catch (int) {}
	results.failedTests += testCase->failedTests;
	results.successfulTests += testCase->successfulTests;
}


/**
 * Run all the cases
 */
void TestRunner::runAllTests ()
{
	TestRunner runner;
	for (auto const& testCase : TestCaseList::staticCases ())
	{
		runner.runTest (testCase.first, testCase.second.get ());
	}
	runner.endAndShowResults ();
}



/**
 * Constructor: init the timer and set the base path size
 */
TestRunner::TestRunner ()
{
	setBasePathSize ();
	results.initResults ();
}


/**
 * Search and run a named case
 *
 * \param [in] caseName		Name of the case to run
 */
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

/**
* Closes the timer and prints the results
*/
void TestRunner::endAndShowResults ()
{
	results.endResults ();
	results.showResults ();
}
