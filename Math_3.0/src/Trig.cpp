//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <math.h>    // <--- ONLY location for <math.h> allowed
#include "Trig.h"

namespace Azul
{
	// Do your magic here

	float Trig::cos(float theta)
	{
		return std::cosf(theta);
	}

	float Trig::sin(float theta)
	{
		return std::sinf(theta);
	}

	float Trig::tan(float theta)
	{
		return std::tanf(theta);
	}

	float Trig::atan(float theta)
	{
		return std::atanf(theta);
	}

	float Trig::atan2(float x, float y)
	{
		return std::atan2f(x, y);
	}

	float Trig::acos(float theta)
	{
		return std::acosf(theta);
	}

	float Trig::asin(float theta)
	{
		return std::asinf(theta);
	}

	void Trig::cossin(float& a, float& b, float c)
	{
		a = Trig::cos(c);
		b = Trig::sin(c);
	}

	float Trig::rsqrt(float val)
	{
		return 1.0f / Trig::sqrt(val);
	}

	float Trig::sqrt(const float val)
	{
		return std::sqrtf(val);
	}
}

//--- End of File ---
