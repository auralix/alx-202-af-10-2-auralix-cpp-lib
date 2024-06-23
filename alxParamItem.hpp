/**
  ******************************************************************************
  * @file		alxParamItem.hpp
  * @brief		Auralix C++ Library - ALX Parameter Item Module
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
#ifndef ALX_PARAM_ITEM_HPP
#define ALX_PARAM_ITEM_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxParamItem.h"
#include "alxParamKvStore.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxParamItem
	{
		//******************************************************************************
		// Class - IParamItem
		//******************************************************************************
		class IParamItem
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------


				//------------------------------------------------------------------------------
				// Constructor
				//------------------------------------------------------------------------------
				IParamItem() {}
				virtual ~IParamItem() {}
				virtual ::AlxParamItem* GetCStructPtr(void) = 0;


				//------------------------------------------------------------------------------
				// General
				//------------------------------------------------------------------------------
				virtual AlxParamItem_DataType GetDataType(void) = 0;
				virtual AlxParamItem_ParamType GetParamType(void) = 0;
				virtual const char* GetKey(void) = 0;
				virtual uint32_t GetId(void) = 0;
				virtual const char* GetGroupKey(void) = 0;
				virtual uint32_t GetGroupId(void) = 0;
				virtual void* GetValPtr(void) = 0;
				virtual uint32_t GetValLen(void) = 0;


				//------------------------------------------------------------------------------
				// Get
				//------------------------------------------------------------------------------
				virtual uint8_t GetValUint8(void) = 0;
				virtual uint16_t GetValUint16(void) = 0;
				virtual uint32_t GetValUint32(void) = 0;
				virtual uint64_t GetValUint64(void) = 0;
				virtual int8_t GetValInt8(void) = 0;
				virtual int16_t GetValInt16(void) = 0;
				virtual int32_t GetValInt32(void) = 0;
				virtual int64_t GetValInt64(void) = 0;
				virtual float GetValFloat(void) = 0;
				virtual double GetValDouble(void) = 0;
				virtual bool GetValBool(void) = 0;
				virtual void GetValArr(void* val) = 0;
				virtual Alx_Status GetValStr(char* val, uint32_t maxLenWithNullTerm) = 0;


				//------------------------------------------------------------------------------
				// Set
				//------------------------------------------------------------------------------
				virtual Alx_Status SetValUint8(uint8_t val) = 0;
				virtual Alx_Status SetValUint16(uint16_t val) = 0;
				virtual Alx_Status SetValUint32(uint32_t val) = 0;
				virtual Alx_Status SetValUint64(uint64_t val) = 0;
				virtual Alx_Status SetValInt8(int8_t val) = 0;
				virtual Alx_Status SetValInt16(int16_t val) = 0;
				virtual Alx_Status SetValInt32(int32_t val) = 0;
				virtual Alx_Status SetValInt64(int64_t val) = 0;
				virtual Alx_Status SetValFloat(float val) = 0;
				virtual Alx_Status SetValDouble(double val) = 0;
				virtual Alx_Status SetValBool(bool val) = 0;
				virtual void SetValArr(void* val) = 0;
				virtual Alx_Status SetValStr(char* val) = 0;


				//------------------------------------------------------------------------------
				// Set Default
				//------------------------------------------------------------------------------
				virtual void SetValToDef(void) = 0;


				//------------------------------------------------------------------------------
				// Get & Set String Format
				//------------------------------------------------------------------------------
				virtual Alx_Status GetVal_StrFormat(char* val, uint32_t maxLenWithNullTerm) = 0;
				virtual Alx_Status SetVal_StrFormat(char* val) = 0;


				//------------------------------------------------------------------------------
				// Load & Store
				//------------------------------------------------------------------------------
				virtual Alx_Status LoadVal(void) = 0;
				virtual Alx_Status StoreVal(void) = 0;
		};


		//******************************************************************************
		// Class - ParamItem
		//******************************************************************************
		template <uint32_t buffLen = 1>
		class ParamItem : public IParamItem
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------

				//------------------------------------------------------------------------------
				// Constructor
				//------------------------------------------------------------------------------

				// Uint8
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					uint8_t valDef,
					uint8_t valMin,
					uint8_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					uint8_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorUint8
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Uint16
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					uint16_t valDef,
					uint16_t valMin,
					uint16_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					uint16_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorUint16
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Uint32
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					uint32_t valDef,
					uint32_t valMin,
					uint32_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					uint32_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorUint32
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Uint64
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					uint64_t valDef,
					uint64_t valMin,
					uint64_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					uint64_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorUint64
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Int8
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					int8_t valDef,
					int8_t valMin,
					int8_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					int8_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorInt8
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Int16
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					int16_t valDef,
					int16_t valMin,
					int16_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					int16_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorInt16
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Int32
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					int32_t valDef,
					int32_t valMin,
					int32_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					int32_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorInt32
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Int64
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					int64_t valDef,
					int64_t valMin,
					int64_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					int64_t* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorInt64
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Float
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					float valDef,
					float valMin,
					float valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					float* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorFloat
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Double
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					double valDef,
					double valMin,
					double valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					double* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorDouble
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valMin,
						valMax,
						valOutOfRangeHandle,
						enumArr,
						numOfEnums
					);
				}
				// Bool
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					bool valDef
				)
				{
					AlxParamItem_CtorBool
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef
					);
				}
				// Arr
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					void* valDef,
					void* valBuff,
					void* valDefBuff,
					uint32_t valBuffLen,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorArr
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valBuff,
						valDefBuff,
						valBuffLen,
						valOutOfRangeHandle
					);
				}
				// Str
				ParamItem
				(
					AlxParamKvStore::IParamKvStore* paramKvStore,
					AlxParamItem_ParamType paramType,
					const char* key,
					uint32_t id,
					const char* groupKey,
					uint32_t groupId,
					const char* valDef,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorStr
					(
						&me,
						paramKvStore->GetCStructPtr(),
						paramType,
						key,
						id,
						groupKey,
						groupId,
						valDef,
						valOutOfRangeHandle,
						buff,
						buffLen
					);
				}
				virtual ~ParamItem() {}
				::AlxParamItem* GetCStructPtr(void) override
				{
					return &me;
				}


				//------------------------------------------------------------------------------
				// General
				//------------------------------------------------------------------------------
				AlxParamItem_DataType GetDataType(void) override
				{
					return AlxParamItem_GetDataType(&me);
				}
				AlxParamItem_ParamType GetParamType(void) override
				{
					return AlxParamItem_GetParamType(&me);
				}
				const char* GetKey(void) override
				{
					return AlxParamItem_GetKey(&me);
				}
				uint32_t GetId(void) override
				{
					return AlxParamItem_GetId(&me);
				}
				const char* GetGroupKey(void) override
				{
					return AlxParamItem_GetGroupKey(&me);
				}
				uint32_t GetGroupId(void) override
				{
					return AlxParamItem_GetGroupId(&me);
				}
				void* GetValPtr(void) override
				{
					return AlxParamItem_GetValPtr(&me);
				}
				uint32_t GetValLen(void) override
				{
					return AlxParamItem_GetValLen(&me);
				}


				//------------------------------------------------------------------------------
				// Get
				//------------------------------------------------------------------------------
				uint8_t GetValUint8(void) override
				{
					return AlxParamItem_GetValUint8(&me);
				}
				uint16_t GetValUint16(void) override
				{
					return AlxParamItem_GetValUint16(&me);
				}
				uint32_t GetValUint32(void) override
				{
					return AlxParamItem_GetValUint32(&me);
				}
				uint64_t GetValUint64(void) override
				{
					return AlxParamItem_GetValUint64(&me);
				}
				int8_t GetValInt8(void) override
				{
					return AlxParamItem_GetValInt8(&me);
				}
				int16_t GetValInt16(void) override
				{
					return AlxParamItem_GetValInt16(&me);
				}
				int32_t GetValInt32(void) override
				{
					return AlxParamItem_GetValInt32(&me);
				}
				int64_t GetValInt64(void) override
				{
					return AlxParamItem_GetValInt64(&me);
				}
				float GetValFloat(void) override
				{
					return AlxParamItem_GetValFloat(&me);
				}
				double GetValDouble(void) override
				{
					return AlxParamItem_GetValDouble(&me);
				}
				bool GetValBool(void) override
				{
					return AlxParamItem_GetValBool(&me);
				}
				void GetValArr(void* val) override
				{
					AlxParamItem_GetValArr(&me, val);
				}
				Alx_Status GetValStr(char* val, uint32_t maxLenWithNullTerm) override
				{
					return AlxParamItem_GetValStr(&me, val, maxLenWithNullTerm);
				}


				//------------------------------------------------------------------------------
				// Set
				//------------------------------------------------------------------------------
				Alx_Status SetValUint8(uint8_t val) override
				{
					return AlxParamItem_SetValUint8(&me, val);
				}
				Alx_Status SetValUint16(uint16_t val) override
				{
					return AlxParamItem_SetValUint16(&me, val);
				}
				Alx_Status SetValUint32(uint32_t val) override
				{
					return AlxParamItem_SetValUint32(&me, val);
				}
				Alx_Status SetValUint64(uint64_t val) override
				{
					return AlxParamItem_SetValUint64(&me, val);
				}
				Alx_Status SetValInt8(int8_t val) override
				{
					return AlxParamItem_SetValInt8(&me, val);
				}
				Alx_Status SetValInt16(int16_t val) override
				{
					return AlxParamItem_SetValInt16(&me, val);
				}
				Alx_Status SetValInt32(int32_t val) override
				{
					return AlxParamItem_SetValInt32(&me, val);
				}
				Alx_Status SetValInt64(int64_t val) override
				{
					return AlxParamItem_SetValInt64(&me, val);
				}
				Alx_Status SetValFloat(float val) override
				{
					return AlxParamItem_SetValFloat(&me, val);
				}
				Alx_Status SetValDouble(double val) override
				{
					return AlxParamItem_SetValDouble(&me, val);
				}
				Alx_Status SetValBool(bool val) override
				{
					return AlxParamItem_SetValBool(&me, val);
				}
				void SetValArr(void* val) override
				{
					AlxParamItem_SetValArr(&me, val);
				}
				Alx_Status SetValStr(char* val) override
				{
					return AlxParamItem_SetValStr(&me, val);
				}


				//------------------------------------------------------------------------------
				// Set Default
				//------------------------------------------------------------------------------
				void SetValToDef(void) override
				{
					AlxParamItem_SetValToDef(&me);
				}


				//------------------------------------------------------------------------------
				// Get & Set String Format
				//------------------------------------------------------------------------------
				Alx_Status GetVal_StrFormat(char* val, uint32_t maxLenWithNullTerm) override
				{
					return AlxParamItem_GetVal_StrFormat(&me, val, maxLenWithNullTerm);
				}
				Alx_Status SetVal_StrFormat(char* val) override
				{
					return AlxParamItem_SetVal_StrFormat(&me, val);
				}


				//------------------------------------------------------------------------------
				// Load & Store
				//------------------------------------------------------------------------------
				Alx_Status LoadVal(void) override
				{
					return AlxParamItem_LoadVal(&me);
				}
				Alx_Status StoreVal(void) override
				{
					return AlxParamItem_StoreVal(&me);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxParamItem me = {};
				uint8_t buff[buffLen] = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_PARAM_ITEM_HPP
