/**
  ******************************************************************************
  * @file alxId.hpp
  * @brief Auralix C++ Library - ALX ID Module
  * @version $LastChangedRevision: 5735 $
  * @date $LastChangedDate: 2021-08-05 01:58:54 +0200 (Thu, 05 Aug 2021) $
  ******************************************************************************
  */

#ifndef ALX_ID_HPP
#define ALX_ID_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxId.h>
#include <alxIoPin.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxId
	{
		class IId
		{
			public:
				IId() {};
				virtual ~IId() {};
				virtual void Init(void) = 0;
				virtual void Trace(void) = 0;
				virtual uint8_t GetHwId(void) = 0;
				virtual const char* GetUniqueIdStr(void) = 0;
				virtual uint32_t GetSwAppVerDate(void) = 0;
				virtual const char* GetSwAppVerStr(void) = 0;
		};
		class Id final : public IId
		{
			public:
				Id
				(
					const char* swArtf,
					const char* swName,
					uint8_t swVerMajor,
					uint8_t swVerMinor,
					uint8_t swVerPatch,
					bool swIsBuildJobUsed,
					bool swIsBootloader,
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
						swArtf,
						swName,
						swVerMajor,
						swVerMinor,
						swVerPatch,
						swIsBuildJobUsed,
						swIsBootloader,
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
					const char* swArtf,
					const char* swName,
					uint8_t swVerMajor,
					uint8_t swVerMinor,
					uint8_t swVerPatch,
					bool swIsBuildJobUsed,
					bool swIsBootloader,
					AlxId_HwInstance hwInstance,
					const char* hwMcuName
				)
				{
					AlxId_Ctor_NoHwId
					(
						&me,
						swArtf,
						swName,
						swVerMajor,
						swVerMinor,
						swVerPatch,
						swIsBuildJobUsed,
						swIsBootloader,
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
				uint32_t GetSwAppVerDate(void) override
				{
					return AlxId_GetSwAppVerDate(&me);
				}
				const char* GetSwAppVerStr(void) override
				{
					return AlxId_GetSwAppVerStr(&me);
				}
			private:
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
				::AlxId me = {};
				::AlxIoPin* _hwIdIoPinArr[ALX_ID_HW_ID_IO_PIN_BUFF_LEN] = {};
		};
	}
}

#endif // ALX_ID_HPP
