/*********************************************************************************************
*	Name		: testRunner.h
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#pragma once
#ifndef _TEST_RUNNER_H_
#define _TEST_RUNNER_H_


#include <chrono> //MEasure execution time
#include <string>

#include "TinyCppUnit_cfg.h"

#include "TestResults.h"
#include "testCase.h"



class TINYCPPUNIT_LOCAL TestRunner
{
private:
	TestResults results;

	void runTest (std::string, TestCase*);

public:
	static void runAllTests ();


	TestRunner ();
	void runSingleTest (const char * caseName);
	void endAndShowResults ();

};


#endif //_TEST_RUNNER_H_
