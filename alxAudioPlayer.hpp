/**
  ******************************************************************************
  * @file		alxAudioPlayer.hpp
  * @brief		Auralix C++ Library - ALX Audio Player Module
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
#ifndef ALX_AUDIO_PLAYER_HPP
#define ALX_AUDIO_PLAYER_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxAudioPlayer.h"


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxAudioPlayer
	{
		class IAudioPlayer
		{
			public:
				IAudioPlayer() {};
				virtual ~IAudioPlayer() {};
				virtual void LoadTrack(const uint8_t* trackPtr, uint32_t len_Byte, uint32_t startOffset_Sample, ::AlxAudio_Encoding encoding, bool isMono) = 0;
				virtual float GetSampleL(void) = 0;
				virtual float GetSampleR(void) = 0;
				virtual float GetSampleMono(void) = 0;
				virtual void IncSampleOffset(void) = 0;
				virtual void Play(void) = 0;
				virtual void Stop(void) = 0;
				virtual void Pause(void) = 0;
				virtual void Replay(void) = 0;
				virtual void LoopOn(void) = 0;
				virtual void LoopOff(void) = 0;
				virtual void LoopConfig(bool isOn) = 0;
				virtual bool IsPlaying(void) = 0;
		};
		class AudioPlayer final : public IAudioPlayer
		{
			public:
				AudioPlayer
				(
					const uint8_t* defaultTrackPtr,
					uint32_t defaultTrackLen_Byte,
					uint32_t defaultTrackStartOffset_Sample,
					AlxAudio_Encoding defaultTrackEncoding,
					bool isDefaultTrackMono
				)
				{
					AlxAudioPlayer_Ctor
					(
						&me,
						defaultTrackPtr,
						defaultTrackLen_Byte,
						defaultTrackStartOffset_Sample,
						defaultTrackEncoding,
						isDefaultTrackMono
					);
				};
				virtual ~AudioPlayer() {}
				void LoadTrack(const uint8_t* trackPtr, uint32_t len_Byte, uint32_t startOffset_Sample, AlxAudio_Encoding encoding, bool isMono) override
				{
					AlxAudioPlayer_LoadTrack(&me, trackPtr, len_Byte, startOffset_Sample, encoding, isMono);
				}
				float GetSampleL(void) override			{ return AlxAudioPlayer_GetSampleL(&me); }
				float GetSampleR(void) override			{ return AlxAudioPlayer_GetSampleR(&me); }
				float GetSampleMono(void) override		{ return AlxAudioPlayer_GetSampleMono(&me); }
				void IncSampleOffset(void) override		{ AlxAudioPlayer_IncSampleOffset(&me); }
				void Play(void) override				{ AlxAudioPlayer_Play(&me); }
				void Stop(void) override				{ AlxAudioPlayer_Stop(&me); }
				void Pause(void) override				{ AlxAudioPlayer_Pause(&me); }
				void Replay(void) override				{ AlxAudioPlayer_Replay(&me); }
				void LoopOn(void) override				{ AlxAudioPlayer_LoopOn(&me); }
				void LoopOff(void) override				{ AlxAudioPlayer_LoopOff(&me); }
				void LoopConfig(bool isOn) override		{ AlxAudioPlayer_LoopConfig(&me, isOn); }
				bool IsPlaying(void) override			{ return AlxAudioPlayer_IsPlaying(&me); }
			protected:
				::AlxAudioPlayer me = {};
		};
	}
}

#endif // ALX_AUDIO_PLAYER_HPP
