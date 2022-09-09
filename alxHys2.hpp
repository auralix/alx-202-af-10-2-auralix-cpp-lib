/**
  ******************************************************************************
  * @file		alxHys2.hpp
  * @brief		Auralix C++ Library - ALX Hysteresis Module
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
#ifndef ALX_HYS2_HPP
#define ALX_HYS2_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxHys2.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxHys2
	{
		//******************************************************************************
		// Class - IHys2
		//******************************************************************************
		class IHys2
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IHys2() {}
				virtual ~IHys2() {}
				virtual ::AlxHys2_St Process(float in) = 0;
		};


		//******************************************************************************
		// Class - Hys2
		//******************************************************************************
		class Hys2 final : public IHys2
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Hys2
				(
					float topHigh,
					float topLow,
					float botHigh,
					float botLow
				)
				{
					AlxHys2_Ctor
					(
						&me,
						topHigh,
						topLow,
						botHigh,
						botLow
					);
				}
				virtual ~Hys2() {}
				::AlxHys2_St Process(float in) override
				{
					return AlxHys2_Process(&me, in);
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxHys2 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// ALX_HYS2_HPP
