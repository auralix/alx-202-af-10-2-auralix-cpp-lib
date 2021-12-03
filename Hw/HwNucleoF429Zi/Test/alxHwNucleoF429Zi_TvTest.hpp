/**
  ******************************************************************************
  * @file alxHwNucleoF429Zi_TvTest.hpp
  * @brief Auralix HW NUCLEO-F429ZI C++ Library - TV Test Module
  * @version $LastChangedRevision: 2878 $
  * @date $LastChangedDate: 2021-04-13 19:33:15 +0200 (Tue, 13 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_HW_NUCLEO_F429ZI_TV_TEST_HPP
#define ALX_HW_NUCLEO_F429ZI_TV_TEST_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxHwNucleoF429Zi_Main.hpp>


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxHwNucleoF429Zi_TvTest
	{
		class G01_BringUp
		{
			public:
				G01_BringUp() {};
				virtual ~G01_BringUp() {};
				void Init(void)
				{
					main.alxClkObj.Init();
					main.alxTraceObj.Init();
				}
				void Run(void)
				{
					T01_Trace();
				}
				void T01_Trace(void)
				{
					while(1)
					{
						ALX_TRACE_STD("", "Test");
						AlxDelay_ms(500);
					}
				}
			public:
				Alx::AlxHwNucleoF429Zi_Main::Main main;
		};
	}
}

#endif // #if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)

#endif // ALX_HW_NUCLEO_F429ZI_TV_TEST_HPP
