/**
  ******************************************************************************
  * @file alxTrace.hpp
  * @brief Auralix C++ Library - Trace Module
  * @version $LastChangedRevision: 5968 $
  * @date $LastChangedDate: 2021-09-07 15:15:09 +0200 (Tue, 07 Sep 2021) $
  ******************************************************************************
  */

#ifndef ALX_TRACE_HPP
#define ALX_TRACE_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTrace.h>


//******************************************************************************
// Preprocessor
//******************************************************************************
#define ALX_TRACE_STR_CPP(str) do								{ Alx::AlxTrace::alxTraceCpp.WriteStr(str); } while(false)
#define ALX_TRACE_FORMAT_CPP(...) do							{ Alx::AlxTrace::alxTraceCpp.WriteFormat(__VA_ARGS__); } while(false)
#define ALX_TRACE_STD_CPP(file, ...) do							{ Alx::AlxTrace::alxTraceCpp.WriteStd(file, __LINE__, __func__, __VA_ARGS__); } while(false)
#define ALX_TRACE_SM_CPP(smLevel, smName, stName, acName) do	{ Alx::AlxTrace::alxTraceCpp.WriteSm(smLevel, smName, stName, acName); } while(false)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxTrace
	{
		class ITrace
		{
			public:
				ITrace() {};
				virtual ~ITrace() {};
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
				virtual void WriteStr(const char* str) = 0;
				virtual void WriteFormat(const char* format, ...) = 0;
				virtual void WriteStd(const char* file, uint32_t line, const char* fun, const char* format, ...) = 0;
				virtual void WriteSm(uint8_t smLevel, const char* smName, const char* stName, const char* acName) = 0;
		};
		class ATrace : public ITrace
		{
			public:
				ATrace(::AlxTrace* me) : me(me) {};
				virtual ~ATrace() {};
				void Init(void) override
				{
					AlxTrace_Init(me);
				}
				void DeInit(void) override
				{
					AlxTrace_DeInit(me);
				}
				void WriteStr(const char* str) override
				{
					AlxTrace_WriteStr(me, str);
				}
				void WriteFormat(const char* format, ...) override
				{
					char buff[256] = {};
					va_list args = {};

					va_start(args, format);
					vsnprintf(buff, 256, format, args);
					va_end(args);

					WriteStr(buff);
				}
				void WriteStd(const char* file, uint32_t line, const char* fun, const char* format, ...) override
				{
					char buff[256] = {};
					va_list args = {};

					AlxGlobal_Uint64ToStr(AlxTick_Get_ms(&alxTick), buff);
					WriteFormat("trace;%s;%s;%lu;%s;", buff, file, line, fun);

					va_start(args, format);
					vsnprintf(buff, 256, format, args);
					va_end(args);

					WriteFormat("%s\r\n", buff);
				}
				void WriteSm(uint8_t smLevel, const char* smName, const char* stName, const char* acName) override
				{
					if ((smName != NULL) && (stName != NULL) && (acName != NULL))
					{
						char smLevelStr[50] = {};
						AlxTrace_GetSmLevelStr(smLevel, smLevelStr);

						char tickStr[50] = {};
						AlxGlobal_Uint64ToStr(AlxTick_Get_ms(&alxTick), tickStr);

						WriteFormat("traceSm;%s;%s%s_%s_%s\r\n", tickStr, smLevelStr, smName, stName, acName);
					}
				}
			protected:
				::AlxTrace* me = nullptr;
		};
		#if (defined(ALX_STM32F1) || defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)) && (!defined(ALX_MBED))
		class Trace : public ATrace
		{
			public:
				Trace
				(
					::AlxTrace* me,
					GPIO_TypeDef* port,
					uint16_t pin,
					#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
					uint32_t alternate,
					#endif // defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
					USART_TypeDef* usart,
					::AlxGlobal_BaudRate baudRate
				) : ATrace(me)
				{
					AlxTrace_Ctor(	me,
									port,
									pin,
									#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
									alternate,
									#endif // defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
									usart,
									baudRate
									);
				};
				virtual ~Trace() {};
		};
		#endif
		#if defined(ALX_MBED)
		class Trace : public ATrace
		{
			public:
				Trace
				(
					::AlxTrace* me
				) : ATrace(me)
				{
					AlxTrace_Ctor(me);
				};
				virtual ~Trace() {};
				void Init(void) override
				{
					mbed_trace_init();
				}
				void WriteStd(const char* file, uint32_t line, const char* fun, const char* format, ...) override
				{
					char buffTick[256] = {};
					char buff[256] = {};
					va_list args = {};

					va_start(args, format);
					vsnprintf(buff, 256, format, args);
					va_end(args);
					AlxGlobal_Uint64ToStr(AlxTick_Get_ms(&alxTick), buffTick);
					WriteFormat("trace;%s;%s;%lu;%s;%s", buffTick, file, line, fun, buff);
				}
				void WriteFormat(const char* format, ...) override
				{
					char buff[256] = {};
					va_list args = {};

					va_start(args, format);
					vsnprintf(buff, 256, format, args);
					va_end(args);

					mbed_tracef(TRACE_LEVEL_CMD, "alxTrace.hpp", buff);
				}
		};
		extern Trace alxTraceCpp;
		#endif
	}
}

#endif // ALIX_TRACE_HPP
