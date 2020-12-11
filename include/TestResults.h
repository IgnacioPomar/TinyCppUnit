/*********************************************************************************************
*	Name		: TestResults.h
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#pragma once
#ifndef _TEST_RESULTS_H_
#define _TEST_RESULTS_H_

#include <chrono> //MEasure execution time


#include "TinyCppUnit_cfg.h"

class TINYCPPUNIT_LOCAL TestResults
{
public:

	int successfulTests = 0;
	int failedTests = 0;
	int testCases = 0;
	int emptyCases = 0;


	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;

	void initResults ();
	void endResults ();
	void showResults ();
};

#endif
