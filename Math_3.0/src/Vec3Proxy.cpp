//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
	// Add Proxy here

	Vec3Proxy::Vec3Proxy(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{ }

	bool Vec3Proxy::operator==(const Vec3Proxy& rhs) const
	{
		return (x * x + y * y + z * z) == (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
	}

	bool Vec3Proxy::operator!=(const Vec3Proxy& rhs) const
	{
		return (x * x + y * y + z * z) != (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
	}

	bool Vec3Proxy::operator>=(const Vec3Proxy& rhs) const
	{
		return (x * x + y * y + z * z) >= (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
	}

	bool Vec3Proxy::operator<=(const Vec3Proxy& rhs) const
	{
		return (x * x + y * y + z * z) <= (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
	}

	bool Vec3Proxy::operator>(const Vec3Proxy& rhs) const
	{
		return (x * x + y * y + z * z) > (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
	}

	bool Vec3Proxy::operator<(const Vec3Proxy& rhs) const
	{
		return (x * x + y * y + z * z) < (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z);
	}

	Vec3Proxy::operator float() const
	{
		return Trig::sqrt(x * x + y * y + z * z);
	}
}

//--- End of File ---
