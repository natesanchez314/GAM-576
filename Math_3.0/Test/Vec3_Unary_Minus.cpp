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

TEST(Vec3_Unary_Minus, TestConfig::ALL)
{
#if Vec3_Unary_Minus

	Vec3 A(-2.0f, -3.0f, -4.0f);
	Vec3 B(0, 0, 0);

	CHECK(A[x] == -2.0f);
	CHECK(A[y] == -3.0f);
	CHECK(A[z] == -4.0f);

	CHECK(B[x] == 0.0f);
	CHECK(B[y] == 0.0f);
	CHECK(B[z] == 0.0f);

	B = -A;

	CHECK(A[x] == -2.0f);
	CHECK(A[y] == -3.0f);
	CHECK(A[z] == -4.0f);

	CHECK(B[x] == 2.0f);
	CHECK(B[y] == 3.0f);
	CHECK(B[z] == 4.0f);

#endif
} TEST_END

// ---  End of File ---------------
