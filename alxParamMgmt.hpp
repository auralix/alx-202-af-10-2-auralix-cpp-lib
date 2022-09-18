/**
  ******************************************************************************
  * @file		alxParamMgmt.hpp
  * @brief		Auralix C++ Library - ALX Parameter Management Module
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
#ifndef ALX_PARAM_MGMT_HPP
#define ALX_PARAM_MGMT_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxParamMgmt.h"
#include "alxParamItem.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamMgmt
	{
		//******************************************************************************
		// Class - IParamMgmt
		//******************************************************************************
		class IParamMgmt
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IParamMgmt() {}
				virtual ~IParamMgmt() {}
				virtual double Get(const char* name) = 0;
				virtual double Get(uint32_t id) = 0;
				virtual Alx_Status Set(const char* name, double val) = 0;
				virtual Alx_Status Set(uint32_t id, double val) = 0;
				virtual void Get(const char* name, char* val, uint32_t len) = 0;
				virtual void Get(uint32_t id, char* val, uint32_t len) = 0;
				virtual Alx_Status Set(const char* name, char* val, uint32_t len) = 0;
				virtual Alx_Status Set(uint32_t id, char* val, uint32_t len) = 0;
				virtual void SeToDef(const char* name) = 0;
				virtual void SeToDef(uint32_t id) = 0;
				virtual void SeToDefGroup(uint32_t groupId) = 0;
				virtual void SeToDefAll(uint32_t groupId) = 0;
		};


		//******************************************************************************
		// Class - ParamMgmt
		//******************************************************************************
		class ParamMgmt : public IParamMgmt
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ParamMgmt() {}
				virtual ~ParamMgmt() {}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PARAM_MGMT_HPP
