/**
  ******************************************************************************
  * @file alxIoPinIrq.hpp
  * @brief Auralix C++ Library - ALX IO Pin Module
  * @version $LastChangedRevision: 5745 $
  * @date $LastChangedDate: 2021-08-08 19:52:52 +0200 (Sun, 08 Aug 2021) $
  ******************************************************************************
  */

#ifndef ALX_IO_PIN_IRQ_HPP
#define ALX_IO_PIN_IRQ_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxIoPinIrq.h>
#include <alxIoPin.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxIoPinIrq
	{
		class IIoPinIrq
		{
			public:
				IIoPinIrq() {};
				virtual ~IIoPinIrq() {};
				virtual void Init(void) = 0;
				virtual void DeInit(void) = 0;
		};
		class AIoPinIrq : public IIoPinIrq
		{
			public:
				AIoPinIrq() {};
				virtual ~AIoPinIrq() {};
				void Init(void) override
				{
					return AlxIoPinIrq_Init(&me);
				}
				void DeInit(void) override
				{
					return AlxIoPinIrq_DeInit(&me);
				}
			protected:
				::AlxIoPinIrq me = {};
		};
		#if defined(ALX_STM32F4) || defined(ALX_STM32G4) || defined(ALX_STM32L0)
		class IoPinIrq : public AIoPinIrq
		{
			public:
				IoPinIrq
				(
					AlxIoPin::IIoPin** ioPinArr,
					uint8_t numOfIoPins,
					Alx_IrqPriority* irqPriorityArr
				)
				{
					for (uint32_t i = 0; i < numOfIoPins; i++)
					{
						AlxIoPin::IIoPin* temp = *(ioPinArr + i);
						ioPinIrqIoPinArr[i] = temp->GetCStructPtr();
					}
					
					AlxIoPinIrq_Ctor
					(
						&me,
						ioPinIrqIoPinArr,
						numOfIoPins,
						irqPriorityArr
					);
				};
				virtual ~IoPinIrq() {};
			private:
				::AlxIoPin* ioPinIrqIoPinArr[ALX_IO_PIN_IRQ_BUFF_LEN] = {};
		};
		#endif
	}
}

#endif // ALX_IO_PIN_IRQ_HPP
