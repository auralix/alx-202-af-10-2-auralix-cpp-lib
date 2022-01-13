/**
  ******************************************************************************
  * @file alxHwNucleoF429Zi_MfTest.hpp
  * @brief Auralix HW NUCLEO-F429ZI C++ Library - MF Test Module
  * @version $LastChangedRevision: 2878 $
  * @date $LastChangedDate: 2021-04-13 19:33:15 +0200 (Tue, 13 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_HW_NUCLEO_F429ZI_MF_TEST_HPP
#define ALX_HW_NUCLEO_F429ZI_MF_TEST_HPP

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
	namespace AlxHwNucleoF429Zi_MfTest
	{
		class G01_BringUp
		{
			public:
				G01_BringUp() {};
				virtual ~G01_BringUp() {};
			public:
				void Init(void)
				{
					main.alxClkObj.Init();
					main.alxTraceObj.Init();
				}
				void Run(void)
				{
					T01_Trace();
					//T02_IoPin();
				}
			public:
				void T01_Trace(void)
				{
					while(1)
					{
						ALX_TRACE_STD("", "Test");
						AlxDelay_ms(1000);
					}
				}
				void T02_IoPin(void)
				{
					while (1)
					{
						// TOGGLE PIN
						AlxDelay_ms(500);
					}
				}
			public:
				Alx::AlxHwNucleoF429Zi_Main::Main main;
		};
		class G02_ParamExamples
		{
			public:
				G02_ParamExamples() {};
				virtual ~G02_ParamExamples() {};
			public:
				void Init(void)
				{
					main.alxClkObj.Init();
					main.alxTraceObj.Init();
				}
				void Run(void)
				{
					//T01_ChangeValue();
					T02_TestBond();
				}
			public:
				void T01_ChangeValue(void)
				{
					/*uint8_t x = 0;

					x = height_mm.GetValUint8();

					Alx_Status stat = height_mm.SetValUint8(5);

					x = height_mm.GetValUint8();

					height_mm.SetValToDef();

					x = height_mm.GetValUint8();

					x = 0;*/
				}
				void T02_TestBond(void)
				{
					uint8_t no = 20;

					Alx_Status stat = AlxBound_Uint8(&no, 15, 15);

					no = 0;
				}
			public:
				Alx::AlxHwNucleoF429Zi_Main::Main main;
				//Alx::AlxParamItem::ParamItem height01_mm = { "Test", 1, 1, (uint8_t) 100, (uint8_t) 2, (uint8_t) 150, AlxParamItem_ValOutOfRangeHandle_Assert };
				//Alx::AlxParamItem::ParamItem height02_mm = { "Test", 1, 1, (uint16_t)100, (uint16_t)2, (uint16_t)150, AlxParamItem_ValOutOfRangeHandle_Assert };
				//Alx::AlxParamItem::ParamItem_Uint8 height_mm("Test", 1, 1, 100, 2, 150, AlxParamItem_ValOutOfRangeHandle_Assert);
		};
	}
}


#endif // #if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)

#endif // ALX_HW_NUCLEO_F429ZI_MF_TEST_HPP
