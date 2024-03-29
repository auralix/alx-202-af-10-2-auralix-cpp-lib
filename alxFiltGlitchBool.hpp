﻿/**
  ******************************************************************************
  * @file		alxFiltGlitchBool.hpp
  * @brief		Auralix C++ Library - ALX Fliter Glitch Bool Module
  * @copyright	Copyright (C) Auralix d.o.o. All rights reserved.
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
#ifndef ALX_FILT_GLITCH_BOOL_HPP
#define ALX_FILT_GLITCH_BOOL_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxFiltGlitchBool.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFiltGlitchBool
	{
		//******************************************************************************
		// Class - IFiltGlitchBool
		//******************************************************************************
		class IFiltGlitchBool
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IFiltGlitchBool() {}
				virtual ~IFiltGlitchBool() {}
				virtual bool Process(bool in) = 0;
		};


		//******************************************************************************
		// Class - FiltGlitchBool
		//******************************************************************************
		class FiltGlitchBool : public IFiltGlitchBool
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				FiltGlitchBool
				(
					bool valFilteredInitial,
					float stableTrueTime_ms,
					float stableFalseTime_ms
				)
				{
					AlxFiltGlitchBool_Ctor
					(
						&me,
						valFilteredInitial,
						stableTrueTime_ms,
						stableFalseTime_ms
					);
				}
				virtual ~FiltGlitchBool() {}
				bool Process(bool in) override
				{
					return AlxFiltGlitchBool_Process(&me, in);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxFiltGlitchBool me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_FILT_GLITCH_BOOL_HPP
