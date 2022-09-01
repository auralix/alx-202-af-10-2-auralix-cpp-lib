/**
  ******************************************************************************
  * @file		alxFifo_GTest.cpp
  * @brief		Auralix C++ Library - ALX FIFO Module - Test
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
#include "alxFifo.hpp"


//******************************************************************************
// Module Guard
//******************************************************************************
#if defined(ALX_CPP_LIB)


//******************************************************************************
// Code
//******************************************************************************
namespace Alx
{
	namespace AlxFifoGTest
	{
		#if defined (ALX_GTEST)
		namespace Gtest
		{
			//******************************************************************************
			// Class - FifoG01Test
			//******************************************************************************
			class FifoG01Test : public testing::Test
			{
				protected:
					FifoG01Test() {};
					virtual ~FifoG01Test() {};

					AlxFifo::FifoTest<10>* fifoTest = nullptr;

					void SetUp() override
					{
						fifoTest = new AlxFifo::FifoTest<10>;
					}
					void TearDown() override
					{
						delete fifoTest;
					}
			};
			TEST_F(FifoG01Test, T01Ctor)
			{
				// Ctor
				uint8_t temp1[10] = {0};
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}
			TEST_F(FifoG01Test, T02WriteUpToFullThenErrLen1)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0
				data[0] = 0;
				status = fifoTest->Write(data[0]);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 1);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 1, 2, 3, 4, 5, 6
				for (uint32_t i = 1; i <= 6; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[1], 6);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 0, 1, 2, 3, 4, 5, 6 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp3, 7) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 7);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 7);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 7, 8, 9
				for (uint32_t i = 7; i <= 9; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[7], 3);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp4[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 10 (error)
				data[0] = 10;
				status = fifoTest->Write(data[0]);
				EXPECT_EQ(status, AlxFifo_ErrFull);
				uint8_t temp5[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp5, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);
			}
			TEST_F(FifoG01Test, T03WriteUpToFullThenErrLen10)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
				for (uint32_t i = 0; i <= 9; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 10);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
				for (uint32_t i = 0; i <= 9; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 10);
				EXPECT_EQ(status, AlxFifo_ErrFull);
				uint8_t temp3[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);
			}
			TEST_F(FifoG01Test, T03WriteUpToSecondToFullThenErrLen3)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 9);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 9, 0, 1 (error at writing 0)
				data[0] = 9;
				data[1] = 0;
				data[2] = 1;
				status = fifoTest->Write(&data[0], 3);
				EXPECT_EQ(status, AlxFifo_ErrFull);
				uint8_t temp3[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);
			}
			TEST_F(FifoG01Test, T04ReadUpToEmptyThenErrLen1)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 9);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 0, 1
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 0 , 1 };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 2);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 7);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 2
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 1);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp4[10] = { 2 };
				EXPECT_TRUE(memcmp(data, temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 3);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 6);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 6);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp5[10] = { 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(data, temp5, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Read = empty
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 1);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp6[10] = {0};
				EXPECT_TRUE(memcmp(data, temp6, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}
			TEST_F(FifoG01Test, T05ReadUpToEmptyThenErrLen3)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 9);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Read = empty
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 3);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp4[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}
			TEST_F(FifoG01Test, T06ReadUpToSecondToEmptyThenErrLen3)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 9);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 0, 1, 2, 3, 4, 5, 6, 7
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 8);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 0, 1, 2, 3, 4, 5, 6, 7};
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 8);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 8, empty
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 3);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp4[10] = { 8 };
				EXPECT_TRUE(memcmp(data, temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}
			TEST_F(FifoG01Test, T07WriteRead1)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 9);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 0, 1, 2, 3, 4, 5, 6, 7
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 8);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 0, 1, 2, 3, 4, 5, 6, 7 };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 8);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 7, 8, 9
				for (uint32_t i = 7; i <= 9; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[7], 3);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp4[10] = { 8, 9, 0, 0, 0, 0, 0, 0, 8, 7 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 2);
				EXPECT_EQ(fifoTest->GetTail(), 8);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 4);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 7, 8, 9
				for (uint32_t i = 7; i <= 9; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[7], 3);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp5[10] = { 8, 9, 7, 8, 9, 0, 0, 0, 8, 7 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp5, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 5);
				EXPECT_EQ(fifoTest->GetTail(), 8);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 7);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 8, 7
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp6[10] = { 8 , 7 };
				EXPECT_TRUE(memcmp(data, temp6, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 5);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 5);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, AlxFifo_ErrFull);
				uint8_t temp7[10] = { 8, 9, 7, 8, 9, 0, 1, 2, 3, 4 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp7, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Init
				fifoTest->Flush();
				uint8_t temp8[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp8, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Read = empty
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0]);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp9[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp9, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}
			TEST_F(FifoG01Test, T07WriteRead2)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 9);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 10);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp3[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Init
				fifoTest->Flush();
				uint8_t temp4[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Read = empty
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0]);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp5[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp5, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8
				for (uint32_t i = 0; i <= 8; i++) data[i] = (uint8_t)i;
				status = fifoTest->Write(&data[0], 9);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp6[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp6, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 9);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = 0, 1
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp7[10] = { 0 , 1 };
				EXPECT_TRUE(memcmp(data, temp7, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 9);
				EXPECT_EQ(fifoTest->GetTail(), 2);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 7);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);
			}
			TEST_F(FifoG01Test, T08WriteStr)
			{
				Alx_Status status;
				uint8_t data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4
				status = fifoTest->WriteStr((const char*)"01234");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { '0', '1', '2', '3', '4' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 5);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 5);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = '0', '1'
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data[0], 2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp7[10] = { '0', '1' };
				EXPECT_TRUE(memcmp(data, temp7, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 5);
				EXPECT_EQ(fifoTest->GetTail(), 2);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 3);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Init
				fifoTest->Flush();
				uint8_t temp4[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}

			TEST_F(FifoG01Test, T09WriteStrErrFull)
			{
				Alx_Status status;

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// Write = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
				status = fifoTest->WriteStr((const char*)"01234567891011");
				EXPECT_EQ(status, AlxFifo_ErrFull);
				uint8_t temp2[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp2, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Init
				fifoTest->Flush();
				uint8_t temp3[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}

			TEST_F(FifoG01Test, T10OpenThenReadStrUntil)
			{
				Alx_Status status;
				char data[10];

				// Ctor
				uint8_t temp1[10] = { 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// ReadStrUntil 1 element
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "a", 10, &numRead1);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp2[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp2, 10) == 0);
				EXPECT_EQ(numRead1, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}

			TEST_F(FifoG01Test, T11ReadStrUntil1Char)
			{
				Alx_Status status;
				char data[10];

				// Write = "aaaabbaaaa"
				status = fifoTest->WriteStr((const char*)"aaaabbaaaa");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp1[10] = { 'a', 'a', 'a', 'a', 'b', 'b', 'a', 'a', 'a', 'a' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "c"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "c", 10, &numRead1);
				EXPECT_EQ(status, AlxFifo_ErrNoDelim);
				uint8_t temp2[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp2, 10) == 0);
				EXPECT_EQ(numRead1, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "b"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead2;
				status = fifoTest->ReadStrUntil(&data[0], "b", 10, &numRead2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 'a', 'a', 'a', 'a', '\0' };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(numRead2, 4);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 5);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 5);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "a"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead3;
				status = fifoTest->ReadStrUntil(&data[0], "a", 10, &numRead3);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp4[10] = { 'b', '\0' };
				EXPECT_TRUE(memcmp(data, temp4, 10) == 0);
				EXPECT_EQ(numRead3, 1);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 7);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 3);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = "cccc"
				status = fifoTest->WriteStr((const char*)"cccc");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp5[10] = { 'c', 'c', 'c', 'c', 0, 0, 0, 'a', 'a', 'a' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp5, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 7);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 7);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "c"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead4;
				status = fifoTest->ReadStrUntil(&data[0], "c", 10, &numRead4);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp6[10] = { 'a', 'a', 'a', '\0' };
				EXPECT_TRUE(memcmp(data, temp6, 10) == 0);
				EXPECT_EQ(numRead4, 3);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 1);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 3);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "c"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead5;
				status = fifoTest->ReadStrUntil(&data[0], "c", 10, &numRead5);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp7[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp7, 10) == 0);
				EXPECT_EQ(numRead5, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 2);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 2);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);
			}

			TEST_F(FifoG01Test, T12ReadStrUntil2CharFIFOAround)
			{
				Alx_Status status;
				char data[10];

				// Write = "aaaaaabb"
				status = fifoTest->WriteStr((const char*)"aaaabbcc");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp1[10] = { 'a', 'a', 'a', 'a', 'b', 'b', 'c', 'c' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 8);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 8);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "bbd"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "bbd", 10, &numRead1);
				EXPECT_EQ(status, AlxFifo_ErrNoDelim);
				uint8_t temp2[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp2, 10) == 0);
				EXPECT_EQ(numRead1, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 8);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 8);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "bb"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead2;
				status = fifoTest->ReadStrUntil(&data[0], "bb", 10, &numRead2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 'a', 'a', 'a', 'a', '\0' };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(numRead2, 4);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 8);
				EXPECT_EQ(fifoTest->GetTail(), 6);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 2);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = "ccccdd"
				status = fifoTest->WriteStr((const char*)"ccccdd");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp4[10] = { 'c', 'c', 'd', 'd', 0, 0, 'c', 'c', 'c', 'c' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 6);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 8);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "dd"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead3;
				status = fifoTest->ReadStrUntil(&data[0], "dd", 10, &numRead3);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp5[10] = { 'c', 'c', 'c', 'c', 'c', 'c', '\0' };
				EXPECT_TRUE(memcmp(data, temp5, 10) == 0);
				EXPECT_EQ(numRead3, 6);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 4);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}

			TEST_F(FifoG01Test, T13ReadStrUntil03)
			{
				Alx_Status status;
				char data[10];

				// Write = "1234123456"
				status = fifoTest->WriteStr((const char*)"1234123456");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp1[10] = { '1', '2', '3', '4', '1', '2', '3', '4', '5', '6' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "2345"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "2345", 10, &numRead1);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { '1', '2', '3', '4', '1', '\0' };
				EXPECT_TRUE(memcmp(data, temp2, 10) == 0);
				EXPECT_EQ(numRead1, 5);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\0"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead2;
				status = fifoTest->ReadStrUntil(&data[0], "\0", 10, &numRead2);
				EXPECT_EQ(status, AlxFifo_ErrNoDelim);
				uint8_t temp3[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(numRead2, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(),false);

				// ReadStrUntil "6"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead3;
				status = fifoTest->ReadStrUntil(&data[0], "6", 10, &numRead3);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp4[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp4, 10) == 0);
				EXPECT_EQ(numRead3, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}

			TEST_F(FifoG01Test, T14ReadStrUntilrn)
			{
				Alx_Status status;
				char data[10];

				// Write = "1\r\n2\r\n3\r\n4"
				status = fifoTest->WriteStr((const char*)"1\r\n2\r\n3\r\n4");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp1[10] = { '1', '\r', '\n', '2', '\r', '\n', '3', '\r', '\n', '4' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\r\n"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "\r\n", 10, &numRead1);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { '1', '\0' };
				EXPECT_TRUE(memcmp(data, temp2, 10) == 0);
				EXPECT_EQ(numRead1, 1);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 3);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 7);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\r\n"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead2;
				status = fifoTest->ReadStrUntil(&data[0], "\r\n", 10, &numRead2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { '2', '\0' };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(numRead2, 1);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 6);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 4);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = "\r\n5\r\n6"
				status = fifoTest->WriteStr((const char*)"\r\n5\r\n6");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp4[10] = { '\r', '\n', '5', '\r', '\n', '6', '3', '\r', '\n', '4' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp4, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 6);
				EXPECT_EQ(fifoTest->GetTail(), 6);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\r\n"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead3;
				status = fifoTest->ReadStrUntil(&data[0], "\r\n", 10, &numRead3);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp5[10] = { '3', '\0' };
				EXPECT_TRUE(memcmp(data, temp5, 10) == 0);
				EXPECT_EQ(numRead3, 1);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 6);
				EXPECT_EQ(fifoTest->GetTail(), 9);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 7);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\r\n"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead4;
				status = fifoTest->ReadStrUntil(&data[0], "\r\n", 10, &numRead4);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp6[10] = { '4', '\0' };
				EXPECT_TRUE(memcmp(data, temp6, 10) == 0);
				EXPECT_EQ(numRead4, 1);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 6);
				EXPECT_EQ(fifoTest->GetTail(), 2);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 4);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\r\n"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead5;
				status = fifoTest->ReadStrUntil(&data[0], "\r\n", 10, &numRead5);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp7[10] = { '5', '\0' };
				EXPECT_TRUE(memcmp(data, temp7, 10) == 0);
				EXPECT_EQ(numRead5, 1);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 6);
				EXPECT_EQ(fifoTest->GetTail(), 5);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\r\n"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead6;
				status = fifoTest->ReadStrUntil(&data[0], "\r\n", 10, &numRead6);
				EXPECT_EQ(status, AlxFifo_ErrNoDelim);
				uint8_t temp8[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp8, 10) == 0);
				uint8_t temp9[10] = { 0, 0, 0, 0, 0, '6', 0, 0, 0, 0 };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp9, 10) == 0);
				EXPECT_EQ(numRead6, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 6);
				EXPECT_EQ(fifoTest->GetTail(), 5);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "3"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead7;
				status = fifoTest->ReadStrUntil(&data[0], "3", 10, &numRead7);
				EXPECT_EQ(status, AlxFifo_ErrNoDelim);
				uint8_t temp10[10] = { '\0' };
				EXPECT_TRUE(memcmp(data, temp10, 10) == 0);
				EXPECT_EQ(numRead7, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 6);
				EXPECT_EQ(fifoTest->GetTail(), 5);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "63"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead8;
				status = fifoTest->ReadStrUntil(&data[0], "63", 10, &numRead8);
				EXPECT_EQ(status, AlxFifo_ErrNoDelim);
				uint8_t temp11[10] = { '\0' };
				EXPECT_TRUE(memcmp(data, temp11, 10) == 0);
				EXPECT_EQ(numRead8, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 6);
				EXPECT_EQ(fifoTest->GetTail(), 5);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 1);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);
			}

			TEST_F(FifoG01Test, T15ReadStrUntil06)
			{
				Alx_Status status;
				char data[10];
				uint8_t data3[10];

				// Write = "----bbbbcc"
				status = fifoTest->WriteStr((const char*)"----bbbbcc");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp1[10] = { '-', '-', '-', '-', 'b', 'b', 'b', 'b', 'c', 'c' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Read = ----
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				status = fifoTest->Read(&data3[0], 4);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { '-', '-', '-', '-' };
				EXPECT_TRUE(memcmp(data3, temp2, 4) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 4);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 6);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// Write = "ccdd"
				status = fifoTest->WriteStr((const char*)"ccdd");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 'c', 'c', 'd', 'd', 'b', 'b', 'b', 'b', 'c', 'c' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp3, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 4);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "ddb"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "ddb", 10, &numRead1);
				EXPECT_EQ(status, AlxFifo_ErrNoDelim);
				uint8_t temp4[10] = { 0 };
				EXPECT_TRUE(memcmp(data, temp4, 10) == 0);
				EXPECT_EQ(numRead1, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 4);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "dd"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead2;
				status = fifoTest->ReadStrUntil(&data[0], "dd", 10, &numRead2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp5[10] = { 'b', 'b', 'b', 'b', 'c', 'c' , 'c', 'c' };
				EXPECT_TRUE(memcmp(data, temp5, 10) == 0);
				EXPECT_EQ(numRead2, 8);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 4);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);

				// ReadStrUntil "dd"
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead3;
				status = fifoTest->ReadStrUntil(&data[0], "dd", 10, &numRead3);
				EXPECT_EQ(status, AlxFifo_ErrEmpty);
				uint8_t temp6[10] = { 0};
				EXPECT_TRUE(memcmp(data, temp6, 10) == 0);
				EXPECT_EQ(numRead3, 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 4);
				EXPECT_EQ(fifoTest->GetTail(), 4);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}

			TEST_F(FifoG01Test, T16ReadStrUntilmaxLen)
			{
				Alx_Status status;
				char data[10];

				// Write = "aaaaaabb"
				status = fifoTest->WriteStr((const char*)"aaaabbbbbc");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp1[10] = { 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b', 'b', 'c' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "b" maxLen = 3
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "b", 3, &numRead1);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { 'a', 'a', 'a' };
				EXPECT_TRUE(memcmp(data, temp2, 10) == 0);
				EXPECT_EQ(numRead1, 3);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 5);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 5);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "c" maxLen = 3
				for (uint32_t i = 0; i < 10; i++) data[i] = 0;
				uint32_t numRead2;
				status = fifoTest->ReadStrUntil(&data[0], "c", 3, &numRead2);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp3[10] = { 'b', 'b', 'b' };
				EXPECT_TRUE(memcmp(data, temp3, 10) == 0);
				EXPECT_EQ(numRead2, 3);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}

			TEST_F(FifoG01Test, T17ReadStrUntilmaxLen02)
			{
				Alx_Status status;
				char data[5];

				// Write = "12312345\r\n"
				status = fifoTest->WriteStr((const char*)"12312345\r\n");
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp1[10] = { '1', '2', '3', '1', '2', '3', '4', '5', '\r', '\n' };
				EXPECT_TRUE(memcmp(fifoTest->GetBuffPtr(), temp1, 10) == 0);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 10);
				EXPECT_EQ(fifoTest->IsFull(), true);
				EXPECT_EQ(fifoTest->IsEmpty(), false);

				// ReadStrUntil "\r\n" maxLen = 5
				for (uint32_t i = 0; i < 5; i++) data[i] = 0;
				uint32_t numRead1;
				status = fifoTest->ReadStrUntil(&data[0], "\r\n", 5, &numRead1);
				EXPECT_EQ(status, Alx_Ok);
				uint8_t temp2[10] = { '1', '2', '3', '4', '5' };
				EXPECT_TRUE(memcmp(data, temp2, 5) == 0);
				EXPECT_EQ(numRead1, 5);
				EXPECT_EQ(fifoTest->GetBuffLen(), 10);
				EXPECT_EQ(fifoTest->GetHead(), 0);
				EXPECT_EQ(fifoTest->GetTail(), 0);
				EXPECT_EQ(fifoTest->GetNumOfEntries(), 0);
				EXPECT_EQ(fifoTest->IsFull(), false);
				EXPECT_EQ(fifoTest->IsEmpty(), true);
			}
		}
		#endif
	}
}


#endif	// #if defined(ALX_CPP_LIB)
