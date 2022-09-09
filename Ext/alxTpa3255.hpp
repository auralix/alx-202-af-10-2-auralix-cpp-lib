/**
  ******************************************************************************
  * @file		alxTpa3255.hpp
  * @brief		Auralix C++ Library - ALX Speaker Amplifier TPA3255 Module
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
#ifndef ALX_TPA3255_HPP
#define ALX_TPA3255_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxTpa3255.h"
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
	namespace AlxTpa3255
	{
		//******************************************************************************
		// Class - ITpa3255
		//******************************************************************************
		class ITpa3255
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ITpa3255() {}
				virtual ~ITpa3255() {}
				virtual void Init() = 0;
				virtual void DeInit() = 0;
				virtual void Handle() = 0;
				virtual void Enable() = 0;
				virtual void Disable() = 0;
				virtual bool IsErrAsserted() = 0;
				virtual bool IsWarningAsserted() = 0;
				virtual bool WasErrAsserted() = 0;
				virtual bool WasWarningAsserted() = 0;
				virtual void ClearWasErrAsserted() = 0;
				virtual void ClearWasWarningAsserted() = 0;
		};


		//******************************************************************************
		// Class - Tpa3255
		//******************************************************************************
		class Tpa3255 final : public ITpa3255
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Tpa3255
				(
					Alx::AlxIoPin::IIoPin* di_nRESET,
					Alx::AlxIoPin::IIoPin* do_nFAULT,
					Alx::AlxIoPin::IIoPin* do_nCLIP_OTW,
					float waitTime_ReEnable_ms
				)
				{
					AlxTpa3255_Ctor
					(
						&me,
						di_nRESET->GetCStructPtr(),
						do_nFAULT->GetCStructPtr(),
						do_nCLIP_OTW->GetCStructPtr(),
						waitTime_ReEnable_ms
					);
				}
				virtual ~Tpa3255() {}
				void Init() override
				{
					AlxTpa3255_Init(&me);
				}
				void DeInit() override
				{
					AlxTpa3255_DeInit(&me);
				}
				void Handle() override
				{
					AlxTpa3255_Handle(&me);
				}
				void Enable() override
				{
					AlxTpa3255_Enable(&me);
				}
				void Disable() override
				{
					AlxTpa3255_Disable(&me);
				}
				bool IsErrAsserted() override
				{
					return AlxTpa3255_IsErrAsserted(&me);
				}
				bool IsWarningAsserted() override
				{
					return AlxTpa3255_IsWarningAsserted(&me);
				}
				bool WasErrAsserted() override
				{
					return AlxTpa3255_WasErrAsserted(&me);
				}
				bool WasWarningAsserted() override
				{
					return AlxTpa3255_WasWarningAsserted(&me);
				}
				void ClearWasErrAsserted() override
				{
					AlxTpa3255_ClearWasErrAsserted(&me);
				}
				void ClearWasWarningAsserted() override
				{
					AlxTpa3255_ClearWasWarningAsserted(&me);
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxTpa3255 me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_TPA3255_HPP
