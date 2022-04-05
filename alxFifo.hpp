/**
  ******************************************************************************
  * @file alxFifo.hpp
  * @brief Auralix C++ Library - ALX FIFO Module
  * @version $LastChangedRevision: 4403 $
  * @date $LastChangedDate: 2021-03-16 23:23:43 +0100 (Tue, 16 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_FIFO_HPP
#define ALX_FIFO_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxFifo.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFifo
	{
		class IFifo
		{
			public:
				IFifo() {};
				virtual ~IFifo() {};
				virtual void Flush(void) = 0;
				virtual ::Alx_Status Read(uint8_t* data, uint32_t len = 1) = 0;
				virtual ::Alx_Status ReadStrUntil(char* str, const char* delim, uint32_t maxLen, uint32_t *numRead = nullptr) = 0;
				virtual ::Alx_Status Write(uint8_t data) = 0;
				virtual ::Alx_Status Write(const uint8_t* data, uint32_t len) = 0;
				virtual ::Alx_Status WriteStr(const char* str) = 0;
				virtual uint32_t GetNumOfEntries(void) = 0;
				virtual uint8_t* GetBuffPtr(void) = 0;
		};

		template <uint32_t buffLen>
		class Fifo : public IFifo
		{
			public:
				Fifo()
				{
					AlxFifo_Ctor(&me, buff, buffLen);
				};
				Fifo(uint8_t* buffCLib, uint32_t buffLenCLib)
				{
					ALX_FIFO_ASSERT(buffLen == 1);	// TV: If we want to use C lib sytle Ctor, then template argument buffLen must be 1
					
					AlxFifo_Ctor(&me, buffCLib, buffLenCLib);
				};
				virtual ~Fifo() {};
				void Flush(void) override																						{ AlxFifo_Flush(&me); };
				::Alx_Status Read(uint8_t* data, uint32_t len = 1) override														{ return AlxFifo_Read(&me, data, len); }
				::Alx_Status ReadStrUntil(char* str, const char* delim, uint32_t maxLen, uint32_t *numRead = nullptr) override	{ return AlxFifo_ReadStrUntil(&me, str, delim, maxLen, numRead); }
				::Alx_Status Write(uint8_t data) override																		{ return AlxFifo_Write(&me, data); }
				::Alx_Status Write(const uint8_t* data, uint32_t len) override													{ return AlxFifo_WriteMulti(&me, data, len); }
				::Alx_Status WriteStr(const char* str) override																	{ return AlxFifo_WriteStr(&me, str); }
				uint32_t GetNumOfEntries(void) override																			{ return AlxFifo_GetNumOfEntries(&me); }
				uint8_t* GetBuffPtr(void) override																				{ return (uint8_t*)buff; }
			protected:
				::AlxFifo me = {};
				uint8_t buff[buffLen] = {};
		};

		template <uint32_t buffLen>
		class FifoTest : public Fifo <buffLen>
		{
			public:
				FifoTest() : Fifo <buffLen>() {};
				virtual ~FifoTest() {};
			public:
				uint32_t GetHead(void)		{ return this->me.head; }
				uint32_t GetTail(void)		{ return this->me.tail; }
				bool IsFull(void)			{ return this->me.isFull; }
				bool IsEmpty(void)			{ return this->me.isEmpty; }
				uint32_t GetBuffLen(void)	{ return this->me.buffLen; }
				uint8_t* GetHeadPtr(void)	{ return (uint8_t*)this->buff + this->me.head; }
				uint8_t* GetTailPtr(void)	{ return (uint8_t*)this->buff + this->me.tail; }
		};
	}
}

#endif // ALX_FIFO_HPP
