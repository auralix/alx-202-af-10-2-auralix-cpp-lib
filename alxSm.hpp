/**
  ******************************************************************************
  * @file		alxSm.hpp
  * @brief		Auralix C++ Library - ALX State Machine Module
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
#ifndef ALX_SM_HPP
#define ALX_SM_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include "alxGlobal.hpp"
#include "alxTrace.h"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Preprocessor
//******************************************************************************

// Trace //
#if defined(_ALX_SM_TRACE) || defined(_ALX_TRACE_ALL)
	#define ALX_SM_TRACE(smLevel, smName, stName, acName) ALX_TRACE_SM(smLevel, smName, stName, acName)
#else
	#define ALX_SM_TRACE(...) do{} while (false)
#endif


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxSm
	{
		//******************************************************************************
		// Class - St
		//******************************************************************************
		class St
		{
			public:
				St() {};
				virtual ~St() {};
				virtual void Do(void)
				{
					void();
				}
				virtual void Entry(void)
				{
					void();
				}
				virtual void Exit(void)
				{
					void();
				}
			protected:
				const char* name = nullptr;
			private:
				friend class Sm;
		};


		//******************************************************************************
		// Class - Sm
		//******************************************************************************
		class Sm
		{
			public:
				virtual void Handle(void)
				{
					st->Do();
				};
			protected:
				void SetSt(St* st)
				{
					this->st->Exit(); // Exit current state, execute exit action
					ALX_SM_TRACE(level, name, this->st->name, "Exit");

					this->st = st; // Change state

					ALX_SM_TRACE(level, name, this->st->name, "Entry");
					this->st->Entry(); // Enter new state, execute entry action
				}
			protected:
				enum class Level : uint32_t
				{
					_0 = 0,
					_1 = 1,
					_2 = 2,
					_3 = 3,
					_4 = 4,
					_5 = 5
				};
				Sm(St* st, Level level) : st(st), level((uint32_t)level) {};
				virtual ~Sm() {};
				void Exit(St* st)
				{
					st->Exit();
					ALX_SM_TRACE(level, name, st->name, "Exit");
				}
			protected:
				const uint32_t level = 0;
				const char* name = nullptr;
				St* st = nullptr;
		};
	}
}


#endif	// #if defined(ALX_CPP_LIB)

#endif // ALX_SM_HPP
