/**
  ******************************************************************************
  * @file alxOsCriticalSection.hpp
  * @brief Auralix C++ Library - ALX OS Critical Section Module
  * @version $LastChangedRevision: 5745 $
  * @date $LastChangedDate: 2021-08-08 19:52:52 +0200 (Sun, 08 Aug 2021) $
  ******************************************************************************
  */

#ifndef ALX_OS_CRITICAL_SECTION_HPP
#define ALX_OS_CRITICAL_SECTION_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>


//******************************************************************************
// Preprocessor
//******************************************************************************
#define ALX_OS_CRITICAL_SECTION_FILE "alxOsCriticalSection.hpp"

// Assert //
#if defined(_ALX_OS_CRITICAL_SECTION_ASSERT_BKPT) || defined(_ALX_ASSERT_BKPT_ALL)
	#define ALX_OS_CRITICAL_SECTION_ASSERT(expr) ALX_ASSERT_BKPT(ALX_OS_CRITICAL_SECTION_FILE, expr)
#elif defined(_ALX_OS_CRITICAL_SECTION_ASSERT_TRACE) || defined(_ALX_ASSERT_TRACE_ALL)
	#define ALX_OS_CRITICAL_SECTION_ASSERT(expr) ALX_ASSERT_TRACE(ALX_OS_CRITICAL_SECTION_FILE, expr)
#elif defined(_ALX_OS_CRITICAL_SECTION_ASSERT_RST) || defined(_ALX_ASSERT_RST_ALL)
	#define ALX_OS_CRITICAL_SECTION_ASSERT(expr) ALX_ASSERT_RST(ALX_OS_CRITICAL_SECTION_FILE, expr)
#else
	#define ALX_OS_CRITICAL_SECTION_ASSERT(expr) do{} while (false)
#endif

// Trace //
#if defined(_ALX_OS_CRITICAL_SECTION_TRACE) || defined(_ALX_TRACE_ALL)
	#define ALX_OS_CRITICAL_SECTION_TRACE(...) ALX_TRACE_STD(ALX_OS_CRITICAL_SECTION_FILE, __VA_ARGS__)
#else
	#define ALX_OS_CRITICAL_SECTION_TRACE(...) do{} while (false)
#endif


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxOsCriticalSection
	{
		ALX_STATIC_INLINE void Enter(void)
		{
			#ifdef ALX_MBED
			mbed::CriticalSectionLock::enable();
			#endif
		}
		ALX_STATIC_INLINE void Exit(void)
		{
			#ifdef ALX_MBED
			mbed::CriticalSectionLock::disable();
			#endif
		}
	}
}

#endif // ALX_OS_CRITICAL_SECTION_HPP
