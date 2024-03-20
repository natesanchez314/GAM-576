//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
	// Add Proxy here

	Vec4Proxy::Vec4Proxy(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{ }

	bool Vec4Proxy::operator==(const Vec4Proxy& rhs) const
	{
		return (x * x + y * y + z * z + w * w) == (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
	}

	bool Vec4Proxy::operator!=(const Vec4Proxy& rhs) const
	{
		return (x * x + y * y + z * z + w * w) != (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
	}

	bool Vec4Proxy::operator>=(const Vec4Proxy& rhs) const
	{
		return (x * x + y * y + z * z + w * w) >= (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
	}

	bool Vec4Proxy::operator<=(const Vec4Proxy& rhs) const
	{
		return (x * x + y * y + z * z + w * w) <= (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
	}

	bool Vec4Proxy::operator>(const Vec4Proxy& rhs) const
	{
		return (x * x + y * y + z * z + w * w) > (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
	}

	bool Vec4Proxy::operator<(const Vec4Proxy& rhs) const
	{
		return (x * x + y * y + z * z + w * w) < (rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w);
	}

	Vec4Proxy::operator float() const
	{
		return Trig::sqrt(x * x + y * y + z * z + w * w);
	}
}

//--- End of File ---
