/**
  ******************************************************************************
  * @file		alxOsFlag.hpp
  * @brief		Auralix C++ Library - ALX OS Flag Module
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
#ifndef ALX_OS_FLAG_HPP
#define ALX_OS_FLAG_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Preprocessor
//******************************************************************************
#define ALX_OS_FLAG_FILE "alxOsFlag.hpp"

// Assert //
#if defined(_ALX_OS_FLAG_ASSERT_BKPT) || defined(_ALX_ASSERT_BKPT_ALL)
	#define ALX_OS_FLAG_ASSERT(expr) ALX_ASSERT_BKPT(ALX_OS_FLAG_FILE, expr)
#elif defined(_ALX_OS_FLAG_ASSERT_TRACE) || defined(_ALX_ASSERT_TRACE_ALL)
	#define ALX_OS_FLAG_ASSERT(expr) ALX_ASSERT_TRACE(ALX_OS_FLAG_FILE, expr)
#elif defined(_ALX_OS_FLAG_ASSERT_RST) || defined(_ALX_ASSERT_RST_ALL)
	#define ALX_OS_FLAG_ASSERT(expr) ALX_ASSERT_RST(ALX_OS_FLAG_FILE, expr)
#else
	#define ALX_OS_FLAG_ASSERT(expr) do{} while (false)
#endif

// Trace //
#if defined(_ALX_OS_FLAG_TRACE) || defined(_ALX_TRACE_ALL)
	#define ALX_OS_FLAG_TRACE(...) ALX_TRACE_STD(ALX_OS_FLAG_FILE, __VA_ARGS__)
#else
	#define ALX_OS_FLAG_TRACE(...) do{} while (false)
#endif


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxOsFlag
	{
		//******************************************************************************
		// Class - IOsFlag
		//******************************************************************************
		class IOsFlag
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IOsFlag() {}
				virtual ~IOsFlag() {}
				virtual void Assert(void) = 0;
				virtual void DeAssert(void) = 0;
				virtual bool IsAsserted(void) = 0;
				virtual bool IsDeAsserted(void) = 0;
				virtual void OsWaitUntilDeAsserted(void) = 0;
		};


		//******************************************************************************
		// Class - OsFlag
		//******************************************************************************
		#if defined(ALX_MBED)
		class OsFlag final : public IOsFlag
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				OsFlag(const char* name) : eventFlags(name)
				{
					DeAssert();
				}
				virtual ~OsFlag() {}
				void Assert(void) override
				{
					uint32_t status = eventFlags.clear(0x00000001);	// We have active low logic
					ALX_OS_FLAG_ASSERT(status == 0x00000001);
				}
				void DeAssert(void) override
				{
					uint32_t status = eventFlags.set(0x00000001);	// We have active low logic
					ALX_OS_FLAG_ASSERT(status == 0x00000001);
				}
				bool IsAsserted(void) override
				{
					uint32_t flags = eventFlags.get();

					if (flags == 0x00000000)	// Flag is asserted if low
						return true;
					else
						return false;
				}
				bool IsDeAsserted(void) override
				{
					return !IsAsserted();
				}
				void OsWaitUntilDeAsserted(void) override
				{
					uint32_t status = eventFlags.wait_all(0x00000001, osWaitForever, false);
					ALX_OS_FLAG_ASSERT(status == 0x00000001);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				rtos::EventFlags eventFlags;
		};
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// ALX_OS_FLAG_HPP
