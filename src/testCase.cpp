/*********************************************************************************************
*	Name		: testCase.cpp
*	Description	: test case generic functions
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#include <iostream> //std::cout

#include "testCaselist.h"
#include "testCase.h"


void TestCase::showMessage (const char * msg)
{
	//TODO: when multithread, we will need control
	std::cout << msg;

}

//TODO: only one funtion to print all errors
void TestCase::check (bool cond, const char * func)
{
	if (!cond)
	{
		std::string msg = "[Fail] ";
		msg.append (func);
		this->showMessage (msg.c_str ());

		throw int (1); //we break the flow
	}
}

void TestCase::require (bool cond, const char * func)
{
	if (!cond)
	{
		std::string msg = "[Fail] ";
		msg.append (func);
		this->showMessage (msg.c_str());

		throw int (1); //we break the flow
	}
}


StaticCaseAutoRegister::StaticCaseAutoRegister (const char * casename, TestCase * testCase)
{
	TestCaseList::addCase (casename, testCase);
}

