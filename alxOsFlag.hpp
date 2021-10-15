/**
  ******************************************************************************
  * @file alxOsFlag.hpp
  * @brief Auralix C++ Library - ALX OS Flag Module
  * @version $LastChangedRevision: 5745 $
  * @date $LastChangedDate: 2021-08-08 19:52:52 +0200 (Sun, 08 Aug 2021) $
  ******************************************************************************
  */

#ifndef ALX_OS_FLAG_HPP
#define ALX_OS_FLAG_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>


//******************************************************************************
// Preprocessor
//******************************************************************************
#define ALX_OS_FLAG_FILE "alxOsFlag.hpp"

// Assert //
#if defined(_ALX_OS_FLAG_ASSERT_BKPT) || defined(_ALX_ASSERT_BKPT_ALL)
	#define ALX_OS_FLAG_ASSERT(expr) ALX_ASSERT_BKPT(ALX_OS_FLAG_FILE, expr)
#elif defined(_ALX_OS_FLAG_ASSERT_TRACE) || defined(_ALX_ASSERT_TRACE_ALL)
	#define ALX_OS_FLAG_ASSERT(expr) ALX_ASSERT_TRACE(ALX_OS_FLAG_FILE, expr)
#elif defined(_ALX_OS_FLAG_ASSERT_RST) || defined(_ALX_ASSERT_RST_ALL)
	#define ALX_OS_FLAG_ASSERT(expr) ALX_ASSERT_RST(ALX_OS_FLAG_FILE, expr)
#else
	#define ALX_OS_FLAG_ASSERT(expr) do{} while (false)
#endif

// Trace //
#if defined(_ALX_OS_FLAG_TRACE) || defined(_ALX_TRACE_ALL)
	#define ALX_OS_FLAG_TRACE(...) ALX_TRACE_STD(ALX_OS_FLAG_FILE, __VA_ARGS__)
#else
	#define ALX_OS_FLAG_TRACE(...) do{} while (false)
#endif


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxOsFlag
	{
		class IOsFlag
		{
			public:
				IOsFlag() {};
				virtual ~IOsFlag() {};
				virtual void Assert(void) = 0;
				virtual void DeAssert(void) = 0;
				virtual bool IsAsserted(void) = 0;
				virtual bool IsDeAsserted(void) = 0;
				virtual void OsWaitUntilDeAsserted(void) = 0;
		};
		#if defined(ALX_MBED)
		class OsFlag final : public IOsFlag
		{
			public:
				OsFlag
				(
					const char* name
				) :
					eventFlags(name)
				{
					DeAssert();
				};
				virtual ~OsFlag() {};
				void Assert(void) override
				{
					uint32_t status = eventFlags.clear(0x00000001);	// We have active low logic
					ALX_OS_FLAG_ASSERT(status == 0x00000001);
				}
				void DeAssert(void) override
				{
					uint32_t status = eventFlags.set(0x00000001);	// We have active low logic
					ALX_OS_FLAG_ASSERT(status == 0x00000001);
				}
				bool IsAsserted(void) override
				{
					uint32_t flags = eventFlags.get();
					
					if (flags == 0x00000000)	// Flag is asserted if low
						return true;
					else
						return false;
				}
				bool IsDeAsserted(void) override
				{
					return !IsAsserted();
				}
				void OsWaitUntilDeAsserted(void) override
				{
					uint32_t status = eventFlags.wait_all(0x00000001, osWaitForever, false);
					ALX_OS_FLAG_ASSERT(status == 0x00000001);
				}
			private:
				rtos::EventFlags eventFlags;
		};
		#endif
	}
}

#endif // ALX_OS_FLAG_HPP
