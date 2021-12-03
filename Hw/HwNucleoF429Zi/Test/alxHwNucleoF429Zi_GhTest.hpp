/**
  ******************************************************************************
  * @file alxHwNucleoF429Zi_GhTest.hpp
  * @brief Auralix HW NUCLEO-F429ZI C++ Library - GH Test Module
  * @version $LastChangedRevision: 2878 $
  * @date $LastChangedDate: 2021-04-13 19:33:15 +0200 (Tue, 13 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_HW_NUCLEO_F429ZI_GH_TEST_HPP
#define ALX_HW_NUCLEO_F429ZI_GH_TEST_HPP

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
	namespace AlxHwNucleoF429Zi_GhTest
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
						ALX_TRACE_STD("", "Test");	// Trace on pin PA9
						AlxDelay_ms(1000);
					}
				}
			public:
				Alx::AlxHwNucleoF429Zi_Main::Main main;
		};
		class G02_RangeTests
		{
			public:
				G02_RangeTests() {};
				virtual ~G02_RangeTests() {};
				void Init(void)
				{
					main.alxClkObj.Init();
					main.alxTraceObj.Init();
				}
				void Run(void)
				{
					T01_Range_Uint8();
					T02_Range_Uint16();
					T03_Range_Uint32();
					T04_Range_Uint64();
					T05_Range_Int8();
					T06_Range_Int16();
					T07_Range_Int32();
					T08_Range_Int64();
					T09_Range_Float();
					T10_Range_Double();
					T11_Range_Arr(); // TODO
					T12_Range_Str();
				}
				void T01_Range_Uint8(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckUint8(0, 100, 10);

					// #2 OutMin
					uint8_t min = 1;
					stat = AlxRange_CheckUint8(min, 10, 100);

					// #3 OutMax
					uint8_t max = 200;
					stat = AlxRange_CheckUint8(max, 10, 100);

					// #4 Ok
					uint8_t ok = 50;
					stat = AlxRange_CheckUint8(ok, 10, 100);
				}
				void T02_Range_Uint16(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckUint16(0, 50000, 100);

					// #2 OutMin
					uint16_t min = 10;
					stat = AlxRange_CheckUint16(min, 100, 50000);

					// #3 OutMax
					uint16_t max = 60000;
					stat = AlxRange_CheckUint16(max, 100, 50000);

					// #4 Ok
					uint16_t ok = 1000;
					stat = AlxRange_CheckUint16(ok, 100, 50000);
				}
				void T03_Range_Uint32(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckUint32(0, 4000000000, 1000);

					// #2 OutMin
					uint32_t min = 100;
					stat = AlxRange_CheckUint32(min, 1000, 4000000000);

					// #3 OutMax
					uint32_t max = 4100000000;
					stat = AlxRange_CheckUint32(max, 1000, 4000000000);

					// #4 Ok
					uint32_t ok = 10000;
					stat = AlxRange_CheckUint32(ok, 1000, 4000000000);
				}
				void T04_Range_Uint64(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckUint64(0, 500000000000000, 10);

					// #2 OutMin
					uint64_t min = 1;
					stat = AlxRange_CheckUint64(min, 10, 500000000000000);

					// #3 OutMax
					uint64_t max = 600000000000000;
					stat = AlxRange_CheckUint64(max, 10, 500000000000000);

					// #4 Ok
					uint64_t ok = 5000000000000;
					stat = AlxRange_CheckUint64(ok, 10, 500000000000000);
				}
				void T05_Range_Int8(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckInt8(0, 100, -100);

					// #2 OutMin
					int8_t min = -125;
					stat = AlxRange_CheckInt8(min, -100, 100);

					// #3 OutMax
					int8_t max = 125;
					stat = AlxRange_CheckInt8(max, -100, 100);

					// #4 Ok
					int8_t ok = 50;
					stat = AlxRange_CheckInt8(ok, -100, 100);
				}
				void T06_Range_Int16(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckInt16(0, 30000, -30000);

					// #2 OutMin
					int16_t min = -31000;
					stat = AlxRange_CheckInt16(min, -30000, 30000);

					// #3 OutMax
					int16_t max = 31000;
					stat = AlxRange_CheckInt16(max, -30000, 30000);

					// #4 Ok
					int16_t ok = 1000;
					stat = AlxRange_CheckInt16(ok, -30000, 30000);
				}
				void T07_Range_Int32(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckInt32(0, 2000000000, -2000000000);

					// #2 OutMin
					int32_t min = -2100000000;
					stat = AlxRange_CheckInt32(min, -2000000000, 2000000000);

					// #3 OutMax
					int32_t max = 2100000000;
					stat = AlxRange_CheckInt32(max, -2000000000, 2000000000);

					// #4 Ok
					int32_t ok = 10000;
					stat = AlxRange_CheckInt32(ok, -2000000000, 2000000000);
				}
				void T08_Range_Int64(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckInt64(0, 5000000000000000, -5000000000000000);

					// #2 OutMin
					int64_t min = -6000000000000000;
					stat = AlxRange_CheckInt64(min, -5000000000000000, 5000000000000000);

					// #3 OutMax
					int64_t max = 6000000000000000;
					stat = AlxRange_CheckInt64(max, -5000000000000000, 5000000000000000);

					// #4 Ok
					int64_t ok = 10000000000000;
					stat = AlxRange_CheckInt64(ok, -5000000000000000, 5000000000000000);
				}
				void T09_Range_Float(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckFloat(0.0, 3.402823466E+37, 1.175494351E-37);

					// #2 OutMin
					float min = 1.175494351E-38;
					stat = AlxRange_CheckFloat(min, 1.175494351E-37, 3.402823466E+37);

					// #3 OutMax
					float max = 3.402823466E+38;
					stat = AlxRange_CheckFloat(max, 1.175494351E-37, 3.402823466E+37);

					// #4 Ok
					float ok = 1.175494351E-10;
					stat = AlxRange_CheckFloat(ok, 1.175494351E-37, 3.402823466E+37);
				}
				void T10_Range_Double(void)
				{
					// #1 Assert
					 Alx_Status stat = AlxRange_CheckDouble(0.0, 1.7976931348623158E+307, 2.2250738585072014E-307);

					// #2 OutMin
					double min = 2.2250738585072014E-308;
					stat = AlxRange_CheckDouble(min, 2.2250738585072014E-307, 1.7976931348623158E+307);

					// #3 OutMax
					double max = 1.7976931348623158E+308;
					stat = AlxRange_CheckDouble(max, 2.2250738585072014E-307, 1.7976931348623158E+307);

					// #4 Ok
					double ok = 2.2250738585072014E-30;
					stat = AlxRange_CheckDouble(ok, 2.2250738585072014E-307, 1.7976931348623158E+307);
				}
				void T11_Range_Arr(void)
				{
					// #1 Assert
//					 Alx_Status stat = AlxRange_CheckArr(0.0, 3.402823466E+37, 1.175494351E-37);
//
//					// #2 OutMin
//					float min = 1.175494351E-38;
//					stat = AlxRange_CheckArr(min, 1.175494351E-37, 3.402823466E+37);
//
//					// #3 OutMax
//					float max = 3.402823466E+38;
//					stat = AlxRange_CheckArr(max, 1.175494351E-37, 3.402823466E+37);
//
//					// #4 Ok
//					float ok = 1.175494351E-10;
//					stat = AlxRange_CheckArr(ok, 1.175494351E-37, 3.402823466E+37);
				}
				void T12_Range_Str(void)
				{
					// #1 Assert
					Alx_Status stat = AlxRange_CheckStr((char*)"TestTest", 0);

					// #2 OutMax
					stat = AlxRange_CheckStr((char*)"TestTest", 4);

					// #2 Ok
					stat = AlxRange_CheckStr((char*)"Test", 6);
				}
			public:
				Alx::AlxHwNucleoF429Zi_Main::Main main;
		};
		class G03_BoundTests
		{
			public:
				G03_BoundTests() {};
				virtual ~G03_BoundTests() {};
				void Init(void)
				{
					main.alxClkObj.Init();
					main.alxTraceObj.Init();
				}
				void Run(void)
				{
					T01_Bound_Uint8();
					T02_Bound_Uint16();
					T03_Bound_Uint32();
					T04_Bound_Uint64();
					T05_Bound_Int8();
					T06_Bound_Int16();
					T07_Bound_Int32();
					T08_Bound_Int64();
					T09_Bound_Float();
					T10_Bound_Double();
					T11_Bound_Arr(); // TODO
					T12_Bound_Str();
				}
				void T01_Bound_Uint8(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Uint8(0, 100, 10);

					// #2 OutMin
					uint8_t min = 1;
					stat = AlxBound_Uint8(&min, 10, 100);

					// #3 OutMax
					uint8_t max = 200;
					stat = AlxBound_Uint8(&max, 10, 100);

					// #4 Ok
					uint8_t ok = 50;
					stat = AlxBound_Uint8(&ok, 10, 100);
				}
				void T02_Bound_Uint16(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Uint16(0, 50000, 100);

					// #2 OutMin
					uint16_t min = 10;
					stat = AlxBound_Uint16(&min, 100, 50000);

					// #3 OutMax
					uint16_t max = 60000;
					stat = AlxBound_Uint16(&max, 100, 50000);

					// #4 Ok
					uint16_t ok = 1000;
					stat = AlxBound_Uint16(&ok, 100, 50000);
				}
				void T03_Bound_Uint32(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Uint32(0, 4000000000, 1000);

					// #2 OutMin
					uint32_t min = 100;
					stat = AlxBound_Uint32(&min, 1000, 4000000000);

					// #3 OutMax
					uint32_t max = 4100000000;
					stat = AlxBound_Uint32(&max, 1000, 4000000000);

					// #4 Ok
					uint32_t ok = 10000;
					stat = AlxBound_Uint32(&ok, 1000, 4000000000);
				}
				void T04_Bound_Uint64(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Uint64(0, 500000000000000, 10);

					// #2 OutMin
					uint64_t min = 1;
					stat = AlxBound_Uint64(&min, 10, 500000000000000);

					// #3 OutMax
					uint64_t max = 600000000000000;
					stat = AlxBound_Uint64(&max, 10, 500000000000000);

					// #4 Ok
					uint64_t ok = 5000000000000;
					stat = AlxBound_Uint64(&ok, 10, 500000000000000);
				}
				void T05_Bound_Int8(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Int8(0, 100, -100);

					// #2 OutMin
					int8_t min = -125;
					stat = AlxBound_Int8(&min, -100, 100);

					// #3 OutMax
					int8_t max = 125;
					stat = AlxBound_Int8(&max, -100, 100);

					// #4 Ok
					int8_t ok = 50;
					stat = AlxBound_Int8(&ok, -100, 100);
				}
				void T06_Bound_Int16(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Int16(0, 30000, -30000);

					// #2 OutMin
					int16_t min = -31000;
					stat = AlxBound_Int16(&min, -30000, 30000);

					// #3 OutMax
					int16_t max = 31000;
					stat = AlxBound_Int16(&max, -30000, 30000);

					// #4 Ok
					int16_t ok = 1000;
					stat = AlxBound_Int16(&ok, -30000, 30000);
				}
				void T07_Bound_Int32(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Int32(0, 2000000000, -2000000000);

					// #2 OutMin
					int32_t min = -2100000000;
					stat = AlxBound_Int32(&min, -2000000000, 2000000000);

					// #3 OutMax
					int32_t max = 2100000000;
					stat = AlxBound_Int32(&max, -2000000000, 2000000000);

					// #4 Ok
					int32_t ok = 10000;
					stat = AlxBound_Int32(&ok, -2000000000, 2000000000);
				}
				void T08_Bound_Int64(void)
				{
					// #1 Assert
					Alx_Status stat = AlxBound_Int64(0, 5000000000000000, -5000000000000000);

					// #2 OutMin
					int64_t min = -6000000000000000;
					stat = AlxBound_Int64(&min, -5000000000000000, 5000000000000000);

					// #3 OutMax
					int64_t max = 6000000000000000;
					stat = AlxBound_Int64(&max, -5000000000000000, 5000000000000000);

					// #4 Ok
					int64_t ok = 10000000000000;
					stat = AlxBound_Int64(&ok, -5000000000000000, 5000000000000000);
				}
				void T09_Bound_Float(void)
				{
					// #1 Assert
					float Ass = 0.0f;
					Alx_Status stat = AlxBound_Float(&Ass, 3.402823466E+37, 1.175494351E-37);

					// #2 OutMin
					float min = 1.175494351E-38;
					stat = AlxBound_Float(&min, 1.175494351E-37, 3.402823466E+37);

					// #3 OutMax
					float max = 3.402823466E+38;
					stat = AlxBound_Float(&max, 1.175494351E-37, 3.402823466E+37);

					// #4 Ok
					float ok = 1.175494351E-10;
					stat = AlxBound_Float(&ok, 1.175494351E-37, 3.402823466E+37);
				}
				void T10_Bound_Double(void)
					{
						// #1 Assert
						double Ass = 0.0f;
						Alx_Status stat = AlxBound_Double(&Ass, 1.7976931348623158E+307, 2.2250738585072014E-307);

						// #2 OutMin
						double min = 2.2250738585072014E-308;
						stat = AlxBound_Double(&min, 2.2250738585072014E-307, 1.7976931348623158E+307);

						// #3 OutMax
						double max = 1.7976931348623158E+308;
						stat = AlxBound_Double(&max, 2.2250738585072014E-307, 1.7976931348623158E+307);

						// #4 Ok
						double ok = 2.2250738585072014E-30;
						stat = AlxBound_Double(&ok, 2.2250738585072014E-307, 1.7976931348623158E+307);
					}
				void T11_Bound_Arr(void)
				{
					// #1 Assert
//					 Alx_Status stat = AlxBound_Arr(0.0, 3.402823466E+37, 1.175494351E-37);
//
//					// #2 OutMin
//					float min = 1.175494351E-38;
//					stat = AlxBound_Arr(min, 1.175494351E-37, 3.402823466E+37);
//
//					// #3 OutMax
//					float max = 3.402823466E+38;
//					stat = AlxBound_Arr(max, 1.175494351E-37, 3.402823466E+37);
//
//					// #4 Ok
//					float ok = 1.175494351E-10;
//					stat = AlxBound_Arr(ok, 1.175494351E-37, 3.402823466E+37);
				}
				void T12_Bound_Str(void)
				{
					char boudned[20];

					// #1 Assert
					Alx_Status stat = AlxBound_Str(boudned, (char*)"TestTest", 0);

					// #2 OutMax
					stat = AlxBound_Str(boudned, (char*)"TestTest", 4);

					// #2 Ok
					stat = AlxBound_Str(boudned, (char*)"Test", 4);
				}
			public:
				Alx::AlxHwNucleoF429Zi_Main::Main main;
		};
		class G04_ParamItemTests
		{
		public:
			G04_ParamItemTests() {};
			virtual ~G04_ParamItemTests() {};
			void Init(void)
			{
				main.alxClkObj.Init();
				main.alxTraceObj.Init();
			}
			void Run(void)
			{
				T01_ParamItem_Uint8();
				//T02_ParamItem_Uint16();
				// TODO
			}
			void T01_ParamItem_Uint8(void)
			{

			}
			// TODO
		public:
			Alx::AlxHwNucleoF429Zi_Main::Main main;
			//Alx::AlxParamItem::ParamItem Item_Uint8  = { "Test", 1, 1,  (uint8_t)100,  (uint8_t)1,  (uint8_t)1000, AlxParamItem_ValOutOfRangeHandle_Assert };
			//Alx::AlxParamItem::ParamItem Item_Uint16 = { "Test", 1, 1, (uint16_t)100, (uint16_t)1, (uint16_t)1000, AlxParamItem_ValOutOfRangeHandle_Assert };
			// TODO
		};
	}
}

#endif // #if defined(ALX_HW_NUCLEO_F429ZI_CPP_TEST)

#endif // ALX_HW_NUCLEO_F429ZI_GH_TEST_HPP
