/**
  ******************************************************************************
  * @file		alxAudioVol.hpp
  * @brief		Auralix C++ Library - ALX Audio Volume Module
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
#ifndef ALX_AUDIO_VOL_HPP
#define ALX_AUDIO_VOL_HPP


//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAudioVol.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAudioVol
	{
		//******************************************************************************
		// Class - IAudioVol
		//******************************************************************************
		class IAudioVol
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				IAudioVol() {}
				virtual ~IAudioVol() {}
				virtual float Process(float inSample) = 0;
				virtual void Set_pct(float vol_pct) = 0;
				virtual void Set_dB(float gain_dB) = 0;
		};


		//******************************************************************************
		// Class - AudioVol
		//******************************************************************************
		class AudioVol final : public IAudioVol
		{
			public:
				//------------------------------------------------------------------------------
				// Public Functions
				//------------------------------------------------------------------------------
				AudioVol
				(
					float volMin_dB,
					float volMax_dB
				)
				{
					AlxAudioVol_Ctor
					(
						&me,
						volMin_dB,
						volMax_dB
					);
				}
				virtual ~AudioVol() {}
				float Process(float inSample) override
				{
					return AlxAudioVol_Process(&me, inSample);
				}
				void Set_pct(float vol_pct) override
				{
					AlxAudioVol_Set_pct(&me, vol_pct);
				}
				void Set_dB(float gain_dB) override
				{
					AlxAudioVol_Set_dB(&me, gain_dB);
				}
			protected:
				//------------------------------------------------------------------------------
				// Protected Variables
				//------------------------------------------------------------------------------
				::AlxAudioVol me = {};
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_AUDIO_VOL_HPP
