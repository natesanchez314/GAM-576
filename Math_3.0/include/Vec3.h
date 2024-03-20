//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VECT3_H
#define ENGINE_MATH_VECT3_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Constants.h"
#include "Vec3Proxy.h"

// This file assumes Framework.h is included in executable for Align16

namespace Azul
{
	// forward declare
	class Mat3;
	class Vec4;
	class Quat;
	class Mat4;

	// -----------------------------------------------------------
	// 
	// Vec3 
	//   True 3 element vector... 
	//     its stored in a SIMD friendly struct for cache reasons
	//     the "w" component is ignored and not set
	//                         
	//   v3  = | x  y  z  - | 
	//     
	// -----------------------------------------------------------

	class Vec3 final : public Align16
	{
	public:

		// Do your magic here

		Vec3();
		Vec3(float x, float y, float z);
		Vec3(const Vec3& other);
		Vec3(const Vec4& vec4);
		Vec3& operator=(const Vec3& other);
		~Vec3();

		bool isEqual(const Vec3& other);
		bool isEqual(const Vec3& other, float epsilon);
		bool isZero();
		bool isZero(float epsilon);

		Vec3 operator+(const Vec3& rhs);
		void operator+=(const Vec3& rhs);
		Vec3 operator+();
		Vec3 operator-(const Vec3& rhs);
		friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
		{
			return Vec3(lhs._vx - rhs._vx, lhs._vy - rhs._vy, lhs._vz - rhs._vz);
		}
		void operator-=(const Vec3& rhs);
		Vec3 operator-();
		Vec3 operator*(float rhs);
		void operator*=(float rhs);
		friend Vec3 operator*(float lhs, const Vec3& rhs)
		{
			return Vec3(lhs * rhs._vx, lhs * rhs._vy, lhs * rhs._vz);
		}
		Vec3 operator*(const Mat3& rhs);
		Vec4 operator*(const Mat4& rhs);
		void operator*=(const Mat3& rhs);
		Vec3 operator*(const Quat& rhs);
		void operator*=(const Quat& rhs);

		Vec3& norm();
		Vec3 getNorm() const;
		Vec3Proxy len() const;
		float magSqr() const;
		float dot(const Vec3& rhs) const;
		Vec3 cross(const Vec3& rhs) const;
		float getAngle(const Vec3& rhs) const;

		// Getters
		float x() const;
		float y() const;
		float z() const;
		float operator[](const x_enum) const;
		float operator[](const y_enum) const;
		float operator[](const z_enum) const;

		// Setters
		float& x();
		float& y();
		float& z();
		void x(float x);
		void y(float y);
		void z(float z);
		float& operator[](const x_enum);
		float& operator[](const y_enum);
		float& operator[](const z_enum);
		void set(float x, float y, float z);
		void set(const Vec3& other);

			// sample of my protos
			
			// Forces User to explicitly do the cast or constructor call with explicit
			//explicit Vec3(const Vec4 &v);
	                //Vec3 &operator=(const Vec4 &v);

			// Bracket
			//float &operator[] (const enum x_enum);
			//const float operator[] (const enum x_enum) const;
			//
			// Accessors - Robin's suggestion
			//void x(const float v);
			//const float x() const;

			// scale operators
			//Vec3 operator * (const float scale) const;
			//friend Vec3 operator *(const float scale, const Vec3 &inV);
			//void operator *= (const float scale);

			// Vec3 * Mat3
			//Vec3 operator* (const Mat3 &m) const;
			//Vec3 operator*= (const Mat3 &m);

			// Vector functions
			//const Vec3 cross(const Vec3 &vIn) const;
			//const Vec3Proxy len(void) const;

		// for printing
		void Print(const char *pName) const;

	private:

		friend Mat3;
		friend Vec4;
		friend Quat;

		union
		{
			/*                          */
			/*   v3  = | x  y  z  - |   */
			/*                          */

			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				
			};
		};
	};
}

#endif

//--- End of File ---
