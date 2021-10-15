/**
  ******************************************************************************
  * @file alxInterpLin_GTest.cpp
  * @brief Auralix C++ Library - ALX Linear Interpolation Module - Test
  * @version $LastChangedRevision: 4271 $
  * @date $LastChangedDate: 2021-03-05 19:03:28 +0100 (Fri, 05 Mar 2021) $
  ******************************************************************************
  */

//******************************************************************************
// Includes
//******************************************************************************
#include <alxInterpLin.hpp>


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
