/**
  ******************************************************************************
  * @file		alxInterpLin.hpp
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
#ifndef ALX_INTERP_LIN_HPP
#define ALX_INTERP_LIN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxInterpLin.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxInterpLin
	{
		class IInterpLin
		{
			public:
				IInterpLin() {};
				virtual ~IInterpLin() {};
				virtual Alx_Status GetY(float x, float* y) = 0;
				virtual float GetY(float x) = 0;
				virtual::AlxInterpLin* GetCStructPtr(void) = 0;
		};
		class InterpLin final : public IInterpLin
		{
			public:
				InterpLin
				(
					float *xPointArr,
					float *yPointArr,
					uint32_t numOfArrPoints,
					bool isXpointArrRising
				)
				{
					AlxInterpLin_Ctor(&me, xPointArr, yPointArr, numOfArrPoints, isXpointArrRising);
				};
			virtual ~InterpLin() {};
				Alx_Status GetY(float x, float* y) override		{ return AlxInterpLin_GetY_WithStatus	(&me, x, y);}
				float GetY(float x) override					{ return AlxInterpLin_GetY				(&me, x	);	}
				::AlxInterpLin* GetCStructPtr(void) override	{ return &me;	}
			protected:
				::AlxInterpLin me = {};
		};
	}
}

#endif // ALX_FILT_GLITCH_BOOL_HPP
