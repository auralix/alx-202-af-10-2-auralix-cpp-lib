/**
  ******************************************************************************
  * @file		alxI2s.hpp
  * @brief		Auralix C++ Library - ALX I2S Module
  * @copyright	Copyright (C) 2020-2022 Auralix d.o.o. All rights reserved.
  *
  * @section License
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is part of Auralix C Library.
  *
  * Auralix C Library is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation, either version 3
  * of the License, or (at your option) any later version.
  *
  * Auralix C Library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Auralix C Library. If not, see <https://www.gnu.org/licenses/>.
  ******************************************************************************
  **/

//******************************************************************************
// Include Guard
//******************************************************************************
#ifndef ALX_I2S_HPP
#define ALX_I2S_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxI2s.h"
#include "alxClk.hpp"
#include "alxIoPin.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxI2s
	{
		//******************************************************************************
		// Class - II2s
		//******************************************************************************
		class II2s
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				II2s() {}
				virtual ~II2s() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual void Foreground_Handle(void) = 0;
				virtual ::AlxI2s* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - AI2s
		//******************************************************************************
		class AI2s : public II2s
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AI2s() {}
				virtual ~AI2s() {}
				Alx_Status Init(void) override
				{
					return AlxI2s_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxI2s_DeInit(&me);
				}
				void Foreground_Handle(void) override
				{
					return AlxI2s_Foreground_Handle(&me);
				}
				::AlxI2s* GetCStructPtr(void) override
				{
					return &me;
				}

			//protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxI2s me = {};
		};


		//******************************************************************************
		// Class - I2s
		//******************************************************************************
		#if defined(ALX_STM32F4)
		class I2s : public AI2s
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
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
				}
				virtual ~I2s() {}
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_I2S_HPP
