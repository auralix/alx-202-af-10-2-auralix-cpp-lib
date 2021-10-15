/**
  ******************************************************************************
  * @file alxAdc_HwTest.hpp
  * @brief Auralix C++ Library - ALX ADC Module - Test
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_ADC_HW_TEST_HPP
#define ALX_ADC_HW_TEST_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTick.hpp>
#include <alxClk.hpp>
#include <alxTrace.hpp>
#include <alxIoPin.hpp>
#include <alxAdc.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAdcHwTest
	{
		#if defined(ALX_STM32F4)
		class AdcHwTest_Mcu
		{
			public:
				AdcHwTest_Mcu() {};
				virtual ~AdcHwTest_Mcu() {};
				void T01_BasicExampleInternalReference()
				{
					adc.Init(); // Init adc module

					float voltageCh_12_V = adc.GetVoltage_V(Alx_Ch_12); // Get voltage on ch12
					float voltageCh_13_V = adc.GetVoltage_V(Alx_Ch_13); // Get voltage on ch13
					float voltageCh_McuStm32_Vref = adc.GetVoltage_V(Alx_Ch_McuStm32_Vref); // Get voltage of Vref, with the help of VrefInt STM32 specific

					adc.DeInit(); // DeInit adc module
				}
			public:
				// Common Tick, Clk and Trace objects init, not part of example
				AlxTick::Tick tick = { &alxTick };
				AlxClk::Clk clk = { &alxClk, AlxClk_Config_McuStm32F4_Sysclk_180MHz_Pclk1Apb1_45MHz_Pclk2Apb2_90MHz_Hsi_16MHz };
				AlxTrace::Trace trace = { &alxTrace, GPIOA, GPIO_PIN_9, GPIO_AF7_USART1, USART1, AlxGlobal_BaudRate_115200 };
			public:
				AlxIoPin::IoPin ai_PC2 = { GPIOC, GPIO_PIN_2, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, ALX_NULL, ALX_NULL }; // IoPins should be configured in analog mode
				AlxIoPin::IoPin ai_PC3 = { GPIOC, GPIO_PIN_3, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, ALX_NULL, ALX_NULL };
				AlxIoPin::IIoPin* adcIoPinArr[2] = // This array of pointers to IoPins used by adc module
				{
					&ai_PC2, // It is recommended to allignd ioPins Array to channel array.. so that it is easier to se on which pin is which channel
					&ai_PC3
				};
				Alx_Ch adcChArr[3] = // This array of channels used by adc module
				{
					Alx_Ch_12, // Channels must be from low number to high number.. channel number must also match STM32 channel number
					Alx_Ch_13,
					Alx_Ch_McuStm32_Vref // There can also be some internal channels used in STM32, so check which number they are in sequence
				};
				Alx::AlxAdc::AdcMcu adc =
				{
					ADC1,
					adcIoPinArr, // Here is pointer to IoPin array
					ALX_ARR_LEN(adcIoPinArr), // Here is IoPin array length, converted with ALX_ARR_LEN macro
					adcChArr, // Here is pointer to channel array
					ALX_ARR_LEN(adcChArr), // Here is channel array length, converted with ALX_ARR_LEN macro
					&clk, // Pointer to clock module, to get & check clokc info
					AlxAdcMcu_Clk_McuStm32F4_AdcClk_22MHz5_Pclk2Apb2_90MHz, // Here must be correct PCLK2/APB2 that is in system
					ADC_SAMPLETIME_480CYCLES, // sample time for one channel to get sample
					true, // If internal reference will be used for ADC then this must be true
					ALX_NULL // since internal reference will be used, this is don't care.. if we would have precise external reference we will write its value here
				};
		};
		#endif
	}
}

#endif // ALX_ADC_HW_TEST_HPP
