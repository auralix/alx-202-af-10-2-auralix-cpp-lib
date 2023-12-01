/**
  ******************************************************************************
  * @file		alxRtc.hpp
  * @brief		Auralix C++ Library - ALX RTC Module
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
#ifndef ALX_RTC_HPP
#define ALX_RTC_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxRtc.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxRtc
	{
		//******************************************************************************
		// Class - IRtc
		//******************************************************************************
		class IRtc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IRtc() {}
				virtual ~IRtc() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status SetDateTime(AlxRtc_DateTime dateTime) = 0;
				virtual Alx_Status GetDateTime(AlxRtc_DateTime* dateTime) = 0;
				virtual AlxRtc_DateTime GetDateTime(void) = 0;
				virtual bool IsDateTimeConfigured(void) = 0;
				virtual Alx_Status SetUnixTime_ns(uint64_t unixTime_ns) = 0;
				virtual Alx_Status SetUnixTime_us(uint64_t unixTime_us) = 0;
				virtual Alx_Status SetUnixTime_ms(uint64_t unixTime_ms) = 0;
				virtual Alx_Status SetUnixTime_sec(uint64_t unixTime_sec) = 0;
				virtual Alx_Status GetUnixTime_ns(uint64_t* unixTime_ns) = 0;
				virtual Alx_Status GetUnixTime_us(uint64_t* unixTime_us) = 0;
				virtual Alx_Status GetUnixTime_ms(uint64_t* unixTime_ms) = 0;
				virtual Alx_Status GetUnixTime_sec(uint64_t* unixTime_sec) = 0;
				virtual uint64_t GetUnixTime_ns(void) = 0;
				virtual uint64_t GetUnixTime_us(void) = 0;
				virtual uint64_t GetUnixTime_ms(void) = 0;
				virtual uint64_t GetUnixTime_sec(void) = 0;
				virtual ::AlxRtc* GetCStructPtr(void) = 0;
				virtual Alx_Status TuneTime_ns(int64_t tuneTime_ns) = 0;
				virtual Alx_Status TuneTime_us(int64_t tuneTime_ns) = 0;
				virtual Alx_Status TuneTime_ms(int64_t tuneTime_ns) = 0;
		};


		//******************************************************************************
		// Class - ARtc
		//******************************************************************************
		class ARtc : public IRtc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ARtc() {}
				virtual ~ARtc() {}
				Alx_Status Init(void) override
				{
					return AlxRtc_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxRtc_DeInit(&me);
				}
				Alx_Status SetDateTime(AlxRtc_DateTime dateTime) override
				{
					return AlxRtc_SetDateTime(&me, dateTime);
				}
				Alx_Status GetDateTime(AlxRtc_DateTime* dateTime) override
				{
					return AlxRtc_GetDateTimeWithStatus(&me, dateTime);
				}
				AlxRtc_DateTime GetDateTime(void) override
				{
					return AlxRtc_GetDateTime(&me);
				}
				bool IsDateTimeConfigured(void) override
				{
					return AlxRtc_IsDateTimeConfigured(&me);
				}
				Alx_Status SetUnixTime_ns(uint64_t unixTime_ns) override
				{
					return AlxRtc_SetUnixTime_ns(&me, unixTime_ns);
				}
				Alx_Status SetUnixTime_us(uint64_t unixTime_us) override
				{
					return AlxRtc_SetUnixTime_us(&me, unixTime_us);
				}
				Alx_Status SetUnixTime_ms(uint64_t unixTime_ms) override
				{
					return AlxRtc_SetUnixTime_ms(&me, unixTime_ms);
				}
				Alx_Status SetUnixTime_sec(uint64_t unixTime_sec) override
				{
					return AlxRtc_SetUnixTime_sec(&me, unixTime_sec);
				}
				Alx_Status GetUnixTime_ns(uint64_t* unixTime_ns) override
				{
					return AlxRtc_GetUnixTimeWithStatus_ns(&me, unixTime_ns);
				}
				Alx_Status GetUnixTime_us(uint64_t* unixTime_us) override
				{
					return AlxRtc_GetUnixTimeWithStatus_us(&me, unixTime_us);
				}
				Alx_Status GetUnixTime_ms(uint64_t* unixTime_ms) override
				{
					return AlxRtc_GetUnixTimeWithStatus_ms(&me, unixTime_ms);
				}
				Alx_Status GetUnixTime_sec(uint64_t* unixTime_sec) override
				{
					return AlxRtc_GetUnixTimeWithStatus_sec(&me, unixTime_sec);
				}
				uint64_t GetUnixTime_ns(void) override
				{
					return AlxRtc_GetUnixTime_ns(&me);
				}
				uint64_t GetUnixTime_us(void) override
				{
					return AlxRtc_GetUnixTime_us(&me);
				}
				uint64_t GetUnixTime_ms(void) override
				{
					return AlxRtc_GetUnixTime_ms(&me);
				}
				uint64_t GetUnixTime_sec(void) override
				{
					return AlxRtc_GetUnixTime_sec(&me);
				}
				::AlxRtc* GetCStructPtr(void) override
				{
					return &me;
				}
				Alx_Status TuneTime_ns(int64_t tuneTime_ns) override
				{
					return AlxRtc_TuneTime_ns(&me, tuneTime_ns);
				}
				Alx_Status TuneTime_us(int64_t tuneTime_us) override
				{
					return AlxRtc_TuneTime_us(&me, tuneTime_us);
				}
				Alx_Status TuneTime_ms(int64_t tuneTime_ms) override
				{
					return AlxRtc_TuneTime_ms(&me, tuneTime_ms);
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxRtc me = {};
		};


		//******************************************************************************
		// Class - Rtc
		//******************************************************************************
		#if defined(ALX_STM32F4)
		class Rtc : public ARtc
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Rtc
				(
					AlxRtc_Clk rtcClk,
					AlxRtc_LseDrive lseDrive
				)
				{
					AlxRtc_Ctor
					(
						&me,
						rtcClk,
						lseDrive
					);
				}
				virtual ~Rtc() {}
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_RTC_HPP
