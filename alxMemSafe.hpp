/**
  ******************************************************************************
  * @file alxMemSafe.hpp
  * @brief Auralix C++ Library - ALX Mem Safe Module
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
//#include <typeinfo>


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
				virtual Alx_Status		MemSafe_Read(uint8_t* data, uint32_t len) =		0;
				virtual Alx_Status		MemSafe_Write(uint8_t* data, uint32_t len) =	0;
				virtual bool			MemSafe_IsReadDone(void) =						0;
				virtual bool			MemSafe_IsReadErr(void) =						0;
				virtual bool			MemSafe_IsWriteDone(void) =						0;
				virtual bool			MemSafe_IsWriteErr(void) =						0;
				virtual::AlxMemSafe*	GetCStructPtr(void) =							0;
		};
		//template<typename T>
		class MemSafe final : public IMemSafe
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				MemSafe
				(
					AlxMemRaw* memRaw,
					AlxCrc* crc,
					uint32_t copyAddrA,
					uint32_t copyAddrB,
					uint32_t copyLen,
					bool nonBlockingEnable,
					uint8_t memSafeReadWriteNumOfTries,
					uint8_t memRawReadWriteNumOfTries,
					uint16_t memRawReadWriteTimeout_ms,
					uint8_t* buff1,
					uint32_t buff1Len,
					uint8_t* buff2,
					uint32_t buff2Len
				)
				{
					AlxMemSafe_Ctor
					(
						&me,
						memRaw,
						crc,
						copyAddrA,
						copyAddrB,
						copyLen,
						nonBlockingEnable,
						memSafeReadWriteNumOfTries,
						memRawReadWriteNumOfTries,
						memRawReadWriteTimeout_ms,
						buff1,
						buff1Len,
						buff2,
						buff2Len
					);
				};

				virtual			~MemSafe() {};
				Alx_Status		MemSafe_Read(uint8_t* data, uint32_t len) override		{ return AlxMemSafe_Read(&me, data, len); }
				Alx_Status		MemSafe_Write(uint8_t* data, uint32_t len) override		{ return AlxMemSafe_Write(&me, data, len); }
				bool			MemSafe_IsReadDone(void) override						{ return AlxMemSafe_IsReadDone(&me); }
				bool			MemSafe_IsReadErr(void) override						{ return AlxMemSafe_IsReadErr(&me); }
				bool			MemSafe_IsWriteDone(void) override						{ return AlxMemSafe_IsWriteDone(&me); }
				bool			MemSafe_IsWriteErr(void) override						{ return AlxMemSafe_IsWriteErr(&me); }
				::AlxMemSafe*	GetCStructPtr(void) override							{ return &me; }
			protected:
				//******************************************************************************
				// Protected Variables
				//******************************************************************************
				::AlxMemSafe me = {};
		};
	}
}

#endif // ALX_MEM_SAFE_HPP
