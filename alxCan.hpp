/**
  ******************************************************************************
  * @file		alxCan.hpp
  * @brief		Auralix C++ Library - ALX CAN Module
  * @copyright	Copyright (C) 2020-2022 Auralix d.o.o. All rights reserved.
  *
  * @section License
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is part of Auralix C Library.
  *
  * Auralix C Library is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation, either version 3
  * of the License, or (at your option) any later version.
  *
  * Auralix C Library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Auralix C Library. If not, see <https://www.gnu.org/licenses/>.
  ******************************************************************************
  **/

//******************************************************************************
// Include Guard
//******************************************************************************
#ifndef ALX_CAN_HPP
#define ALX_CAN_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxCan.h"
#include "alxIoPin.hpp"
#include "alxClk.hpp"
#include "alxFifo.hpp"


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
