/**
  ******************************************************************************
  * @file alxMemRaw.hpp
  * @brief Auralix C++ Library - ALX Mem Raw Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_MEM_RAW_HPP
#define ALX_MEM_RAW_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxMemRaw.h>
//#include <typeinfo>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxMemRaw
	{
		class IMemRaw
		{
			public:
				IMemRaw() {};
				virtual ~IMemRaw() {};
				virtual Alx_Status		MemRaw_Init(void) =	0;
				virtual Alx_Status		MemRaw_DeInit(void) = 0;
				virtual Alx_Status		MemRaw_Read(uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t timeout_ms) = 0;
				virtual Alx_Status		MemRaw_Write(uint32_t addr, uint8_t* data, uint32_t len, bool checkWithReadEnable, uint8_t numOfTries, uint16_t timeout_ms) = 0;
				virtual::AlxMemRaw*		GetCStructPtr(void) = 0;
		};
		//template<typename T>
		class MemRaw final : public IMemRaw
		{
			public:
				//******************************************************************************
				// Public Functions
				//******************************************************************************
				MemRaw() {	AlxMemRaw_Ctor(&me); };
				virtual			~MemRaw() {};
				Alx_Status		MemRaw_Init(void) override																													{ return AlxMemRaw_Init(&me); }
				Alx_Status		MemRaw_DeInit(void) override																												{ return AlxMemRaw_DeInit(&me); }
				Alx_Status		MemRaw_Read(uint32_t addr, uint8_t* data, uint32_t len, uint8_t numOfTries, uint16_t timeout_ms) override									{ return AlxMemRaw_Read(&me, addr, data, len, numOfTries, timeout_ms); }
				Alx_Status		MemRaw_Write(uint32_t addr, uint8_t* data, uint32_t len, bool checkWithReadEnable, uint8_t numOfTries, uint16_t timeout_ms) override		{ return AlxMemRaw_Write(&me, addr, data, len, checkWithReadEnable, numOfTries, timeout_ms); }
				::AlxMemRaw*	GetCStructPtr(void) override																												{ return &me; }
			protected:
				//******************************************************************************
				// Protected Variables
				//******************************************************************************
				::AlxMemRaw me = {};
		};
	}
}

#endif // ALX_MEM_RAW_HPP
