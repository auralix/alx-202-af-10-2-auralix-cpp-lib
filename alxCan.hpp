/**
  ******************************************************************************
  * @file alxCan.hpp
  * @brief Auralix C++ Library - ALX CAN Module
  * @version $LastChangedRevision: 5930 $
  * @date $LastChangedDate: 2021-09-03 15:45:15 +0200 (Fri, 03 Sep 2021) $
  ******************************************************************************
  */

#ifndef ALX_CAN_HPP
#define ALX_CAN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxCan.h>
#include <alxIoPin.hpp>
#include <alxClk.hpp>
#include <alxFifo.hpp>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxCan
	{
		class ICan
		{
			public:
				ICan() {};
				virtual ~ICan() {};
				virtual ::Alx_Status Init(void) = 0;
				virtual ::Alx_Status DeInit(void) = 0;
				virtual ::Alx_Status ReInit(void) = 0;
				virtual ::Alx_Status TxMsg(::AlxCan_Msg msg) = 0;
				virtual ::Alx_Status TxMsg(::AlxCan_Msg* msg, uint32_t numOfMsg) = 0;
				virtual ::Alx_Status RxMsg(::AlxCan_Msg* msg) = 0;
				virtual ::Alx_Status RxMsg(::AlxCan_Msg* msg, uint32_t numOfMsg) = 0;
				virtual bool IsErr(void) = 0;
				virtual void Foreground_Handle(void) = 0;
		};
		template <uint32_t txFifoMaxNumOfMsg, uint32_t rxFifoMaxNumOfMsg>
		class ACan : public ICan
		{
			public:
				ACan() {};
				virtual ~ACan() {};
				::Alx_Status Init(void) override
				{
					return AlxCan_Init(&me);
				}
				::Alx_Status DeInit(void) override
				{
					return AlxCan_DeInit(&me);
				}
				::Alx_Status ReInit(void) override
				{
					return AlxCan_ReInit(&me);
				}
				::Alx_Status TxMsg(::AlxCan_Msg msg) override
				{
					return AlxCan_TxMsg(&me, msg);
				}
				::Alx_Status TxMsg(::AlxCan_Msg* msg, uint32_t numOfMsg) override
				{
					return AlxCan_TxMsgMulti(&me, msg, numOfMsg);
				}
				::Alx_Status RxMsg(::AlxCan_Msg* msg) override
				{
					return AlxCan_RxMsg(&me, msg);
				}
				::Alx_Status RxMsg(::AlxCan_Msg* msg, uint32_t numOfMsg) override
				{
					return AlxCan_RxMsgMulti(&me, msg, numOfMsg);
				}
				bool IsErr(void) override
				{
					return AlxCan_IsErr(&me);
				}
				void Foreground_Handle(void) override
				{
					return AlxCan_Foreground_Handle(&me);
				}
			protected:
				::AlxCan me = {};
				AlxFifo::Fifo<txFifoMaxNumOfMsg * sizeof(AlxCan_Msg)> txFifo = {};
				AlxFifo::Fifo<rxFifoMaxNumOfMsg * sizeof(AlxCan_Msg)> rxFifo = {};
		};
		#if (defined(ALX_STM32F4) && defined(HAL_CAN_MODULE_ENABLED)) || (defined(ALX_STM32G4) && defined(HAL_FDCAN_MODULE_ENABLED))
		template <uint32_t txFifoMaxNumOfMsg, uint32_t rxFifoMaxNumOfMsg>
		class Can : public ACan <txFifoMaxNumOfMsg, rxFifoMaxNumOfMsg>
		{
			public:
				Can
				(
					#if defined(ALX_STM32F4)
				 	CAN_TypeDef* can,
					#endif
				 	#if defined(ALX_STM32G4)
					FDCAN_GlobalTypeDef* can,
					#endif
					AlxIoPin::IIoPin* do_CAN_TX,
					AlxIoPin::IIoPin* di_CAN_RX,
					AlxClk::IClk* clk,
					AlxCan_Clk canClk,
					Alx_IrqPriority txIrqPriority,
					Alx_IrqPriority rxIrqPriority
				)
				{
					AlxCan_Ctor
					(
						&this->me,
						can,
						do_CAN_TX->GetCStructPtr(),
						di_CAN_RX->GetCStructPtr(),
						clk->GetCStructPtr(),
						canClk,
						this->txFifo.GetBuffPtr(),
						txFifoMaxNumOfMsg * sizeof(AlxCan_Msg),
						this->rxFifo.GetBuffPtr(),
						txFifoMaxNumOfMsg * sizeof(AlxCan_Msg),
						txIrqPriority,
						rxIrqPriority
					);
				};
				virtual ~Can() {};
		};
		#endif
	}
}

#endif // ALX_CAN_HPP
