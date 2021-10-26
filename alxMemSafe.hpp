/**
  ******************************************************************************
  * @file alxMemSafe.hpp
  * @brief Auralix C++ Library - ALX Memory Safe Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_MEM_SAFE_HPP
#define ALX_MEM_SAFE_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxMemSafe.h>
#include <alxCrc.hpp>
#include <alxMemRaw.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxMemSafe
	{
		class IMemSafe
		{
			public:
				IMemSafe() {};
				virtual ~IMemSafe() {};
				virtual ::Alx_Status	Read(uint8_t* data, uint32_t len) = 0;
				virtual ::Alx_Status	Write(uint8_t* data, uint32_t len) = 0;
				virtual bool			IsReadDone(void) = 0;
				virtual bool			IsReadErr(void) = 0;
				virtual bool			IsWriteDone(void) = 0;
				virtual bool			IsWriteErr(void) = 0;
				virtual ::AlxMemSafe*	GetCStructPtr(void) = 0;
		};
		template <uint32_t t_Buff1Len, uint32_t t_Buff2Len>
		class MemSafe : public IMemSafe
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				MemSafe
				(
					AlxMemRaw::MemRaw* memRaw,
					AlxCrc::Crc* crc,
					uint32_t copyAddrA,
					uint32_t copyAddrB,
					uint32_t copyLen,
					bool nonBlockingEnable,
					uint8_t memSafeReadWriteNumOfTries,
					uint8_t memRawReadWriteNumOfTries,
					uint16_t memRawReadWriteTimeout_ms
				)
				{
					AlxMemSafe_Ctor
					(
						&me,
						memRaw->GetCStructPtr(),
						crc->GetCStructPtr(),
						copyAddrA,
						copyAddrB,
						copyLen,
						nonBlockingEnable,
						memSafeReadWriteNumOfTries,
						memRawReadWriteNumOfTries,
						memRawReadWriteTimeout_ms,
						buff1,
						t_Buff1Len,
						buff2,
						t_Buff2Len
					);
				};

				virtual			~MemSafe() {};
				::Alx_Status	Read(uint8_t* data, uint32_t len) override		{ return AlxMemSafe_Read(&me, data, len); }
				::Alx_Status	Write(uint8_t* data, uint32_t len) override		{ return AlxMemSafe_Write(&me, data, len); }
				bool			IsReadDone(void) override						{ return AlxMemSafe_IsReadDone(&me); }
				bool			IsReadErr(void) override						{ return AlxMemSafe_IsReadErr(&me); }
				bool			IsWriteDone(void) override						{ return AlxMemSafe_IsWriteDone(&me); }
				bool			IsWriteErr(void) override						{ return AlxMemSafe_IsWriteErr(&me); }
				::AlxMemSafe*	GetCStructPtr(void) override					{ return &me; }
			protected:
				//******************************************************************************
				// Protected Variables
				//******************************************************************************
				::AlxMemSafe me = {};
				uint8_t buff1[t_Buff1Len] ={};
				uint8_t buff2[t_Buff2Len] ={};
		};
	}
}

#endif // ALX_MEM_SAFE_HPP
