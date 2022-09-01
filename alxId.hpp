/**
  ******************************************************************************
  * @file		alxId.hpp
  * @brief		Auralix C++ Library - ALX ID Module
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
#ifndef ALX_ID_HPP
#define ALX_ID_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxId.h"
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
	namespace AlxId
	{
		//******************************************************************************
		// Class - IId
		//******************************************************************************
		class IId
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IId() {};
				virtual ~IId() {};
				virtual void Init(void) = 0;
				virtual void Trace(void) = 0;
				virtual uint8_t GetHwId(void) = 0;
				virtual const char* GetUniqueIdStr(void) = 0;
				virtual uint32_t GetFwAppVerDate(void) = 0;
				virtual const char* GetFwAppVerStr(void) = 0;
		};


		//******************************************************************************
		// Class - Id
		//******************************************************************************
		class Id final : public IId
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				Id
				(
					const char* fwArtf,
					const char* fwName,
					uint8_t fwVerMajor,
					uint8_t fwVerMinor,
					uint8_t fwVerPatch,
					bool fwIsBuildJobUsed,
					bool fwIsBootloader,
					AlxId_HwInstance* hwInstanceKnownArr,
					uint8_t hwInstanceKnownArrLen,
					uint8_t* hwInstanceHwIdSupportedArr,
					uint8_t hwInstanceHwIdSupportedArrLen,
					AlxIoPin::IIoPin** hwIdIoPinArr,
					uint8_t hwIdIoPinArrLen,
					const char* hwMcuName
				)
				{
					for (uint32_t i = 0; i < hwIdIoPinArrLen; i++)
					{
						AlxIoPin::IIoPin* temp = *(hwIdIoPinArr + i);
						_hwIdIoPinArr[i] = temp->GetCStructPtr();
					}

					AlxId_Ctor
					(
						&me,
						fwArtf,
						fwName,
						fwVerMajor,
						fwVerMinor,
						fwVerPatch,
						fwIsBuildJobUsed,
						fwIsBootloader,
						hwInstanceKnownArr,
						hwInstanceKnownArrLen,
						hwInstanceHwIdSupportedArr,
						hwInstanceHwIdSupportedArrLen,
						_hwIdIoPinArr,
						hwIdIoPinArrLen,
						hwMcuName
					);
				};
				Id
				(
					const char* fwArtf,
					const char* fwName,
					uint8_t fwVerMajor,
					uint8_t fwVerMinor,
					uint8_t fwVerPatch,
					bool fwIsBuildJobUsed,
					bool fwIsBootloader,
					AlxId_HwInstance hwInstance,
					const char* hwMcuName
				)
				{
					AlxId_Ctor_NoHwId
					(
						&me,
						fwArtf,
						fwName,
						fwVerMajor,
						fwVerMinor,
						fwVerPatch,
						fwIsBuildJobUsed,
						fwIsBootloader,
						hwInstance,
						hwMcuName
					);
				};
				virtual ~Id() {};
				void Init(void) override
				{
					AlxId_Init(&me);
				}
				void Trace(void) override
				{
					AlxId_Trace(&me);

					ALX_ID_TRACE_FORMAT("\r\n");
					ALX_ID_TRACE_FORMAT("Auralix C++ Library ALX ID Module Identification:\r\n");
					ALX_ID_TRACE_FORMAT("\r\n");

					ALX_ID_TRACE_FORMAT("Language:\r\n");
					ALX_ID_TRACE_FORMAT("- name: C++, ver: %lu\r\n", langCpp.ver);
					ALX_ID_TRACE_FORMAT("- name: %s, ver: %lu\r\n", langCppLib.name, langCppLib.ver);
					ALX_ID_TRACE_FORMAT("\r\n");
				}
				uint8_t GetHwId(void) override
				{
					return AlxId_GetHwId(&me);
				}
				const char* GetUniqueIdStr(void) override
				{
					return AlxId_GetUniqueIdStr(&me);
				}
				uint32_t GetFwAppVerDate(void) override
				{
					return AlxId_GetFwAppVerDate(&me);
				}
				const char* GetFwAppVerStr(void) override
				{
					return AlxId_GetFwAppVerStr(&me);
				}
			private:
				//------------------------------------------------------------------------------
				// Private Structures
				//------------------------------------------------------------------------------
				struct LangCpp
				{
					#ifdef ALX_GCC
						// Preprocesor
						#if (__cplusplus < ALX_LANG_CPP_VER_MIN_REQUIRED)
							#error
						#endif

						// Parameters - Const
						static constexpr uint32_t ver = __cplusplus;
						static constexpr uint32_t verMinRequired = ALX_LANG_CPP_VER_MIN_REQUIRED;
					#endif
					#ifdef _MSC_VER
						// Preprocesor
						#if (_MSVC_LANG < ALX_LANG_CPP_VER_MIN_REQUIRED)
							#error
						#endif

						// Parameters - Const
						static constexpr uint32_t ver = _MSVC_LANG;
						static constexpr uint32_t verMinRequired = ALX_LANG_CPP_VER_MIN_REQUIRED;
					#endif
				} langCpp;
				struct LangCppLib
				{
					#ifdef ALX_GCC
						// Preprocesor
						#if (__GLIBCXX__ < ALX_LANG_CPP_LIB_VER_MIN_REQUIRED)
							#error
						#endif

						// Parameters - Const
						const char name[ALX_ID_NAME_LEN] = "GNU C++ Standard Library";
						static constexpr uint32_t ver = __GLIBCXX__;
						static constexpr uint32_t verMinRequired = ALX_LANG_CPP_LIB_VER_MIN_REQUIRED;
					#endif
				} langCppLib;
			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxId me = {};
				::AlxIoPin* _hwIdIoPinArr[ALX_ID_HW_ID_IO_PIN_ARR_MAX_LEN] = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_ID_HPP
