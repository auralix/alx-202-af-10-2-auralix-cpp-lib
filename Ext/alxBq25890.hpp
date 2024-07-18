/**
  ******************************************************************************
  * @file		alxBq25890.hpp
  * @brief		Auralix C Library - ALX Battery Charger BQ25890 Module
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
#ifndef ALX_BQ25890_HPP
#define ALX_BQ25890_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxBq25890.h"
#include "alxIoPin.hpp"
#include "alxI2c.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxBq25890
	{
		//******************************************************************************
		// Class - IBq25890
		//******************************************************************************
		class IBq25890
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IBq25890() {}
				virtual ~IBq25890() {}
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
				virtual void Handle(void) = 0;
		};


		//******************************************************************************
		// Class - Bq25890
		//******************************************************************************
		class Bq25890 : public IBq25890
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Bq25890
				(
					Alx::AlxI2c::II2c *i2c,
					uint16_t IINLIM,
					bool JEITA_VSET,
					bool BATFET_DIS
				)
				{
					AlxBq25890_Ctor
					(
						&me,
						i2c->GetCStructPtr(),
						IINLIM,
						JEITA_VSET,
						BATFET_DIS
					);
				}
				virtual ~Bq25890() {}
				virtual void Init(void)
				{
					AlxBq25890_Init(&me);
				}
				virtual void DeInit(void)
				{
					AlxBq25890_DeInit(&me);
				}
				virtual void Handle(void)
				{
					AlxBq25890_Handle(&me);
				}
				virtual void GetRegPtr(AlxBq25890_Reg *reg)
				{
					reg = &me.reg;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxBq25890 me = {};
			public:

				Alx::AlxI2c::II2c *i2c = nullptr;
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_BQ25890_HPP
