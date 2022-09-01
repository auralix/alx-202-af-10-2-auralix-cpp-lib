/**
  ******************************************************************************
  * @file		alxParamGroup.hpp
  * @brief		Auralix C++ Library - ALX Parameter Group Module
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
#ifndef ALX_PARAM_GROUP_HPP
#define ALX_PARAM_GROUP_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxParamGroup.h"
#include "alxParamItem.hpp"
#include "alxMemSafe.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamGroup
	{
		//******************************************************************************
		// Class - IParamGroup
		//******************************************************************************
		class IParamGroup
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IParamGroup() {};
				virtual ~IParamGroup() {};
				virtual Alx_Status Init(void) = 0;
				virtual void Write(void) = 0;
				virtual bool IsWriteDone(void) = 0;
				virtual bool IsWriteErr(void) = 0;
				virtual bool IsValStoredBuffDiff(void) = 0;
				virtual void ValBuffToValToStoreBuff(void) = 0;
				virtual void ValToStoreBuffToValStoredBuff(void) = 0;
				virtual void ParamItemsValToValBuff(void) = 0;
				virtual::AlxParamGroup*	GetCStructPtr(void)	= 0;
		};


		//******************************************************************************
		// Class - ParamGroup
		//******************************************************************************
		template<uint32_t numOfParamItems, uint32_t len>
		class ParamGroup : public IParamGroup
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				ParamGroup
				(
					AlxMemSafe::IMemSafe* memSafe,
					const char* name,
					AlxParamItem::IParamItem** paramItemArr,
					uint8_t initNumOfTries
				)
				{
					// #1 Create array of pointers for paramItemArr
					for(uint32_t i = 0; i < numOfParamItems; i++)
					{
						// #1.1 Get pointer value from arrays of pointers for object item[i]
						AlxParamItem::IParamItem* temp = *(paramItemArr + i);

						// #1.2 Get C structure pointer from object[i]
						this->paramItemArr[i] = temp->GetCStructPtr();
					}

					// #2 Ctor
					AlxParamGroup_Ctor
					(
						&me,
						memSafe->GetCStructPtr(),
						name,
						len,
						valBuff,
						valStoredBuff,
						valToStoreBuff,
						this->paramItemArr,
						numOfParamItems,
						initNumOfTries
					);
				};
				virtual ~ParamGroup() {};
				Alx_Status Init(void) override						{ return AlxParamGroup_Init(&me); }
				void Write(void) override							{ AlxParamGroup_Write(&me); }
				bool IsWriteDone(void) override						{ return AlxParamGroup_IsWriteDone(&me); }
				bool IsWriteErr(void) override						{ return AlxParamGroup_IsWriteErr(&me); }
				bool IsValStoredBuffDiff(void) override				{ return AlxParamGroup_IsValStoredBuffDiff(&me); }
				void ValBuffToValToStoreBuff(void) override			{ AlxParamGroup_ValBuffToValToStoreBuff(&me); }
				void ValToStoreBuffToValStoredBuff(void) override	{ AlxParamGroup_ValToStoreBuffToValStoredBuff(&me); }
				void ParamItemsValToValBuff(void) override			{ AlxParamGroup_ParamItemsValToValBuff(&me); }
				::AlxParamGroup* GetCStructPtr(void) override		{ return &me; }
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				uint8_t valBuff[len];		// JK: User has to calculate. Safe way: 8bytes * numOfParamItems
				uint8_t valStoredBuff[len];
				uint8_t valToStoreBuff[len];
				::AlxParamItem* paramItemArr[numOfParamItems] = {};
				::AlxParamGroup me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PARAM_GROUP_HPP
