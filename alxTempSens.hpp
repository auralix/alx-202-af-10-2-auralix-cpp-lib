/**
  ******************************************************************************
  * @file alxTempSens.hpp
  * @brief Auralix C++ Library - ALX Temperature Sensor Module
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_TEMP_SENS_HPP
#define ALX_TEMP_SENS_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxAdc.hpp>
#include <alxInterpLin.hpp>
#include <alxTempSens_Mcu.h>
#include <alxTempSens.h>
#include <alxTempSens_RtdVdiv.h>

//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTempSens
	{
		class ITempSens
		{
			public:
				ITempSens() {};
				virtual ~ITempSens() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status GetTemp_degC(float *temp_degC) = 0;
		};
		class ATempSens : public ITempSens
		{
			public:
				ATempSens() {};
				virtual ~ATempSens() {};
				::Alx_Status Init(void) override
				{
					return AlxTempSens_Init(&tempSens);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxTempSens_DeInit(&tempSens);
				}
				::Alx_Status GetTemp_degC(float *temp_degC) override
				{
					return AlxTempSens_GetTemp_degC(&tempSens, temp_degC);
				}
			protected:
				::AlxTempSens tempSens = {};
		};
		class TempSensRtd : public ATempSens
		{
			public:
				TempSensRtd
				(
					AlxAdc::IAdc* adc,
					AlxInterpLin::IInterpLin* interpLin,
					Alx_Ch chAdc_Vin,
					Alx_Ch chAdc_Vout,
					bool isResRtdLow,
					float resOther_kOhm
				)
				{
					AlxTempSensRtdVdiv_Ctor
					(
						&me,
						adc->GetCStructPtr(),
						interpLin->GetCStructPtr(),
						chAdc_Vin,
						chAdc_Vout,
						isResRtdLow,
						resOther_kOhm
					);
					AlxTempSens_Ctor
					(
						&tempSens,
						AlxTempSens_Submodule_Rtd_Vdiv,
						&me
					);
				};
				virtual ~TempSensRtd() {};
			private:
			::AlxTempSensRtdVdiv me = {};
		};
		
		#if defined(ALX_GTEST)
		class MockTempSens final : public ITempSens
		{
			public:
				MOCK_METHOD(::Alx_Status, Init, (), (override));
				MOCK_METHOD(::Alx_Status, DeInit, (), (override));
				MOCK_METHOD(float, GetTemp_degC, (void), (override));
		};
		#endif
	}
}

#endif // ALX_TEMP_SENS_HPP
