/**
  ******************************************************************************
  * @file		alxAvg.hpp
  * @brief		Auralix C++ Library - ALX Average Module
  * @copyright	Copyright (C) 2020-2022 Auralix d.o.o. All rights reserved.
  *
  * @section License
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is part of Auralix C++ Library.
  *
  * Auralix C++ Library is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation, either version 3
  * of the License, or (at your option) any later version.
  *
  * Auralix C++ Library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Auralix C++ Library. If not, see <https://www.gnu.org/licenses/>.
  ******************************************************************************
  **/

//******************************************************************************
// Include Guard
//******************************************************************************
#ifndef ALX_AVG_HPP
#define ALX_AVG_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAvg.h"
#include "alxFifo.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAvg
	{
		//******************************************************************************
		// Class - IAvg
		//******************************************************************************
		class IAvg
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAvg() {}
				virtual ~IAvg() {}
				virtual float Process(float in) = 0;
		};


		//******************************************************************************
		// Class - Avg
		//******************************************************************************
		template <uint32_t buffLen>
		class Avg : public IAvg
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Avg
				(
					uint32_t shiftThreshold
				)
				{
					AlxAvg_Ctor
					(
						&me,
						buff,
						buffLen,
						shiftThreshold
					);
				}
				virtual ~Avg() {}
				float Process(float in) override
				{
					return AlxAvg_Process(&me, in);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxAvg me = {};
				float buff[buffLen] = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_AVG_HPP
