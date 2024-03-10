/**
  ******************************************************************************
  * @file		alxParamKvStore.hpp
  * @brief		Auralix C++ Library - ALX Parameter Key-Value Store Module
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
#ifndef ALX_PARAM_KV_STORE_HPP
#define ALX_PARAM_KV_STORE_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxParamKvStore.h"
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
	namespace AlxParamKvStore
	{
		//******************************************************************************
		// Class - IParamKvStore
		//******************************************************************************
		class IParamKvStore
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IParamKvStore() {}
				virtual ~IParamKvStore() {}
				virtual Alx_Status Init(void) = 0;
				virtual Alx_Status DeInit(void) = 0;
				virtual Alx_Status Get(const char* key, void* data, uint32_t lenMax, uint32_t* lenActual) = 0;
				virtual Alx_Status Set(const char* key, void* data, uint32_t len) = 0;
				virtual Alx_Status Remove(const char* key) = 0;
				virtual ::AlxParamKvStore* GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - ParamKvStore
		//******************************************************************************
		class ParamKvStore : public IParamKvStore
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ParamKvStore
				(
					AlxFs::IFs* fs
				)
				{
					AlxParamKvStore_Ctor
					(
						&me,
						fs->GetCStructPtr()
					);
				}
				virtual ~ParamKvStore() {}
				Alx_Status Init(void) override
				{
					return AlxParamKvStore_Init(&me);
				}
				Alx_Status DeInit(void) override
				{
					return AlxParamKvStore_DeInit(&me);
				}
				Alx_Status Get(const char* key, void* data, uint32_t lenMax, uint32_t* lenActual) override
				{
					return AlxParamKvStore_Get(&me, key, data, lenMax, lenActual);
				}
				Alx_Status Set(const char* key, void* data, uint32_t len) override
				{
					return AlxParamKvStore_Set(&me, key, data, len);
				}
				Alx_Status Remove(const char* key) override
				{
					return AlxParamKvStore_Remove(&me, key);
				}
				::AlxParamKvStore* GetCStructPtr(void) override
				{
					return &me;
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxParamKvStore me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PARAM_KV_STORE_HPP
