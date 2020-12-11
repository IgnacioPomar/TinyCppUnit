/*********************************************************************************************
*	Name		: testCaseList.cpp
*	Description	:
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/



#include "testCaseList.h"
#include "testCase.h"



void TestCaseList::addCase (const char * caseName, TestCase * casePtr)
{
	TestCaseCollection & col = TestCaseList::staticCases ();
	col[caseName] = std::unique_ptr<TestCase> (casePtr);
}




TestCaseCollection & TestCaseList::staticCases ()
{
	static TestCaseCollection collection;
	return collection;
}
