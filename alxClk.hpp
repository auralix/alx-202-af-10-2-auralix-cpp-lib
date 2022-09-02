/**
  ******************************************************************************
  * @file		alxClk.hpp
  * @brief		Auralix C++ Library - ALX Clock Module
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
#ifndef ALX_CLK_HPP
#define ALX_CLK_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxClk.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxClk
	{
		//******************************************************************************
		// Class - IClk
		//******************************************************************************
		class IClk
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IClk() {}
				virtual ~IClk() {}
				virtual ::Alx_Status Init(void)					= 0;
				virtual uint32_t GetClk_Hz(::AlxClk_Clk clk)	= 0;
				virtual void Irq_Handle(void)					= 0;
				virtual ::AlxClk* GetCStructPtr(void)			= 0;
		};


		//******************************************************************************
		// Class - Clk
		//******************************************************************************
		#ifndef ALX_GTEST
		class Clk final : public IClk
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Clk
				(
					::AlxClk_Config config
				)
				{
					AlxClk_Ctor(&me, config);
				}
				virtual ~Clk() {}
				::Alx_Status Init(void) override				{ return AlxClk_Init(&me); }
				uint32_t GetClk_Hz(::AlxClk_Clk clk) override	{ return AlxClk_GetClk_Hz(&me, clk); }
				void Irq_Handle(void) override					{ return AlxClk_Irq_Handle(&me); }
				::AlxClk* GetCStructPtr(void) override			{ return &me; }
			private:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxClk me = {};
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_CLK_HPP
