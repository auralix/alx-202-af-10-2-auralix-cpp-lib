/**
  ******************************************************************************
  * @file alxSm.hpp
  * @brief Auralix C++ Library - ALX State Machine Module
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

#ifndef ALX_SM_HPP
#define ALX_SM_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxTrace.h>


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

#endif // ALX_SM_HPP
