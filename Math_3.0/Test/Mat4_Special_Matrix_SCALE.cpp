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

TEST(Mat4_Special_Matrix_SCALE, TestConfig::ALL)
{
#if Mat4_Special_Matrix_SCALE

	Mat4 A(Mat4::Scale::XYZ, 2.0f, 3.0f, 4.0f);

	CHECK(A[m0] == 2.0f);
	CHECK(A[m1] == 0.0f);
	CHECK(A[m2] == 0.0f);
	CHECK(A[m3] == 0.0f);
	CHECK(A[m4] == 0.0f);
	CHECK(A[m5] == 3.0f);
	CHECK(A[m6] == 0.0f);
	CHECK(A[m7] == 0.0f);
	CHECK(A[m8] == 0.0f);
	CHECK(A[m9] == 0.0f);
	CHECK(A[m10] == 4.0f);
	CHECK(A[m11] == 0.0f);
	CHECK(A[m12] == 0.0f);
	CHECK(A[m13] == 0.0f);
	CHECK(A[m14] == 0.0f);
	CHECK(eq_float(A[m15],1.0f));

#endif
} TEST_END

// --- End of File ---
