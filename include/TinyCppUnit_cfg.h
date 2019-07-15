/*********************************************************************************************
 *	Name		: TinyCppUnit_cfg.h
 *	Description	: Configuration of the project
 ********************************************************************************************/

#pragma once
#ifndef _TINYCPPUNIT_CFG_H_
#define _TINYCPPUNIT_CFG_H_

 //If the solution is a dinamic library (dll), we need the next macro
#define TINYCPPUNIT_DLL

//IMPORTANT: the project who exports must have the preprocessor macro TINYCPPUNIT_DLL_EXPORTS

//see http://gcc.gnu.org/wiki/Visibility

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#define TINYCPPUNIT_HELPER_DLL_IMPORT __declspec(dllimport)
#define TINYCPPUNIT_HELPER_DLL_EXPORT __declspec(dllexport)
#define TINYCPPUNIT_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define TINYCPPUNIT_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define TINYCPPUNIT_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define TINYCPPUNIT_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define TINYCPPUNIT_HELPER_DLL_IMPORT
#define TINYCPPUNIT_HELPER_DLL_EXPORT
#define TINYCPPUNIT_HELPER_DLL_LOCAL
#endif
#endif

// Now we use the generic helper definitions above to define TINYCPPUNIT_API and TINYCPPUNIT_LOCAL.
// TINYCPPUNIT_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// TINYCPPUNIT_LOCAL is used for non-api symbols.

#ifdef TINYCPPUNIT_DLL // defined if TINYCPPUNIT is compiled as a DLL
#ifdef TINYCPPUNIT_EXPORTS // defined if we are building the TINYCPPUNIT DLL (instead of using it)
#define TINYCPPUNIT_API TINYCPPUNIT_HELPER_DLL_EXPORT
#else
#define TINYCPPUNIT_API TINYCPPUNIT_HELPER_DLL_IMPORT
#endif // TINYCPPUNIT_DLL_EXPORTS
#define TINYCPPUNIT_LOCAL TINYCPPUNIT_HELPER_DLL_LOCAL
#else // TINYCPPUNIT_DLL is not defined: this means TINYCPPUNIT is a static lib.
#define TINYCPPUNIT_API
#define TINYCPPUNIT_LOCAL
#endif // TINYCPPUNIT_DLL


#endif //_TINYCPPUNIT_CFG_H_
