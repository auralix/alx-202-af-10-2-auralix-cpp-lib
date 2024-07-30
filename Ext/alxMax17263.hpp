/**
  ******************************************************************************
  * @file		alxMax17263.hpp
  * @brief		Auralix C Library - ALX MAX17263 Fuel Gauge
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
#ifndef ALX_MAX17263_HPP
#define ALX_MAX17263_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxMax17263.h"
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
	namespace AlxMax17263
	{
		//******************************************************************************
		// Class - IMax17263
		//******************************************************************************
		class IMax17263
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IMax17263() {}
				virtual ~IMax17263() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Handle(max1726_data_t *data) = 0;
				virtual void GetData(max1726_data_t *data) = 0;
				virtual void GetSerial(char *serial) = 0;
		};


		//******************************************************************************
		// Class - Max17263
		//******************************************************************************
		class Max17263 : public IMax17263
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Max17263
				(
					Alx::AlxI2c::II2c *i2c
				)
				{
					AlxMax17263_Ctor
					(
						&me,
						i2c->GetCStructPtr()
					);
				}
				virtual ~Max17263() {}
				Alx_Status Init(void) override
				{
					return AlxMax17263_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxMax17263_DeInit(&me);
				}
				Alx_Status Handle(max1726_data_t *data) override
				{
					return AlxMax17263_Handle(&me, data);
				}
				void GetSerial(char *serial) override
				{
					strncpy(serial, me.data.serial, 32 + 1);
				}

				void GetData(max1726_data_t *data) override
				{
					data->Cycles = me.data.Cycles;
					data->FulLCAP = me.data.FulLCAP;
					data->RepCAP = me.data.RepCAP;
					data->RepSOC = me.data.RepSOC;
					data->reset_happened = me.data.reset_happened;
					data->TTE = me.data.TTE;
					data->TTF = me.data.TTF;
					data->AvgCurrent = me.data.AvgCurrent;
					data->AvgTA = me.data.AvgTA;
					data->AvgVCell = me.data.AvgVCell;
					memcpy(&data->learned_params, &me.data.learned_params, sizeof(me.data.learned_params));
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxMax17263 me = {};
			public:

				Alx::AlxI2c::II2c *i2c = nullptr;
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_MAX17263_HPP
