//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VEC4_PROXY_H
#define ENGINE_MATH_VEC4_PROXY_H

namespace Azul
{
	// Vector related proxies here:

	struct Vec4Proxy
	{
	public:
		//Vec4Proxy(float a, float b, float c, float d);
		//operator float() const;
		//bool operator > (const Vec4Proxy &r) const;

		Vec4Proxy(float _x, float _y, float _z, float _w);
		bool operator==(const Vec4Proxy& rhs) const;
		bool operator!=(const Vec4Proxy& rhs) const;
		bool operator>=(const Vec4Proxy& rhs) const;
		bool operator<=(const Vec4Proxy& rhs) const;
		bool operator>(const Vec4Proxy& rhs) const;
		bool operator<(const Vec4Proxy& rhs) const;
		operator float() const;

	private:
		float x;
		float y;
		float z;
		float w;
	};

}

#endif

//--- End of File ---
