/*********************************************************************************************
*	Name		: module.cpp
*	Description	: Entry point for the tester
*	Copyright	(C) 2019 Ignacio Pomar Ballestero
*	License		: see unlicense.txt
********************************************************************************************/

#pragma once
#ifndef _MODULE_H_
#define _MODULE_H_

#include "TinyCppUnit_cfg.h"

//TODO: Configure if working in dll mode or exe mode. Actually doing both

class TINYCPPUNIT_API ModuleMain
{
public:
	static  int main (int argc, char * argv []);
	static bool dllMain (void * hDllHandle, unsigned long nReason, void * reserved);

private:
	//int		
};



#define UNIT_TEST_MODULE_EXE int main (int argc, char * argv []){return ModuleMain::main (argc,argv);}

#ifdef _WIN32
#include <windows.h>
#define UNIT_TEST_MODULE_DLL  BOOLEAN WINAPI DllMain (IN HINSTANCE hDllHandle,IN DWORD nReason, IN LPVOID Reserved) {return ModuleMain::dllMain (hDllHandle, nReason, Reserved);}
#else
#define UNIT_TEST_MODULE_DLL 
#endif 



#define UNIT_TEST_MODULE UNIT_TEST_MODULE_EXE UNIT_TEST_MODULE_DLL

#endif



