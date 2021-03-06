/**
  ******************************************************************************
  * @file alxDac.hpp
  * @brief Auralix C++ Library - ALX DAC Module
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_DAC_HPP
#define ALX_DAC_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxDac_Mcu.h>
#include <alxDac.h>
#include <alxIoPin.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxDac
	{
		class IDac
		{
			public:
				IDac() {};
				virtual ~IDac() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status Init(float vref_V) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V) = 0;
				virtual ::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V, float vref_V) = 0;
		};
		class ADac : public IDac
		{
			public:
				ADac() {};
				virtual ~ADac() {};
				::Alx_Status Init(void) override
				{
					return AlxDac_Init(&dac);
				}
				::Alx_Status Init(float vref_V) override
				{
					return AlxDac_Init_CalibrateVref(&dac, vref_V);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxDac_DeInit(&dac);
				}
				::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V) override
				{
					return AlxDac_SetVoltage_V(&dac, ch, voltage_V);
				}
				::Alx_Status SetVoltage_V(::Alx_Ch ch, float voltage_V, float vref_V) override
				{
					return AlxDac_SetVoltage_V_CalibrateVref(&dac, ch, voltage_V, vref_V);
				}
			protected:
				::AlxDac dac = {};
		};
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class DacMcu : public ADac
		{
			public:
				DacMcu
				(
					DAC_TypeDef* dac,
					AlxIoPin::IIoPin** ioPinArr,
					::Alx_Ch* chArr,
					float* setVoltageDefaultArr_V,
					uint8_t numOfCh,
					bool isVrefInt_V,
					float vrefExt_V
				)
				{
					for (uint32_t i = 0; i < numOfCh; i++)
					{
						AlxIoPin::IIoPin* temp = *(ioPinArr + i);
						dacIoPinArr[i] = temp->GetCStructPtr();
					}
					
					AlxDacMcu_Ctor(&dacMcu, dac, dacIoPinArr, chArr, setVoltageDefaultArr_V, numOfCh, isVrefInt_V, vrefExt_V);
					AlxDac_Ctor(&this->dac, AlxDac_Submodule_Mcu, &dacMcu);
				};
				virtual ~DacMcu() {};
			private:
				::AlxDac_Mcu dacMcu = {};
				::AlxIoPin* dacIoPinArr[ALX_DAC_BUFF_LEN] = {0};
		};
		#endif
		#if defined(ALX_GTEST)
		class MockDac final : public IDac
		{
			public:
				MOCK_METHOD(::Alx_Status, Init, (), (override));
				MOCK_METHOD(::Alx_Status, Init, (float voltage_V), (override));
				MOCK_METHOD(::Alx_Status, DeInit, (), (override));
				MOCK_METHOD(::Alx_Status, SetVoltage_V, (::Alx_Ch ch, float voltage_V), (override));
				MOCK_METHOD(::Alx_Status, SetVoltage_V, (::Alx_Ch ch, float voltage_V, float vref_V), (override));
		};
		#endif
	}
}

#endif // ALX_DAC_HPP
