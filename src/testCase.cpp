﻿/*********************************************************************************************
*	Name		: testCase.cpp
*	Description	: test case generic functions
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#include <cstring> // for strrchr 
#include <iostream> //std::cout

#include "testCaselist.h"
#include "testCase.h"

const char *   TestCase::getFilename ()
{
	//we want only the file name, not the path
	const char * pch;
	pch = strrchr (this->file, '/');
	if (pch == nullptr)
	{
		pch = strrchr (this->file, '\\');
	}

	return (pch != nullptr) ? ++pch : this->file;
}


void TestCase::showMessage (const char * msg, const char * tag)
{
	//TODO: when multithread, we will need control
	if (tag == nullptr) tag = "\t[message]";
	std::cout << tag << " " << msg << std::endl;

}



bool TestCase::check (bool cond, const char * func, int lineNum)
{
	if (cond)
	{
		this->stdSuccessActions (func);
	}
	else
	{
		this->stdFailActions (func, lineNum);
	}

	return cond;
}

bool TestCase::require (bool cond, const char * func, int lineNum)
{
	this->check (cond, func, lineNum);
	if (!cond)
	{
		throw int (1); //we break the case
	}

	return cond;
}

bool TestCase::checkIsClose (double left, double right, double tolerance, const char * leftStr, const char * rightStr, int lineNum)
{
	std::string condMessage = leftStr;
	condMessage.append (" is near ").append (rightStr);

	double diff = (left > right) ? left - right : right - left;
	return this->check (diff < tolerance, condMessage.c_str (), lineNum);
}

void TestCase::stdFailActions (const char * func, int lineNum)
{
	this->failedTests++;

	std::string tag = "\t[Fail:";
	tag.append (std::to_string (lineNum));
	tag.append ("]");
	this->showMessage (func, tag.c_str ());
}

void TestCase::stdSuccessActions (const char * func)
{
	this->successfulTests++;
}


StaticCaseAutoRegister::StaticCaseAutoRegister (const char * casename, TestCase * testCase)
{
	TestCaseList::addCase (casename, testCase);
}
