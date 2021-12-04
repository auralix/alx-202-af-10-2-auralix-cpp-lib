/**
  ******************************************************************************
  * @file alxHwNucleoF429Zi_MainTest.hpp
  * @brief Auralix HW NUCLEO-F429ZI C++ Library - Main Test Module
  * @version $LastChangedRevision: 2849 $
  * @date $LastChangedDate: 2021-04-12 13:35:09 +0200 (Mon, 12 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_HW_NUCLEO_F429ZI_MAIN_TEST_HPP
#define ALX_HW_NUCLEO_F429ZI_MAIN_TEST_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxHwNucleoF429Zi_Main.hpp>
#include <alxHwNucleoF429Zi_GhTest.hpp>
//#include <alxHwNucleoF429Zi_GkTest.hpp>
//#include <alxHwNucleoF429Zi_JkTest.hpp>
#include <alxHwNucleoF429Zi_MfTest.hpp>
#include <alxHwNucleoF429Zi_TvTest.hpp>


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxHwNucleoF429Zi_MainTest
	{
		class MainTest
		{
			public:
				MainTest() {};
				virtual ~MainTest() {};
				void Init(void)
				{
					// Gh
					//AlxHwNucleoF429Zi_GhTest_G01_BringUp.Init();
					//AlxHwNucleoF429Zi_GhTest_G02_RangeTests.Init();
					//AlxHwNucleoF429Zi_GhTest_G03_BoundTests.Init();

					// Gk

					// Jk

					// Mf
					//AlxHwNucleoF429Zi_MfTest_G01_BringUp.Init();
					//AlxHwNucleoF429Zi_MfTest_G02_ParamExamples.Init();

					// Tv
					AlxHwNucleoF429Zi_TvTest_G01_BringUp.Init();
				}
				void Run(void)
				{
					// Gh
					//AlxHwNucleoF429Zi_GhTest_G01_BringUp.Run();
					//AlxHwNucleoF429Zi_GhTest_G02_RangeTests.Run();
					//AlxHwNucleoF429Zi_GhTest_G03_BoundTests.Run();

					// Gk

					// Jk

					// Mf
					//AlxHwNucleoF429Zi_MfTest_G01_BringUp.Run();
					//AlxHwNucleoF429Zi_MfTest_G02_ParamExamples.Run();

					// Tv
					AlxHwNucleoF429Zi_TvTest_G01_BringUp.Run();
				}
			public:
				// Gh
				//AlxHwNucleoF429Zi_GhTest::G01_BringUp AlxHwNucleoF429Zi_GhTest_G01_BringUp;
				//AlxHwNucleoF429Zi_GhTest::G02_RangeTests AlxHwNucleoF429Zi_GhTest_G02_RangeTests;
				//AlxHwNucleoF429Zi_GhTest::G03_BoundTests AlxHwNucleoF429Zi_GhTest_G03_BoundTests;

				// Gk

				// Jk

				// Mf
				//AlxHwNucleoF429Zi_MfTest::G01_BringUp AlxHwNucleoF429Zi_MfTest_G01_BringUp;
				//AlxHwNucleoF429Zi_MfTest::G02_ParamExamples AlxHwNucleoF429Zi_MfTest_G02_ParamExamples;

				// Tv
				AlxHwNucleoF429Zi_TvTest::G01_BringUp AlxHwNucleoF429Zi_TvTest_G01_BringUp;
		};

		extern MainTest mainTest;
	}
}


#endif // #if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)

#endif // ALX_HW_NUCLEO_F429ZI_MAIN_TEST_HPP
