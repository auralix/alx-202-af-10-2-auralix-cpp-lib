/**
  ******************************************************************************
  * @file		alxBtn.hpp
  * @brief		Auralix C++ Library - ALX Button Module
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
#ifndef ALX_BTN_HPP
#define ALX_BTN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxBtn.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxBtn
	{
		//******************************************************************************
		// Class - IBtn
		//******************************************************************************
		class IBtn
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IBtn() {}
				virtual ~IBtn() {}
				virtual void Handle(bool in) = 0;
				virtual bool IsPressed() = 0;
				virtual bool WasPressed() = 0;
				virtual bool WasReleased() = 0;
				virtual bool IsPressedShort() = 0;
				virtual bool WasPressedShort() = 0;
				virtual bool IsPressedLong() = 0;
				virtual bool WasPressedLong() = 0;
				virtual void ClearWasPressed() = 0;
				virtual void ClearWasReleased() = 0;
				virtual void ClearWasPressedShort() = 0;
				virtual void ClearWasPressedLong() = 0;
		};


		//******************************************************************************
		// Class - Btn
		//******************************************************************************
		class Btn final : public IBtn
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Btn
				(
					bool valInitial,
					float longTime_ms,	// min time of long button press [ms]
					float debounceTime_ms	// time of stable button status to change it's state [ms]
				)
				{
					AlxBtn_Ctor
					(
						&me,
						valInitial,
						longTime_ms,
						debounceTime_ms
					);
				}
				virtual ~Btn() {}
				void Handle(bool in) override
				{
					return AlxBtn_Handle(&me, in);
				}
				bool IsPressed() override
				{
					return AlxBtn_IsPressed(&me);
				}
				bool WasPressed() override
				{
					return AlxBtn_WasPressed(&me);
				}
				bool WasReleased() override
				{
					return AlxBtn_WasReleased(&me);
				}
				bool IsPressedShort() override
				{
					return AlxBtn_IsPressedShort(&me);
				}
				bool WasPressedShort() override
				{
					return AlxBtn_WasPressedShort(&me);
				}
				bool IsPressedLong() override
				{
					return AlxBtn_IsPressedLong(&me);
				}
				bool WasPressedLong() override
				{
					return AlxBtn_WasPressedLong(&me);
				}
				void ClearWasPressed() override
				{
					AlxBtn_ClearWasPressed(&me);
				}
				void ClearWasReleased() override
				{
					AlxBtn_ClearWasReleased(&me);
				}
				void ClearWasPressedShort() override
				{
					AlxBtn_ClearWasPressedShort(&me);
				}
				void ClearWasPressedLong() override
				{
					AlxBtn_ClearWasPressedLong(&me);
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxBtn me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_BTN_HPP
