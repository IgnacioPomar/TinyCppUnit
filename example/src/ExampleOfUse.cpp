/*********************************************************************************************
*	Name		: ExampleOfUse.cpp
*	Description	: File showing how o use the library
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#ifdef _DEBUG 
#define END_LIB_STD "d.lib"
#else
#define END_LIB_STD ".lib"
#endif


#pragma comment(lib, "TinyCppUnit" END_LIB_STD)


#include <tinyCppUnit.h>

int add (int i, int j) { return i + j; }


UNIT_TEST_MODULE




UNIT_TEST_CASE (working_test)
{
	UNIT_CHECK_CLOSE (1.0001, 1.0002, 0.001);
	UNIT_CHECK(add (2, 2) == 4); 
	UNIT_REQUIRE(add (2, 2) == 4);
	UNIT_MESSAGE ("Random message");

}

UNIT_TEST_CASE (failing_test)
{
	UNIT_CHECK (add (2, 2) == 5);
	UNIT_CHECK_CLOSE (1.0001, 1.003, 0.001);
	UNIT_REQUIRE (add (2, 2) == 5);     
	UNIT_MESSAGE ("never arriving message");
	

}
