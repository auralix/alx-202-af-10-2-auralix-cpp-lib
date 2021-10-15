/**
  ******************************************************************************
  * @file alxDac_HwTest.hpp
  * @brief Auralix C++ Library - ALX DAC Module - Test
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_DAC_HW_TEST_HPP
#define ALX_DAC_HW_TEST_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTick.hpp>
#include <alxClk.hpp>
#include <alxTrace.hpp>
#include <alxIoPin.hpp>
#include <alxDac.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxDacHwTest
	{
		#if defined(ALX_STM32F4)
		class DacHwTest_Mcu
		{
			public:
				DacHwTest_Mcu() {};
				virtual ~DacHwTest_Mcu() {};
				void T01_BasicExampleInternalReference()
				{
					dac.Init(3.305f); // Init dac module & calibrate Vref_mV
					
					dac.SetVoltage_mV(Alx_Ch_1, 2.5f, 3.302f); // Set dac output to 2.5 V, change to Vref = 3.302 V, after measuring it with ADC..
					dac.SetVoltage_mV(Alx_Ch_2, 2.f, 3.302f); // Set dac output to 2 V, change to Vref = 3.302 V, after measuring it with ADC..
					
					dac.DeInit(); // DeInit dac module
				}
			public:
				// Common Tick, Clk and Trace objects init, not part of example
				AlxTick::Tick tick = { &alxTick };
				AlxClk::Clk clk = { &alxClk, AlxClk_Config_McuStm32F4_Sysclk_180MHz_Pclk1Apb1_45MHz_Pclk2Apb2_90MHz_Hsi_16MHz };
				AlxTrace::Trace trace = { &alxTrace, GPIOA, GPIO_PIN_9, GPIO_AF7_USART1, USART1, AlxGlobal_BaudRate_115200 };
			public:
				AlxIoPin::IoPin ao_PA4 = { GPIOA, GPIO_PIN_4, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, ALX_NULL, ALX_NULL }; // IoPins should be configured in analog mode
				AlxIoPin::IoPin ao_PA5 = { GPIOA, GPIO_PIN_5, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, ALX_NULL, ALX_NULL };
				AlxIoPin::IIoPin* dacIoPinArr[2] = // This array of pointers to IoPins used by dac module
				{
					&ao_PA4,  // It is recommended to allignd ioPins Array to channel array.. so that it is easier to se on which pin is which channel
					&ao_PA5
				};
				Alx_Ch dacChArr[2] = // This array of channels used by dac module
				{
					Alx_Ch_1, // Channels must be from low number to high number.. channel number must also match STM32 channel number
					Alx_Ch_2
				};
				uint32_t dacSetVoltageDefaultArr_V[2] = 
				{
					1.2f,
					3.f
				};
				Alx::AlxDac::DacMcu dac =
				{
					DAC1,
					dacIoPinArr, // Here is pointer to IoPin array
					dacChArr, // Here is pointer to channel array
					dacSetVoltageDefaultArr_V,
					ALX_ARR_LEN(dacChArr), // Here is channel array length, converted with ALX_ARR_LEN macro
					true, // If internal reference will be used for DAC then this must be true, this measn before each DAC setting we will measure reference voltage with ADC
					ALX_NULL // since internal reference will be used, this is don't care.. if we would have precise external reference we will write its value here
				};
		};
		#endif
	}
}

#endif // ALX_DAC_HW_TEST_HPP
