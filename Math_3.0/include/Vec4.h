//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_Vect4D_H
#define ENGINE_MATH_Vect4D_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Constants.h"
#include "Vec4Proxy.h"

// This file assumes Framework.h is included in executable for Align16

namespace Azul
{
	// forward declare
	class Mat4;
	class Mat3;
	class Vec3;
	class Quat;

	// -----------------------------------------------------------
	// 
	// Vec4 
	//   True 4 element vector... 
	//     its stored in a SIMD friendly struct for cache reasons
	//                         
	//   v4  = | x  y  z  w | 
	//     
	// -----------------------------------------------------------

	class Vec4 final : public Align16
	{
	public:

	    // Do your magic here

		Vec4();
		Vec4(float x, float y, float z);
		Vec4(float x, float y, float z, float w);
		Vec4(const Vec3& vec3);
		Vec4(const Vec3& vec3, float w);
		Vec4(const Vec4& other);
		Vec4& operator=(const Vec4& other);
		~Vec4();

		bool isEqual(const Vec4& other) const;
		bool isEqual(const Vec4& other, float epsilon) const;
		bool isZero() const;
		bool isZero(float epsilon) const;

		Vec4 operator+(const Vec4& rhs);
		void operator+=(const Vec4& rhs);
		Vec4 operator+();
		Vec4 operator-(const Vec4& rhs);
		friend Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
		{
			return Vec4(lhs._vx - rhs._vx, lhs._vy - rhs._vy, lhs._vz - rhs._vz, lhs._vw - rhs._vw);
		}
		void operator-=(const Vec4& rhs);
		Vec4 operator-();
		Vec4 operator*(float rhs);
		friend Vec4 operator*(float lhs, const Vec4& rhs)
		{
			return Vec4(lhs * rhs._vx, lhs * rhs._vy, lhs * rhs._vz, lhs * rhs._vw);
		}
		Vec4 operator*(const Mat4& rhs);
		void operator*=(float rhs);
		void operator*=(const Mat4& rhs);

		Vec4& norm();
		Vec4 getNorm() const;
		Vec4Proxy len() const;
		float magSqr() const;
		float dot(const Vec4& rhs) const;
		Vec4 cross(const Vec4& rhs) const;
		float getAngle(const Vec4& rhs) const;

		// Getters
		float x() const;
		float y() const;
		float z() const;
		float w() const;
		float operator[](const x_enum) const;
		float operator[](const y_enum) const;
		float operator[](const z_enum) const;
		float operator[](const w_enum) const;

		// Setters
		float& x();
		float& y();
		float& z();
		float& w();
		void x(float x);
		void y(float y);
		void z(float z);
		void w(float w);
		float& operator[](const x_enum);
		float& operator[](const y_enum);
		float& operator[](const z_enum);
		float& operator[](const w_enum);
		void set(float x, float y, float z);
		void set(float x, float y, float z, float w);
		void set(const Vec4& other);
		void set(const Vec3& vec3);
		void set(const Vec3& vec3, float w);
	
		// sample of my protos

		// Constructors
		//Vec4(const float in_x, const float in_y, const float in_z, const float in_w);

		// Forces User to explicitly do the cast or constructor call with explicit
		// Vec4(const Vec3 &v, const float w = 1.0f);

		// Bracket
		// float &operator[] (const enum x_enum);
		// const float operator[] (const enum x_enum) const;

		// Accessors - Robin's suggestion
		// void x(const float v);
		// const float x()const;

		// scale operators
		// Vec4 operator * (const float scale) const;
		// friend Vec4 operator *(const float scale, const Vec4 &inV);
		// void operator *= (const float scale);

		// Vec4 * Mat4
		// Vec4 operator * (const Mat4 &m) const;
		// Vec4 operator *= (const Mat4 &m);

		// (Vec3,1) * Mat4
        // friend Vec4 operator *(const Vec3 &v, const Mat4 &m);
        // friend Vec4 operator *= (const Vec3 &v, const Mat4 &m);

		// Vec4 functions
		// const Vec4Proxy len() const;

		// set
		// void set(const Vec4 &A);
		// void set(const Vec3 &v, const float w = 1.0f);

		// comparison
		// bool isEqual(const Vec4 &v, const float epsilon = MATH_TOLERANCE) const;
	
		// for printing
		void Print(const char *pName) const;

	private:

		friend Mat4;
		friend Mat3;
		friend Vec3;
		friend Quat;

		union
		{
			/*                          */
			/*   v4  = | x  y  z  w |   */
			/*                          */

			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				float _vw;
			};
		};
	};

	Vec4 operator* (const Vec3 &v, const Mat4 &m);
	Vec4 operator*= (const Vec3 &v, const Mat4 &m);
}

#endif

//--- End of File ---
