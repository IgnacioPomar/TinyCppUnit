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




UNIT_TEST_CASE (my_test)
{
	// ways to detect and report the same error:
	UNIT_CHECK(add (2, 2) == 4);        // #1 continues on error

	UNIT_REQUIRE(add (2, 2) == 4);      // #2 throws on error
	
	UNIT_MESSAGE( "add(..) result: " );


	//May be in the future
	//UNIT_CHECK_EQUAL (add (2, 2), 4);	  // #7 continues on error
}

