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

#include "TinyCppUnit_cfg.h"


class TestCase;


typedef std::unordered_map <std::string, std::unique_ptr<TestCase>> TestCaseCollection;



class TINYCPPUNIT_LOCAL TestCaseList
{
public:
	static void addCase (const char *, TestCase *);

	static TestCaseCollection & staticCases ();
};


#endif //_TEST_CASE_LIST_H_
