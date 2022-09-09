/**
  ******************************************************************************
  * @file		alxParamStore.hpp
  * @brief		Auralix C++ Library - ALX Parameter Store Module
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
#ifndef ALX_PARAM_STORE_HPP
#define ALX_PARAM_STORE_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxParamStore.h"
#include "alxParamGroup.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamStore
	{
		//******************************************************************************
		// Class - IParamStore
		//******************************************************************************
		class IParamStore
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IParamStore() {}
				virtual ~IParamStore() {}
				virtual Alx_Status Init(Alx_Status* status, uint32_t numOfParamGroups) = 0;
				virtual void Handle(void) = 0;
				virtual bool IsErr(void) = 0;
				virtual::AlxParamStore*	GetCStructPtr(void) = 0;
		};


		//******************************************************************************
		// Class - ParamStore
		//******************************************************************************
		template<uint32_t _numOfParamGroups>
		class ParamStore : public IParamStore
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ParamStore
				(
					Alx::AlxParamGroup::IParamGroup** paramGroupArr
				)
				{
					// #1 Create array of pointers for paramGroupArr
					for(uint32_t i = 0 ; i < _numOfParamGroups ; i++)
					{
						// #1.1 Get pointer value from arrays of pointers for object item[i]
						AlxParamGroup::IParamGroup* temp = *(paramGroupArr + i);

						// #1.2 Get C structure pointer from object[i]
						this->paramGroupArr[i] = temp->GetCStructPtr();
					}

					// #2 Ctor
					AlxParamStore_Ctor
					(
						&me,
						this->paramGroupArr,
						_numOfParamGroups
					);
				}
				virtual ~ParamStore() {}
				Alx_Status Init(Alx_Status* status, uint32_t numOfParamGroups) override
				{
					return AlxParamStore_Init(&me, status, numOfParamGroups);
				}
				void Handle(void) override
				{
					AlxParamStore_Handle(&me);
				}
				bool IsErr(void) override
				{
					return AlxParamStore_IsErr(&me);
				}
				::AlxParamStore* GetCStructPtr(void) override
				{
					return &me;
				}

			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxParamGroup* paramGroupArr[_numOfParamGroups] = {};
				::AlxParamStore me = {};

		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PARAM_STORE_HPP
