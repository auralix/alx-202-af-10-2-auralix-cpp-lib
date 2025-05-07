/**
  ******************************************************************************
  * @file		alxFsSafe.hpp
  * @brief		Auralix C++ Library - ALX File System Safe Module
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
#ifndef ALX_FS_SAFE_HPP
#define ALX_FS_SAFE_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxFsSafe.h"
#include "alxFs.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFsSafe
	{
		//******************************************************************************
		// Class - IFsSafe
		//******************************************************************************
		class IFsSafe
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IFsSafe() {}
				virtual ~IFsSafe() {}
				virtual Alx_Status File_Read(const char* path, void* data, uint32_t len) = 0;
				virtual Alx_Status File_Write(const char* path, void* data, uint32_t len) = 0;
				virtual ::AlxFsSafe* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - FsSafe
		//******************************************************************************
		template <uint32_t buffLen>
		class FsSafe : public IFsSafe
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				FsSafe
				(
					AlxFs::IFs* alxFs
				)
				{
					AlxFsSafe_Ctor
					(
						&me,
						alxFs->GetCStructPtr(),
						buffA,
						buffB,
						buffLen
					);
				}
				virtual ~FsSafe() {}
				Alx_Status File_Read(const char* path, void* data, uint32_t len) override
				{
					return AlxFsSafe_File_Read(&me, path, data, len);
				}
				Alx_Status File_Write(const char* path, void* data, uint32_t len) override
				{
					return AlxFsSafe_File_Write(&me, path, data, len);
				}
				::AlxFsSafe* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxFsSafe me = {};
				uint8_t buffA[buffLen] ={};
				uint8_t buffB[buffLen] ={};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_FS_SAFE_HPP
