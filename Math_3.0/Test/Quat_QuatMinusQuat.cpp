//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"

using namespace Azul;

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

TEST(Quat_QuatMinusQuat, TestConfig::ALL)
{
#if Quat_QuatMinusQuat

	Quat q1, q2;
	Quat out1;
	// Quat - Quat
	q1.set(1.0f, 2.0f, 3.0f, 4.0f);
	q2.set(3.0f, 10.0f, 7.0f, 20.0f);

	// out1 = q1 - q2 
	out1 = q1 - q2;

	CHECK((out1[x] == -2.0f));
	CHECK((out1[y] == -8.0f));
	CHECK((out1[z] == -4.0f));
	CHECK((out1[w] == -16.0f));

	CHECK(q1[x] == 1.0f);
	CHECK(q1[y] == 2.0f);
	CHECK(q1[z] == 3.0f);
	CHECK(q1[w] == 4.0f);

	CHECK(q2[x] == 3.0f);
	CHECK(q2[y] == 10.0f);
	CHECK(q2[z] == 7.0f);
	CHECK(q2[w] == 20.0f);

#endif
} TEST_END

// --- End of File ---
