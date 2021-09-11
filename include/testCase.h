/*********************************************************************************************
*	Name		: testCase.h
*	Description	: Abstract class for each test case
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#pragma once
#ifndef _TEST_CASE_H_
#define _TEST_CASE_H_

#include "TinyCppUnit_cfg.h"

//TODO: Configure if working in dll mode or exe mode. Actually doing both

class TINYCPPUNIT_API TestCase
{
public:
	virtual void runTest () = 0;

	int successfulTests = 0;
	int failedTests = 0;

	bool isTimedCase = false;
	const char * file;

	const char * getFilename ();

protected:
	void showMessage (const char * msg, const char * tag = nullptr);
	bool check (bool cond, const char * func, int lineNum);
	bool require (bool cond, const char * func, int lineNum);
	bool checkIsClose (double left, double right, double tolerance, const char * leftStr, const char * rightStr, int lineNum);
private:
	void stdFailActions (const char * func, int lineNum);
	void stdSuccessActions (const char * func);

};


//Clase en la que están los servicios Que se han generado estáticamente
class TINYCPPUNIT_API StaticCaseAutoRegister
{
public:
	StaticCaseAutoRegister (const char * casename, TestCase * testCase);
};


//__BASE_FILE__

#define UNIT_TEST_CASE(Case) class _##Case       : public TestCase {public: void runTest (); _##Case () {isTimedCase=false;file=__FILE__;}};  \
StaticCaseAutoRegister AutoRegister_##Case (#Case, new _##Case()); \
void _##Case::runTest ()

#define UNIT_TEST_TIMED_CASE(Case) class _##Case : public TestCase {public: void runTest (); _##Case () {isTimedCase=true;file=__FILE__;}};  \
StaticCaseAutoRegister AutoRegister_##Case (#Case, new _##Case()); \
void _##Case::runTest ()

#define UNIT_CHECK_CLOSE(left, right, tolerance) this->checkIsClose (left, right, tolerance, #left, #right, __LINE__)
#define UNIT_CHECK(cond) this->check (cond, #cond, __LINE__)
#define UNIT_REQUIRE(cond) this->require (cond, #cond, __LINE__)
#define UNIT_MESSAGE(msg) this->showMessage (##msg)

#endif //_TEST_CASE_H_
