/**
  ******************************************************************************
  * @file		bts724g.hpp
  * @brief		Auralix C++ Library - ALX HighSide Switch BTS724G Module
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
#ifndef ALX_BTS724G_HPP
#define ALX_BTS724G_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxBts724g.h"
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
	namespace AlxBts724g
	{
		//******************************************************************************
		// Class - IBts724g
		//******************************************************************************
		class IBts724g
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IBts724g() {}
				virtual ~IBts724g() {}
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
				virtual void Handle(void) = 0;
				virtual void SetOut(void) = 0;
				virtual void ResetOut(void) = 0;
				virtual void WriteOut(bool ) = 0;
				virtual bool IsOpenLoadDetected(void) = 0;
				virtual bool IsOverTempDetected(void) = 0;
				virtual bool WasOpenLoadDetected(void) = 0;
				virtual bool WasOverTempDetected(void) = 0;
		};


		//******************************************************************************
		// Class - Bts724g
		//******************************************************************************
		class Bts724g : public IBts724g
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Bts724g
				(
					Alx::AlxIoPin::IIoPin* do_HS_IN,
					Alx::AlxIoPin::IIoPin* di_HS_ST
				)
				{
					AlxBts724g_Ctor
					(
						&me,
						do_HS_IN->GetCStructPtr(),
						di_HS_ST->GetCStructPtr()
					);
				}
				virtual ~Bts724g() {}
				void Init(void)override
				{
					AlxBts724g_Init(&me);
				}
				void DeInit(void)override
				{
					AlxBts724g_DeInit(&me);
				}
				void Handle(void)override
				{
					AlxBts724g_Handle(&me);
				}
				void SetOut(void)override
				{
					AlxBts724g_SetOut(&me);
				}
				void ResetOut(void)override
				{
					AlxBts724g_ResetOut(&me);
				}
				void WriteOut(bool state)override
				{
					AlxBts724g_WriteOut(&me, state);
				}
				bool IsOpenLoadDetected(void)override
				{
					return AlxBts724g_IsOpenLoadDetected(&me);
				}
				bool IsOverTempDetected(void)override
				{
					return AlxBts724g_IsOverTempDetected(&me);
				}
				bool WasOpenLoadDetected(void)override
				{
					return AlxBts724g_WasOpenLoadDetected(&me);
				}
				bool WasOverTempDetected(void)override
				{
					return AlxBts724g_WasOverTempDetected(&me);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxBts724g me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_BTS724G_HPP
