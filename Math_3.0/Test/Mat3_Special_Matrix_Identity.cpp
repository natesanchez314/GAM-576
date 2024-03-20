//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"

using namespace Azul;

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

TEST(Mat3_Special_Matrix_Identity, TestConfig::ALL)
{
#if Mat3_Special_Matrix_Identity

	Mat3 A(Mat3::Special::Identity);

	CHECK(A[m0] == 1.0f);
	CHECK(A[m1] == 0.0f);
	CHECK(A[m2] == 0.0f);
	
	CHECK(A[m4] == 0.0f);
	CHECK(A[m5] == 1.0f);
	CHECK(A[m6] == 0.0f);
	
	CHECK(A[m8] == 0.0f);
	CHECK(A[m9] == 0.0f);
	CHECK(A[m10] == 1.0f);

#endif
} TEST_END

// --- End of File ---
