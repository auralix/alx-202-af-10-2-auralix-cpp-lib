/**
  ******************************************************************************
  * @file alxI2s.hpp
  * @brief Auralix C++ Library - ALX I2S Module
  * @version $LastChangedRevision: 4584 $
  * @date $LastChangedDate: 2021-04-03 03:11:01 +0200 (Sat, 03 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_I2S_HPP
#define ALX_I2S_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxI2s.h>
#include <alxIoPin.hpp>
#include <alxClk.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxI2s
	{
		class II2s
		{
			public:
				II2s() {};
				virtual ~II2s() {};
				virtual ::Alx_Status Init(void)			= 0;
				virtual ::Alx_Status DeInit(void)		= 0;
				virtual void Foreground_Handle(void)	= 0;
				virtual ::AlxI2s* GetCStructPtr(void)	= 0;
		};
		class AI2s : public II2s
		{
			public:
				AI2s() {};
				virtual ~AI2s() {};
				::Alx_Status Init(void) override		{ return AlxI2s_Init(&me); }
				::Alx_Status DeInit(void) override		{ return AlxI2s_DeInit(&me); }
				void Foreground_Handle(void) override	{ return AlxI2s_Foreground_Handle(&me); }
				::AlxI2s* GetCStructPtr(void) override	{ return &me; }
			//protected:
				::AlxI2s me = {};
		};
		#if defined(ALX_STM32F4)
		class I2s : public AI2s
		{
			public:
				I2s
				(
					SAI_Block_TypeDef* i2s,
					AlxIoPin::IIoPin* do_MCLK,
					AlxIoPin::IIoPin* do_BCLK,
					AlxIoPin::IIoPin* do_LRCLK,
					AlxIoPin::IIoPin* do_SDO,
					AlxIoPin::IIoPin* di_SDI,
					AlxClk::IClk* clk,
					AlxI2s_Clk i2sClk,
					uint32_t audioMode,
					uint32_t protocolDataSize,
					bool isMclkUsed,
					Alx_IrqPriority irqPriority
				)
				{
					if(isMclkUsed)
					{
						AlxI2s_Ctor
						(
							&me,
							i2s,
							do_MCLK->GetCStructPtr(),
							do_BCLK->GetCStructPtr(),
							do_LRCLK->GetCStructPtr(),
							do_SDO->GetCStructPtr(),
							di_SDI->GetCStructPtr(),
							clk->GetCStructPtr(),
							i2sClk,
							audioMode,
							protocolDataSize,
							isMclkUsed,
							irqPriority
						);
					}
					else
					{
						AlxI2s_Ctor
						(
							&me,
							i2s,
							ALX_NULL_PTR,
							do_BCLK->GetCStructPtr(),
							do_LRCLK->GetCStructPtr(),
							do_SDO->GetCStructPtr(),
							di_SDI->GetCStructPtr(),
							clk->GetCStructPtr(),
							i2sClk,
							audioMode,
							protocolDataSize,
							isMclkUsed,
							irqPriority
						);
					}
				};
				virtual ~I2s() {};
		};
		#endif
	}
}

#endif // ALX_I2S_HPP














//				virtual void AlxI2s_Start_Write(uint8_t* data, uint16_t len = 1)	= 0;
//				virtual void AlxI2s_Stop_Write(void)								= 0;
//				virtual void AlxI2s_Foreground_Handle(void)							= 0;

//				void AlxI2s_Start_Write(uint8_t* data, uint16_t len) override		{ ::AlxI2s_Start_Write(&me, data, len); }
//				void AlxI2s_Stop_Write(void) override								{ ::AlxI2s_Stop_Write(&me); }
//				void AlxI2s_Foreground_Handle(void) override						{ ::AlxI2s_Foreground_Handle(&me); }



