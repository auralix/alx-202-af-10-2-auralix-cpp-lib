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
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Poll(void) = 0;
				virtual Alx_Status Read(AlxBq25890_Reg *reg) = 0;
				virtual Alx_Status SetShippingMode(void) = 0;
				virtual Alx_Status SetIINLIM(uint8_t current) = 0;
				virtual Alx_Status SetJEITA_VSET(bool value) = 0;
				virtual Alx_Status GetFaults(AlxBq2890_faults_t *faults) = 0;
				virtual Alx_Status GetChargingStatus(uint8_t *status) = 0;


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
					uint8_t IINLIM,
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
				Alx_Status Init(void) override
				{
					return AlxBq25890_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxBq25890_DeInit(&me);
				}
				Alx_Status Poll(void) override
				{
					return AlxBq25890_Poll(&me);
				}
				Alx_Status Read(AlxBq25890_Reg *reg) override
				{
					return AlxBq25890_Read(&me, reg);
				}
				Alx_Status GetFaults(AlxBq2890_faults_t *faults) override
				{
					return AlxBq25890_GetFaults(&me, faults);
				}
				Alx_Status GetChargingStatus(uint8_t *status) override
				{
					return AlxBq25890_GetChargingStatus(&me, status);
				}
				Alx_Status SetShippingMode(void) override
				{
					return AlxBq25890_set_shipping_mode(&me);
				}
				Alx_Status SetJEITA_VSET(bool value) override
				{
					return AlxBq25890_set_JEITA_VSET(&me, value);
				}
				Alx_Status SetIINLIM(uint8_t current) override
				{
					return AlxBq25890_set_IINLIM(&me, current);
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
