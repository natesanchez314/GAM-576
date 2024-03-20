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

TEST(Vec3_Set_Brackets, TestConfig::ALL)
{
#if Vec3_Set_Brackets

	Vec3 A(0.0f, 0.0f, 0.0f);

	CHECK(A[x] == 0.0f);
	CHECK(A[y] == 0.0f);
	CHECK(A[z] == 0.0f);

	A[x] = 2.0f;
	A[y] = 3.0f;
	A[z] = 4.0f;

	CHECK(A[x] == 2.0f);
	CHECK(A[y] == 3.0f);
	CHECK(A[z] == 4.0f);

#endif
}  TEST_END

// ---  End of File ---------------
