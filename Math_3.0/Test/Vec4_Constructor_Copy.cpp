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

TEST(Vec4_Constructor_Copy, TestConfig::ALL)
{
#if Vec4_Constructor_Copy

	Vec4 A(2.0f, 3.0f, 4.0f, 5.0f);
	Vec4 B(A);

	CHECK(A[x] == 2.0f);
	CHECK(A[y] == 3.0f);
	CHECK(A[z] == 4.0f);
	CHECK(A[w] == 5.0f);

	CHECK(B[x] == 2.0f);
	CHECK(B[y] == 3.0f);
	CHECK(B[z] == 4.0f);
	CHECK(B[w] == 5.0f);

#endif
} TEST_END

// ---  End of File ---------------
