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
#ifndef ALX_HYS1_HPP
#define ALX_HYS1_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxHys1.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxHys1
	{
		//******************************************************************************
		// Class - IHys1
		//******************************************************************************
		class IHys1
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IHys1() {}
				virtual ~IHys1() {}
				virtual AlxHys1_St Process(float in) = 0;
		};


		//******************************************************************************
		// Class - Hys1
		//******************************************************************************
		class Hys1 : public IHys1
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Hys1
				(
					float high,
					float low
				)
				{
					AlxHys1_Ctor
					(
						&me,
						high,
						low
					);
				}
				virtual ~Hys1() {}
				AlxHys1_St Process(float in) override
				{
					return AlxHys1_Process(&me, in);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxHys1 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_HYS1_HPP
