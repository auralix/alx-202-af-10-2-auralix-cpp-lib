/**
  ******************************************************************************
  * @file		alxParamItem.hpp
  * @brief		Auralix C++ Library - ALX Parameter Item Module
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
#ifndef ALX_PARAM_ITEM_HPP
#define ALX_PARAM_ITEM_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxParamItem.h"


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
				IParamItem() {}
				virtual ~IParamItem() {}
				virtual const char* GetKey(void) = 0;
				virtual uint32_t GetId(void) = 0;
				virtual uint32_t GetGroupId(void) = 0;
				virtual AlxParamItem_Type GetType(void) = 0;
				virtual void* GetValPtr(void) = 0;
				virtual uint32_t GetValLen(void) = 0;
				virtual void SetValToDef(void) = 0;

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

				virtual Alx_Status GetValUint16_StrFormat(char* val, uint32_t maxLenWithNullTerm) = 0;
				virtual Alx_Status GetValFloat_StrFormat(char* val, uint32_t maxLenWithNullTerm) = 0;
				virtual Alx_Status GetValBool_StrFormat(char* val, uint32_t maxLenWithNullTerm) = 0;

				virtual Alx_Status SetValUint16_StrFormat(char* val) = 0;
				virtual Alx_Status SetValFloat_StrFormat(char* val) = 0;
				virtual Alx_Status SetValBool_StrFormat(char* val) = 0;

				virtual void GetValArr(void* val) = 0;
				virtual void SetValArr(void* val) = 0;
				virtual Alx_Status GetValStr(char* val, uint32_t maxLenWithNullTerm) = 0;
				virtual Alx_Status SetValStr(char* val) = 0;

				virtual ::AlxParamItem* GetCStructPtr(void) = 0;
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

				// Uint8
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint8_t valDef,
					uint8_t valMin,
					uint8_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint8(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Uint16
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint16_t valDef,
					uint16_t valMin,
					uint16_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint16(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Uint32
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint32_t valDef,
					uint32_t valMin,
					uint32_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint32(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Uint64
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					uint64_t valDef,
					uint64_t valMin,
					uint64_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorUint64(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Int8
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int8_t valDef,
					int8_t valMin,
					int8_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorInt8(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Int16
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int16_t valDef,
					int16_t valMin,
					int16_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorInt16(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Int32
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int32_t valDef,
					int32_t valMin,
					int32_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
					)
				{
					AlxParamItem_CtorInt32(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Int64
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					int64_t valDef,
					int64_t valMin,
					int64_t valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorInt64(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Float
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					float valDef,
					float valMin,
					float valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle,
					float* enumArr,
					uint8_t numOfEnums
				)
				{
					AlxParamItem_CtorFloat(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle, enumArr, numOfEnums);
				}
				// Double
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					double valDef,
					double valMin,
					double valMax,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorDouble(&me, name, id, groupId, valDef, valMin, valMax, valOutOfRangeHandle);
				}
				// Bool
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					bool valDef
				)
				{
					AlxParamItem_CtorBool(&me, name, id, groupId, valDef);
				}
				// Arr
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					void* valDefBuff
				)
				{
					//AlxParamItem_CtorArr(&me, name, id, groupId, valDefBuff, arrValBuff, arrValDefBuff, arrBuffLen, AlxParamItem_ValOutOfRangeHandle_Ignore);	// TODO
				}
				// Str
				ParamItem
				(
					const char* name,
					uint32_t id,
					uint32_t groupId,
					const char* valDef,
					AlxParamItem_ValOutOfRangeHandle valOutOfRangeHandle
				)
				{
					AlxParamItem_CtorStr(&me, name, id, groupId, valDef, valOutOfRangeHandle, buff, buffLen);
				}
				virtual ~ParamItem() {}
				const char* GetKey(void) override
				{
					return AlxParamItem_GetKey(&me);
				}
				uint32_t GetId(void) override
				{
					return AlxParamItem_GetId(&me);
				}
				uint32_t GetGroupId(void) override
				{
					return AlxParamItem_GetGroupId(&me);
				}
				AlxParamItem_Type GetType(void) override
				{
					return AlxParamItem_GetType(&me);
				}
				void* GetValPtr(void) override
				{
					return AlxParamItem_GetValPtr(&me);
				}
				uint32_t GetValLen(void) override
				{
					return AlxParamItem_GetValLen(&me);
				}
				void SetValToDef(void) override
				{
					AlxParamItem_SetValToDef(&me);
				}
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
				Alx_Status GetValUint16_StrFormat(char* val, uint32_t maxLenWithNullTerm) override
				{
					return AlxParamItem_GetValUint16_StrFormat(&me, val, maxLenWithNullTerm);
				}
				Alx_Status GetValFloat_StrFormat(char* val, uint32_t maxLenWithNullTerm) override
				{
					return AlxParamItem_GetValFloat_StrFormat(&me, val, maxLenWithNullTerm);
				}
				Alx_Status GetValBool_StrFormat(char* val, uint32_t maxLenWithNullTerm) override
				{
					return AlxParamItem_GetValBool_StrFormat(&me, val, maxLenWithNullTerm);
				}
				Alx_Status SetValUint16_StrFormat(char* val) override
				{
					return AlxParamItem_SetValUint16_StrFormat(&me, val);
				}
				Alx_Status SetValFloat_StrFormat(char* val) override
				{
					return AlxParamItem_SetValFloat_StrFormat(&me, val);
				}
				Alx_Status SetValBool_StrFormat(char* val) override
				{
					return AlxParamItem_SetValBool_StrFormat(&me, val);
				}
				void GetValArr(void* val) override
				{
					AlxParamItem_GetValArr(&me, val);
				}
				void SetValArr(void* val) override
				{
					AlxParamItem_SetValArr(&me, val);
				}
				Alx_Status GetValStr(char* val, uint32_t maxLenWithNullTerm) override
				{
					return AlxParamItem_GetValStr(&me, val, maxLenWithNullTerm);
				}
				Alx_Status SetValStr(char* val) override
				{
					return AlxParamItem_SetValStr(&me, val);
				}
				::AlxParamItem* GetCStructPtr(void) override
				{
					return &me;
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
