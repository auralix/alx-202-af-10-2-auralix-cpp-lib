/**
  ******************************************************************************
  * @file		alxFiltGlitchUint32.hpp
  * @brief		Auralix C++ Library - ALX Fliter Glitch Uint32 Module
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
#ifndef ALX_FILT_GLITCH_UINT32_HPP
#define ALX_FILT_GLITCH_UINT32_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxFiltGlitchUint32.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFiltGlitchUint32
	{
		//******************************************************************************
		// Class - IFiltGlitchUint32
		//******************************************************************************
		class IFiltGlitchUint32
		{
			public:
				IFiltGlitchUint32() {};
				virtual ~IFiltGlitchUint32() {};
				virtual uint32_t Process(uint32_t in) = 0;
		};


		//******************************************************************************
		// Class - FiltGlitchUint32
		//******************************************************************************
		class FiltGlitchUint32 final : public IFiltGlitchUint32
		{
			public:
				FiltGlitchUint32
				(
					uint32_t valInitial,
					float stableTime_ms
				)
				{
					AlxFiltGlitchUint32_Ctor(&me, valInitial, stableTime_ms);
				};
				virtual ~FiltGlitchUint32() {};
				uint32_t Process(uint32_t in) override { return AlxFiltGlitchUint32_Process(&me, in); }
			protected:
				::AlxFiltGlitchUint32 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_FILT_GLITCH_UINT32_HPP
