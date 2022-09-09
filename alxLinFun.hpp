/**
  ******************************************************************************
  * @file		alxLinFun.hpp
  * @brief		Auralix C++ Library - ALX Linear Interpolation Module
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
#ifndef ALX_LIN_FUN_HPP
#define ALX_LIN_FUN_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxLinFun.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxLinFun
	{
		//******************************************************************************
		// Class - ILinFun
		//******************************************************************************
		class ILinFun
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ILinFun() {}
				virtual ~ILinFun() {}
				virtual Alx_Status GetY(float x, float* y) = 0;
				virtual Alx_Status GetX(float y, float* x) = 0;
				virtual float GetY(float x) = 0;
				virtual float GetX(float y) = 0;
		};


		//******************************************************************************
		// Class - LinFun
		//******************************************************************************
		class LinFun final : public ILinFun
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				LinFun
				(
					float point1_x,
					float point1_y,
					float point2_x,
					float point2_y,
					float min,
					float max,
					bool isLimitOnX
				)
				{
					AlxLinFun_Ctor
					(
						&me,
						point1_x,
						point1_y,
						point2_x,
						point2_y,
						min,
						max,
						isLimitOnX
					);
				}
				virtual ~LinFun() {}
				Alx_Status GetY(float x, float* y) override
				{
					return AlxLinFun_GetY_WithStatus(&me, x, y);
				}
				Alx_Status GetX(float y, float* x) override
				{
					return AlxLinFun_GetX_WithStatus(&me, y, x);
				}
				float GetY(float x) override
				{
					return AlxLinFun_GetY(&me, x);
				}
				float GetX(float y) override
				{
					return AlxLinFun_GetX(&me, y);
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxLinFun me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_LIN_FUN_HPP
