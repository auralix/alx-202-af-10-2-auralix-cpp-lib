/**
  ******************************************************************************
  * @file alxClk.hpp
  * @brief Auralix C++ Library - ALX Clock Module
  * @version $LastChangedRevision: 5926 $
  * @date $LastChangedDate: 2021-09-03 00:31:26 +0200 (Fri, 03 Sep 2021) $
  ******************************************************************************
  */

#ifndef ALX_CLK_HPP
#define ALX_CLK_HPP

//******************************************************************************
// Includes
//******************************************************************************
#include <alxGlobal.hpp>
#include <alxClk.h>


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxClk
	{
		class IClk
		{
			public:
				IClk() {};
				virtual ~IClk() {};
				virtual ::Alx_Status Init(void)					= 0;
				virtual uint32_t GetClk_Hz(::AlxClk_Clk clk)	= 0;
				virtual void Irq_Handle(void)					= 0;
				virtual ::AlxClk* GetCStructPtr(void)			= 0;
		};

		#ifndef ALX_GTEST
		class Clk final : public IClk
		{
			public:
				Clk
				(
					::AlxClk_Config config
				)
				{
					AlxClk_Ctor(&me, config);
				};
				virtual ~Clk() {};
				::Alx_Status Init(void) override				{ return AlxClk_Init(&me); }
				uint32_t GetClk_Hz(::AlxClk_Clk clk) override	{ return AlxClk_GetClk_Hz(&me, clk); }
				void Irq_Handle(void) override					{ return AlxClk_Irq_Handle(&me); }
				::AlxClk* GetCStructPtr(void) override			{ return &me; }
			private:
				::AlxClk me = {};
		};
		#endif
	}
}

#endif // ALX_CLK_HPP
