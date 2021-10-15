/**
  ******************************************************************************
  * @file alxTimSw.h
  * @brief Auralix C++ Library - ALX Timer SW Module
  * @version $LastChangedRevision: 4304 $
  * @date $LastChangedDate: 2021-03-09 21:22:50 +0100 (Tue, 09 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_TIM_SW_HPP
#define ALX_TIM_SW_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTimSw.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTimSw
	{
		class ITimSw
		{
			public:
				ITimSw() {};
				virtual ~ITimSw() {};
				virtual void Start(void) = 0;
				virtual void Stop(void) = 0;
				virtual bool IsRunning(void) = 0;
				virtual uint64_t Get_ns(void) = 0;
				virtual uint64_t Get_us(void) = 0;
				virtual uint64_t Get_ms(void) = 0;
				virtual uint64_t Get_sec(void) = 0;
				virtual uint64_t Get_min(void) = 0;
				virtual uint64_t Get_hr(void) = 0;
				virtual bool IsTimeout_ns(uint64_t timeout_ns) = 0;
				virtual bool IsTimeout_us(uint64_t timeout_us) = 0;
				virtual bool IsTimeout_ms(uint64_t timeout_ms) = 0;
				virtual bool IsTimeout_sec(uint64_t timeout_sec) = 0;
				virtual bool IsTimeout_min(uint64_t timeout_min) = 0;
				virtual bool IsTimeout_hr(uint64_t timeout_hr) = 0;
		};
		class TimSw final : public ITimSw
		{
			public:
				TimSw(bool start = false)
				{
					AlxTimSw_Ctor(&me, start);
				};
				virtual ~TimSw() {};
				void Start(void) override							{ AlxTimSw_Start(&me); }
				void Stop(void) override							{ AlxTimSw_Stop(&me); }
				bool IsRunning (void) override						{ return AlxTimSw_IsRunning(&me); }
				uint64_t Get_ns(void) override						{ return AlxTimSw_Get_ns(&me); }
				uint64_t Get_us(void) override						{ return AlxTimSw_Get_us(&me); }
				uint64_t Get_ms(void) override						{ return AlxTimSw_Get_ms(&me); }
				uint64_t Get_sec(void) override						{ return AlxTimSw_Get_sec(&me); }
				uint64_t Get_min(void) override						{ return AlxTimSw_Get_min(&me); }
				uint64_t Get_hr(void) override						{ return AlxTimSw_Get_hr(&me); }
				bool IsTimeout_ns(uint64_t timeout_ns) override		{ return AlxTimSw_IsTimeout_ns(&me, timeout_ns); }
				bool IsTimeout_us(uint64_t timeout_us) override		{ return AlxTimSw_IsTimeout_us(&me, timeout_us); }
				bool IsTimeout_ms(uint64_t timeout_ms) override		{ return AlxTimSw_IsTimeout_ms(&me, timeout_ms); }
				bool IsTimeout_sec(uint64_t timeout_sec) override	{ return AlxTimSw_IsTimeout_sec(&me, timeout_sec); }
				bool IsTimeout_min(uint64_t timeout_min) override	{ return AlxTimSw_IsTimeout_min(&me, timeout_min); }
				bool IsTimeout_hr(uint64_t timeout_hr) override		{ return AlxTimSw_IsTimeout_hr(&me, timeout_hr); }
			protected:
				::AlxTimSw me = {};
		};
		#if defined (ALX_GTEST)
		class MockTimSw final : public ITimSw
		{
			public:
				MOCK_METHOD(void, Start, (), (override));
				MOCK_METHOD(void, Stop, (), (override));
				MOCK_METHOD(bool, IsRunning, (), (override));
				MOCK_METHOD(uint64_t, Get_ns, (), (override));
				MOCK_METHOD(uint64_t, Get_us, (), (override));
				MOCK_METHOD(uint64_t, Get_ms, (), (override));
				MOCK_METHOD(uint64_t, Get_sec, (), (override));
				MOCK_METHOD(uint64_t, Get_min, (), (override));
				MOCK_METHOD(uint64_t, Get_hr, (), (override));
				MOCK_METHOD(bool, IsTimeout_ns, (uint64_t), (override));
				MOCK_METHOD(bool, IsTimeout_us, (uint64_t), (override));
				MOCK_METHOD(bool, IsTimeout_ms, (uint64_t), (override));
				MOCK_METHOD(bool, IsTimeout_sec, (uint64_t), (override));
				MOCK_METHOD(bool, IsTimeout_min, (uint64_t), (override));
				MOCK_METHOD(bool, IsTimeout_hr, (uint64_t), (override));
		};
		#endif
	}
}

#endif // ALX_TIM_SW_HPP
