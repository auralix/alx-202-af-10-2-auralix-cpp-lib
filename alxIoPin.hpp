/**
  ******************************************************************************
  * @file alxIoPin.hpp
  * @brief Auralix C++ Library - ALX IO Pin Module
  * @version $LastChangedRevision: 4690 $
  * @date $LastChangedDate: 2021-04-12 13:34:52 +0200 (Mon, 12 Apr 2021) $
  ******************************************************************************
  */

#ifndef ALX_IO_PIN_HPP
#define ALX_IO_PIN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxIoPin.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxIoPin
	{
		class IIoPin
		{
			public:
				IIoPin() {};
				virtual ~IIoPin() {};
				virtual void Init(void)							= 0;
				virtual void DeInit(void)						= 0;
				virtual bool Read(void)							= 0;
				virtual void Write(bool val)					= 0;
				virtual void Set(void)							= 0;
				virtual void Reset(void)						= 0;
				virtual void Toggle(void)						= 0;
				virtual ::AlxIoPin_TriState Read_TriState(void)	= 0;
				virtual ::AlxIoPin* GetCStructPtr(void)			= 0;
		};
		class AIoPin : public IIoPin
		{
			public:
				AIoPin() {};
				virtual ~AIoPin() {};
				void Init(void) override							{ AlxIoPin_Init(&me); }
				void DeInit(void) override							{ AlxIoPin_DeInit(&me); }
				bool Read(void) override							{ return AlxIoPin_Read(&me); }
				void Write(bool val) override						{ AlxIoPin_Write(&me, val); }
				void Set(void) override								{ AlxIoPin_Set(&me); }
				void Reset(void) override							{ AlxIoPin_Reset(&me); }
				void Toggle(void) override							{ AlxIoPin_Toggle(&me); }
				::AlxIoPin_TriState Read_TriState(void) override	{ return AlxIoPin_Read_TriState(&me); }
				::AlxIoPin* GetCStructPtr(void) override			{ return &me; }
			protected:
				::AlxIoPin me = {};
		};
		#if defined (ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class IoPin : public AIoPin
		{
			public:
				IoPin
				(
					GPIO_TypeDef* port,
					uint16_t pin,
					uint32_t mode,
					uint32_t pull,
					uint32_t speed,
					uint32_t alternate,
					bool val
				)
				{
					AlxIoPin_Ctor(&me, port, pin, mode, pull, speed, alternate, val);
				};
				virtual ~IoPin() {};
		};
		#endif
	}
}

#endif // ALX_IO_PIN_HPP
