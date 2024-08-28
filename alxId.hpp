/**
  ******************************************************************************
  * @file		alxId.hpp
  * @brief		Auralix C++ Library - ALX ID Module
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
				IId() {}
				virtual ~IId() {}
				virtual void Init(void) = 0;
				virtual void Trace(void) = 0;
				virtual const char* GetFwArtf(void) = 0;
				virtual const char* GetFwName(void) = 0;
				virtual uint8_t GetFwVerMajor(void) = 0;
				virtual uint8_t GetFwVerMinor(void) = 0;
				virtual uint8_t GetFwVerPatch(void) = 0;
				virtual uint32_t GetFwVerDate(void) = 0;
				virtual uint64_t GetFwVer(void) = 0;
				virtual uint32_t GetFwHashShort(void) = 0;
				virtual const char* GetFwVerStr(void) = 0;
				virtual const char* GetFwBinStr(void) = 0;
				virtual const char* GetFwBootArtf(void) = 0;
				virtual const char* GetFwBootName(void) = 0;
				virtual uint8_t GetFwBootVerMajor(void) = 0;
				virtual uint8_t GetFwBootVerMinor(void) = 0;
				virtual uint8_t GetFwBootVerPatch(void) = 0;
				virtual uint32_t GetFwBootVerDate(void) = 0;
				virtual uint64_t GetFwBootVer(void) = 0;
				virtual uint32_t GetFwBootHashShort(void) = 0;
				virtual const char* GetFwBootVerStr(void) = 0;
				virtual const char* GetFwBootBinStr(void) = 0;
				virtual const char* GetHwPcbArtf(void) = 0;
				virtual const char* GetHwPcbName(void) = 0;
				virtual uint8_t GetHwPcbVerMajor(void) = 0;
				virtual uint8_t GetHwPcbVerMinor(void) = 0;
				virtual uint8_t GetHwPcbVerPatch(void) = 0;
				virtual uint32_t GetHwPcbVerDate(void) = 0;
				virtual uint64_t GetHwPcbVer(void) = 0;
				virtual const char* GetHwPcbVerStr(void) = 0;
				virtual const char* GetHwBomArtf(void) = 0;
				virtual const char* GetHwBomName(void) = 0;
				virtual uint8_t GetHwBomVerMajor(void) = 0;
				virtual uint8_t GetHwBomVerMinor(void) = 0;
				virtual uint8_t GetHwBomVerPatch(void) = 0;
				virtual uint32_t GetHwBomVerDate(void) = 0;
				virtual uint64_t GetHwBomVer(void) = 0;
				virtual const char* GetHwBomVerStr(void) = 0;
				virtual uint8_t GetHwId(void) = 0;
				virtual void GetHwMcuUniqueIdUint8(uint8_t* uniqueIdUint8, uint8_t len) = 0;
				virtual const char* GetHwMcuUniqueIdStr(void) = 0;
		};


		//******************************************************************************
		// Class - Id
		//******************************************************************************
		class Id : public IId
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
					bool fwIsBootUsed,
					uint32_t fwBootIdAddr,
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
						fwIsBootUsed,
						fwBootIdAddr,
						hwInstanceKnownArr,
						hwInstanceKnownArrLen,
						hwInstanceHwIdSupportedArr,
						hwInstanceHwIdSupportedArrLen,
						_hwIdIoPinArr,
						hwIdIoPinArrLen,
						hwMcuName
					);
				}
				Id
				(
					const char* fwArtf,
					const char* fwName,
					uint8_t fwVerMajor,
					uint8_t fwVerMinor,
					uint8_t fwVerPatch,
					bool fwIsBuildJobUsed,
					bool fwIsBootUsed,
					uint32_t fwBootIdAddr,
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
						fwIsBootUsed,
						fwBootIdAddr,
						hwInstance,
						hwMcuName
					);
				}
				virtual ~Id() {}
				void Init(void) override
				{
					AlxId_Init(&me);
				}
				void Trace(void) override
				{
					AlxId_Trace(&me);

					ALX_ID_TRACE_FORMAT("\r\n");
					ALX_ID_TRACE_FORMAT("AlxId.hpp - Trace\r\n");

					ALX_ID_TRACE_FORMAT("Language:\r\n");
					ALX_ID_TRACE_FORMAT("- name: C++, ver: %lu\r\n", langCpp.ver);
					ALX_ID_TRACE_FORMAT("- name: %s, ver: %lu\r\n", langCppLib.name, langCppLib.ver);
				}
				const char* GetFwArtf(void) override
				{
					return AlxId_GetFwArtf(&me);
				}
				const char* GetFwName(void) override
				{
					return AlxId_GetFwName(&me);
				}
				uint8_t GetFwVerMajor(void) override
				{
					return AlxId_GetFwVerMajor(&me);
				}
				uint8_t GetFwVerMinor(void) override
				{
					return AlxId_GetFwVerMinor(&me);
				}
				uint8_t GetFwVerPatch(void) override
				{
					return AlxId_GetFwVerPatch(&me);
				}
				uint32_t GetFwVerDate(void) override
				{
					return AlxId_GetFwVerDate(&me);
				}
				uint64_t GetFwVer(void) override
				{
					return AlxId_GetFwVer(&me);
				}
				uint32_t GetFwHashShort(void) override
				{
					return AlxId_GetFwHashShort(&me);
				}
				const char* GetFwVerStr(void) override
				{
					return AlxId_GetFwVerStr(&me);
				}
				const char* GetFwBinStr(void) override
				{
					return AlxId_GetFwBinStr(&me);
				}
				const char* GetFwBootArtf(void) override
				{
					return AlxId_GetFwBootArtf(&me);
				}
				const char* GetFwBootName(void) override
				{
					return AlxId_GetFwBootName(&me);
				}
				uint8_t GetFwBootVerMajor(void) override
				{
					return AlxId_GetFwBootVerMajor(&me);
				}
				uint8_t GetFwBootVerMinor(void) override
				{
					return AlxId_GetFwBootVerMinor(&me);
				}
				uint8_t GetFwBootVerPatch(void) override
				{
					return AlxId_GetFwBootVerPatch(&me);
				}
				uint32_t GetFwBootVerDate(void) override
				{
					return AlxId_GetFwBootVerDate(&me);
				}
				uint64_t GetFwBootVer(void) override
				{
					return AlxId_GetFwBootVer(&me);
				}
				uint32_t GetFwBootHashShort(void) override
				{
					return AlxId_GetFwBootHashShort(&me);
				}
				const char* GetFwBootVerStr(void) override
				{
					return AlxId_GetFwBootVerStr(&me);
				}
				const char* GetFwBootBinStr(void) override
				{
					return AlxId_GetFwBootBinStr(&me);
				}
				const char* GetHwPcbArtf(void) override
				{
					return AlxId_GetHwPcbArtf(&me);
				}
				const char* GetHwPcbName(void) override
				{
					return AlxId_GetHwPcbName(&me);
				}
				uint8_t GetHwPcbVerMajor(void) override
				{
					return AlxId_GetHwPcbVerMajor(&me);
				}
				uint8_t GetHwPcbVerMinor(void) override
				{
					return AlxId_GetHwPcbVerMinor(&me);
				}
				uint8_t GetHwPcbVerPatch(void) override
				{
					return AlxId_GetHwPcbVerPatch(&me);
				}
				uint32_t GetHwPcbVerDate(void) override
				{
					return AlxId_GetHwPcbVerDate(&me);
				}
				uint64_t GetHwPcbVer(void) override
				{
					return AlxId_GetHwPcbVer(&me);
				}
				const char* GetHwPcbVerStr(void) override
				{
					return AlxId_GetHwPcbVerStr(&me);
				}
				const char* GetHwBomArtf(void) override
				{
					return AlxId_GetHwBomArtf(&me);
				}
				const char* GetHwBomName(void) override
				{
					return AlxId_GetHwBomName(&me);
				}
				uint8_t GetHwBomVerMajor(void) override
				{
					return AlxId_GetHwBomVerMajor(&me);
				}
				uint8_t GetHwBomVerMinor(void) override
				{
					return AlxId_GetHwBomVerMinor(&me);
				}
				uint8_t GetHwBomVerPatch(void) override
				{
					return AlxId_GetHwBomVerPatch(&me);
				}
				uint32_t GetHwBomVerDate(void) override
				{
					return AlxId_GetHwBomVerDate(&me);
				}
				uint64_t GetHwBomVer(void) override
				{
					return AlxId_GetHwBomVer(&me);
				}
				const char* GetHwBomVerStr(void) override
				{
					return AlxId_GetHwBomVerStr(&me);
				}
				uint8_t GetHwId(void) override
				{
					return AlxId_GetHwId(&me);
				}
				void GetHwMcuUniqueIdUint8(uint8_t* uniqueIdUint8, uint8_t len) override
				{
					AlxId_GetHwMcuUniqueIdUint8(&me, uniqueIdUint8, len);
				}
				const char* GetHwMcuUniqueIdStr(void) override
				{
					return AlxId_GetHwMcuUniqueIdStr(&me);
				}

			private:
				//------------------------------------------------------------------------------
				// Private Variables
				//------------------------------------------------------------------------------
				::AlxId me = {};
				::AlxIoPin* _hwIdIoPinArr[ALX_ID_HW_ID_IO_PIN_ARR_LEN] = {};
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
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif	// #ifndef ALX_ID_HPP
