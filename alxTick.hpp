/**
  ******************************************************************************
  * @file alxTick.hpp
  * @brief Auralix C++ Library - ALX Tick Module
  * @version $LastChangedRevision: 5497 $
  * @date $LastChangedDate: 2021-07-01 20:08:07 +0200 (Thu, 01 Jul 2021) $
  ******************************************************************************
  */

#ifndef ALX_TICK_HPP
#define ALX_TICK_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTick.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTick
	{
		class Tick final
		{
			public:
				Tick(volatile ::AlxTick* me) : me(me)
				{
					AlxTick_Ctor(me);
				};
				virtual ~Tick() {};
				uint64_t Get_ns(void) const volatile
				{
					#if defined(ALX_MBED)
						mbed::CriticalSectionLock::enable();
						uint64_t val = AlxTick_Get_ns(me);
						mbed::CriticalSectionLock::disable();
						return val;
					#else
						return AlxTick_Get_ns(me);
					#endif
				}
				uint64_t Get_us(void) const volatile
				{
					#if defined(ALX_MBED)
						mbed::CriticalSectionLock::enable();
						uint64_t val = AlxTick_Get_us(me);
						mbed::CriticalSectionLock::disable();
						return val;
					#else
						return AlxTick_Get_us(me);
					#endif
				}
				uint64_t Get_ms(void) const volatile
				{
					#if defined(ALX_MBED)
						mbed::CriticalSectionLock::enable();
						uint64_t val = AlxTick_Get_ms(me);
						mbed::CriticalSectionLock::disable();
						return val;
					#else
						return AlxTick_Get_ms(me);
					#endif
				}
				uint64_t Get_sec(void) const volatile
				{
					#if defined(ALX_MBED)
						mbed::CriticalSectionLock::enable();
						uint64_t val = AlxTick_Get_sec(me);
						mbed::CriticalSectionLock::disable();
						return val;
					#else
						return AlxTick_Get_sec(me);
					#endif
				}
				uint64_t Get_min(void) const volatile
				{
					#if defined(ALX_MBED)
						mbed::CriticalSectionLock::enable();
						uint64_t val = AlxTick_Get_min(me);
						mbed::CriticalSectionLock::disable();
						return val;
					#else
						return AlxTick_Get_min(me);
					#endif
				}
				uint64_t Get_hr(void) const volatile
				{
					#if defined(ALX_MBED)
						mbed::CriticalSectionLock::enable();
						uint64_t val = AlxTick_Get_hr(me);
						mbed::CriticalSectionLock::disable();
						return val;
					#else
						return AlxTick_Get_hr(me);
					#endif
				}
				void Inc_ns(void) const volatile				{ AlxTick_Inc_ns(me); }
				void Inc_us(void) const volatile				{ AlxTick_Inc_us(me); }
				void Inc_ms(void) const volatile				{ AlxTick_Inc_ms(me); }
				void Inc_sec(void) const volatile				{ AlxTick_Inc_sec(me); }
				void Inc_min(void) const volatile				{ AlxTick_Inc_min(me); }
				void Inc_hr(void) const volatile				{ AlxTick_Inc_hr(me); }
				void Inc_ns(uint64_t ticks_ns) const volatile	{ AlxTick_IncRange_ns(me, ticks_ns); }
				void Inc_us(uint64_t ticks_us) const volatile	{ AlxTick_IncRange_us(me, ticks_us); }
				void Inc_ms(uint64_t ticks_ms) const volatile	{ AlxTick_IncRange_ms(me, ticks_ms); }
				void Inc_sec(uint64_t ticks_sec) const volatile	{ AlxTick_IncRange_sec(me, ticks_sec); }
				void Inc_min(uint64_t ticks_min) const volatile	{ AlxTick_IncRange_min(me, ticks_min); }
				void Inc_hr(uint64_t ticks_hr) const volatile	{ AlxTick_IncRange_hr(me, ticks_hr); }
				void Reset(void) const volatile
				{
					#if defined(ALX_MBED)
						mbed::CriticalSectionLock::enable();
						AlxTick_Reset(me);
						mbed::CriticalSectionLock::disable();
					#else
						AlxTick_Reset(me);
					#endif
				}
			private:
				volatile ::AlxTick* me = nullptr;
		};
	}
}

#endif // ALX_TICK_HPP
