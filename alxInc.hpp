/**
  ******************************************************************************
  * @file		alxInc.hpp
  * @brief		Auralix C++ Library - ALX Include File
  * @copyright	Copyright (C) Auralix d.o.o. All rights reserved.
  *
  * @section License
  *
  * SPDX-License-Identifier: GPL-3.0-or-later
  *
  * This file is part of Auralix C++ Library.
  *
  * Auralix C++ Library is free software: you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation, either version 3
  * of the License, or (at your option) any later version.
  *
  * Auralix C++ Library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with Auralix C++ Library. If not, see <https://www.gnu.org/licenses/>.
  ******************************************************************************
  **/

//******************************************************************************
// Include Guard
//******************************************************************************
#ifndef ALX_INC_HPP
#define ALX_INC_HPP


//******************************************************************************
// Includes
//******************************************************************************


//------------------------------------------------------------------------------
// ALX - EXT
//------------------------------------------------------------------------------
#include "alxAdau1961.hpp"
#include "alxAdxl355.hpp"
#include "alxBq24600.hpp"
#include "alxBts724g.hpp"
#include "alxTmp1075.hpp"
#include "alxTpa3255.hpp"


//------------------------------------------------------------------------------
// ALX - MCU
//------------------------------------------------------------------------------
#include "alxAdc.hpp"
#include "alxCan.hpp"
#include "alxClk.hpp"
#include "alxDac.hpp"
#include "alxI2c.hpp"
#include "alxI2s.hpp"
#include "alxIoPin.hpp"
#include "alxIoPinIrq.hpp"
#include "alxMmc.hpp"
#include "alxPwm.hpp"
#include "alxRtc.hpp"
#include "alxSerialPort.hpp"
#include "alxSpi.hpp"
#include "alxTrace.hpp"
#include "alxWdt.hpp"


//------------------------------------------------------------------------------
// ALX
//------------------------------------------------------------------------------
#include "alxAudioPlayer.hpp"
#include "alxAudioVol.hpp"
#include "alxAvg.hpp"
#include "alxCrc.hpp"
#include "alxFifo.hpp"
#include "alxFiltGlitchBool.hpp"
#include "alxFiltGlitchUint32.hpp"
#include "alxFs.hpp"
#include "alxFtpClient.hpp"
#include "alxGlobal.hpp"
#include "alxHys1.hpp"
#include "alxHys2.hpp"
#include "alxId.hpp"
#include "alxInc.hpp"
#include "alxInterpLin.hpp"
#include "alxLinFun.hpp"
#include "alxLogger.hpp"
#include "alxMemRaw.hpp"
#include "alxMemSafe.hpp"
#include "alxNet.hpp"
#include "alxNtpClient.hpp"
#include "alxOsMutex.hpp"
#include "alxOsThread.hpp"
#include "alxParamGroup.hpp"
#include "alxParamItem.hpp"
#include "alxParamKvStore.hpp"
#include "alxParamMgmt.hpp"
#include "alxParamStore.hpp"
#include "alxSd.hpp"
#include "alxSm.hpp"
#include "alxSocket.hpp"
#include "alxTempSensRtdVdiv.hpp"
#include "alxTimSw.hpp"


#endif	// #ifndef ALX_INC_HPP
