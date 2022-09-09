/**
  ******************************************************************************
  * @file		alxBq24600.hpp
  * @brief		Auralix C Library - ALX Battery Charger BQ24600 Module
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
#ifndef ALX_BQ24600_HPP
#define ALX_BQ24600_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxBq24600.h"
#include "alxIoPin.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxBq24600
	{
		//******************************************************************************
		// Class - IBq24600
		//******************************************************************************
		class IBq24600
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IBq24600() {}
				virtual ~IBq24600() {}
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
				virtual void Handle(void) = 0;
				virtual void Enable(void) = 0;
				virtual void Disable(void) = 0;
				virtual bool IsBatCharging(void) = 0;
				virtual bool IsBatFull(void) = 0;
				virtual bool IsSleep(void) = 0;
				virtual bool IsErr(void) = 0;
		};


		//******************************************************************************
		// Class - Bq24600
		//******************************************************************************
		class Bq24600 : public IBq24600
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Bq24600
				(
					Alx::AlxIoPin::IIoPin* di_EN,
					Alx::AlxIoPin::IIoPin* do_nPG,
				 	Alx::AlxIoPin::IIoPin* do_STAT
				)
				{
					AlxBq24600_Ctor
					(
						&me,
						di_EN->GetCStructPtr(),
						do_nPG->GetCStructPtr(),
						do_STAT->GetCStructPtr()
					);
				}
				virtual ~Bq24600() {}
				virtual void Init(void)
				{
					AlxBq24600_Init(&me);
				}
				virtual void DeInit(void)
				{
					AlxBq24600_DeInit(&me);
				}
				virtual void Handle(void)
				{
					AlxBq24600_Handle(&me);
				}
				virtual void Enable(void)
				{
					AlxBq24600_Enable(&me);
				}
				virtual void Disable(void)
				{
					AlxBq24600_Disable(&me);
				}
				virtual bool IsBatCharging(void)
				{
					return AlxBq24600_IsBatCharging(&me);
				}
				virtual bool IsBatFull(void)
				{
					return AlxBq24600_IsBatFull(&me);
				}
				virtual bool IsSleep(void)
				{
					return AlxBq24600_IsSleep(&me);
				}
				virtual bool IsErr(void)
				{
					return AlxBq24600_IsErr(&me);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxBq24600 me = {0};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// ALX_BQ24600_HPP
