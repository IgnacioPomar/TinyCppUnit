/*********************************************************************************************
*	Name		: TestResults.cpp
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#include <iostream> //std::cout

#include "TestResults.h"


/**
 * record the launch time
 */
void TestResults::initResults ()
{
	this->start = std::chrono::high_resolution_clock::now ();
}

/**
* record the end time
*/
void TestResults::endResults ()
{
	this->end = std::chrono::high_resolution_clock::now ();
}

/**
* shows the final results
*/
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
