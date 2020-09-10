/*********************************************************************************************
*	Name		: testCaseList.h
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#pragma once
#ifndef _TEST_CASE_LIST_H_
#define _TEST_CASE_LIST_H_

#include <memory>
#include <unordered_map>
#include <string>
#include <chrono> //MEasure execution time

#include "TinyCppUnit_cfg.h"


class TestCase;


typedef std::unordered_map <std::string, std::unique_ptr<TestCase>> TestCaseCollection;

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


class TINYCPPUNIT_LOCAL TestCaseList
{
public:
	static void addCase (const char *, TestCase *);
	static void runAllTests ();
	static void runSingleTest (const char * caseName, TestResults&);
private:
	static TestCaseCollection & staticCases ();
	static void runTest (std::string, TestCase*, TestResults&);
};


#endif //_TEST_CASE_LIST_H_
