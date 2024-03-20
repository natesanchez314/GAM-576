//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VEC3_PROXY_H
#define ENGINE_MATH_VEC3_PROXY_H

namespace Azul
{
	// Vector related proxies here:

	struct Vec3Proxy
	{
	public:
		// sample
		// 
		//   Vec3Proxy(float a, float b, float c);
		//	 operator float() const;
		//   bool operator > (const Vec3Proxy &r) const;

		Vec3Proxy(float _x, float _y, float _z);
		bool operator==(const Vec3Proxy& rhs) const;
		bool operator!=(const Vec3Proxy& rhs) const;
		bool operator>=(const Vec3Proxy& rhs) const;
		bool operator<=(const Vec3Proxy& rhs) const;
		bool operator>(const Vec3Proxy& rhs) const;
		bool operator<(const Vec3Proxy& rhs) const;
		operator float() const;

	private:
		float x;
		float y;
		float z;
	};

}

#endif

//--- End of File ---
