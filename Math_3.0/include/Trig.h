//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_TRIG_H
#define ENGINE_MATH_TRIG_H

namespace Azul
{
	class Trig
	{
	public:

		// Do your magic here

		//static float cos(const float  angle_radians);

		static float sqrt(const float val);
		static float cos(float theta);
		static float sin(float theta);
		static float tan(float theta);
		static float atan(float theta);
		static float atan2(float x, float y);
		static float acos(float theta);
		static float asin(float theta);
		static void cossin(float& a, float& b, float c);
		static float rsqrt(float val);
	};
}

#endif

//--- End of File ---
