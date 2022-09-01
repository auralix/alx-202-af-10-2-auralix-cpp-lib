/**
  ******************************************************************************
  * @file		alxInterpLin_GTest.cpp
  * @brief		Auralix C++ Library - ALX Linear Interpolation Module - Test
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
// Includes
//******************************************************************************
#include "alxInterpLin.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxInterpLinGTest
	{
		#if defined (ALX_GTEST)
		namespace Gtest
		{
			//******************************************************************************
			// Class - InterpLinG01Test
			//******************************************************************************
			class InterpLinG01Test : public testing::Test
			{
				protected:
					InterpLinG01Test() {};
					virtual ~InterpLinG01Test() {};

					//Alx::AlxInterpLin::InterpLin *interpLin = nullptr;

					void SetUp() override
					{
					}
					void TearDown() override
					{
					}
			};
			TEST_F(InterpLinG01Test, T01_RisingArray)
			{
				uint32_t len = 10;
				bool isRising = true;
				float dataX[10] = {1,2,3,4,5,6,7,8,9,10};
				float dataY[10] = {1,2,3,4,5,6,7,8,9,10};


				Alx::AlxInterpLin::InterpLin interpLin = {
					(float*)dataX,
					(float*)dataY,
					len,
					isRising
				};
					EXPECT_EQ(interpLin.GetY(0), 1);
					EXPECT_EQ(interpLin.GetY(1), 1);
					EXPECT_EQ(interpLin.GetY(5.5), 5.5);
					EXPECT_EQ(interpLin.GetY(10), 10);
					EXPECT_EQ(interpLin.GetY(11), 10);
			}
			TEST_F(InterpLinG01Test, T02_FallingArray)
			{
				uint32_t len = 10;
				bool isRising = false;
				float dataX[10] = {10,9,8,7,6,5,4,3,2,1};
				float dataY[10] = {10,9,8,7,6,5,4,3,2,1};

				Alx::AlxInterpLin::InterpLin interpLin = {
					(float*)dataX,
					(float*)dataY,
					len,
					isRising
				};
					EXPECT_EQ(interpLin.GetY(0), 1);
					EXPECT_EQ(interpLin.GetY(1), 1);
					EXPECT_EQ(interpLin.GetY(5.5), 5.5);
					EXPECT_EQ(interpLin.GetY(10), 10);
					EXPECT_EQ(interpLin.GetY(11), 10);
			}
			TEST_F(InterpLinG01Test, T02_ScatterdY)
			{
				uint32_t len = 10;
				bool isRising = true;
				float dataX[11] = {0,1,2,3,4,5,6,7,8,9,10};
				float dataY[11] = {0,1,2,3,0,1,2,3,0,1,2};

				Alx::AlxInterpLin::InterpLin interpLin = {
					(float*)dataX,
					(float*)dataY,
					len,
					isRising
				};
					EXPECT_EQ(interpLin.GetY(-5), 0);
					EXPECT_EQ(interpLin.GetY(3), 3);
					EXPECT_EQ(interpLin.GetY(7), 3);
					EXPECT_EQ(interpLin.GetY(6.5), 2.5);
			}

		}
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)
