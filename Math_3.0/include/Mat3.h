//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_MATRIX_3x3_H
#define ENGINE_MATH_MATRIX_3x3_H

#include "Vec4.h"
#include "Debug.h"
#include "Mat4.h"

namespace Azul
{

	class Mat3 final : public Align16
	{
	public:

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Row
		{
			i0,
			i1,
			i2
		};

	public:

		// Do your magic here

		Mat3();
		Mat3(Vec3 v0, Vec3 v1, Vec3 v2);
		Mat3(float m0, float m1, float m2, float m4, float m5, float m6, float m8, float m9, float m10);
		Mat3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11);
		Mat3(Special type);
		Mat3(const Mat3& other);
		Mat3(const Mat4& mat4);
		Mat3& operator=(const Mat3& other);
		~Mat3();

		bool isEqual(const Mat3& other) const;
		bool isIdentity() const;
		bool isIdentity(float epsilon) const;
		bool isRotation() const;
		bool isRotation(float epsilon) const;

		Mat3 operator+(const Mat3& rhs);
		void operator+=(const Mat3& rhs);
		Mat3 operator+();
		Mat3 operator-(const Mat3& rhs);
		void operator-=(const Mat3& rhs);
		Mat3 operator-();
		Mat3 operator*(const Mat3& rhs);
		void operator*=(const Mat3& rhs);
		Mat3 operator*(float rhs);
		void operator*=(float rhs);
		friend Mat3 operator*(float lhs, const Mat3& rhs)
		{
			return Mat3(lhs * rhs._m0, lhs * rhs._m1, lhs * rhs._m2, lhs * rhs._m3,
				lhs * rhs._m4, lhs * rhs._m5, lhs * rhs._m6, lhs * rhs._m7,
				lhs * rhs._m8, lhs * rhs._m9, lhs * rhs._m10, lhs * rhs._m11);
		}

		float det() const;
		void T();
		Mat3 getT() const;
		void inv();
		Mat3 getInv() const;
		void set(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d);
		void set(enum Special type);
		void set(const Row row, const Vec3& Vec3);
		Vec3& get(const Row row) const;

		// Getters
		float m0(void) const;
		float m1(void) const;
		float m2(void) const;
		float m3(void) const;
		float m4(void) const;
		float m5(void) const;
		float m6(void) const;
		float m7(void) const;
		float m8(void) const;
		float m9(void) const;
		float m10(void) const;
		float m11(void) const;
		float m12(void) const;
		float m13(void) const;
		float m14(void) const;
		float m15(void) const;
		float operator[](const m0_enum) const;
		float operator[](const m1_enum) const;
		float operator[](const m2_enum) const;
		float operator[](const m3_enum) const;
		float operator[](const m4_enum) const;
		float operator[](const m5_enum) const;
		float operator[](const m6_enum) const;
		float operator[](const m7_enum) const;
		float operator[](const m8_enum) const;
		float operator[](const m9_enum) const;
		float operator[](const m10_enum) const;
		float operator[](const m11_enum) const;
		float operator[](const m12_enum) const;
		float operator[](const m13_enum) const;
		float operator[](const m14_enum) const;
		float operator[](const m15_enum) const;

		// Setters
		float& m0(void);
		float& m1(void);
		float& m2(void);
		float& m3(void);
		float& m4(void);
		float& m5(void);
		float& m6(void);
		float& m7(void);
		float& m8(void);
		float& m9(void);
		float& m10(void);
		float& m11(void);
		float& m12(void);
		float& m13(void);
		float& m14(void);
		float& m15(void);
		void m0(float m0);
		void m1(float m1);
		void m2(float m2);
		void m3(float m3);
		void m4(float m4);
		void m5(float m5);
		void m6(float m6);
		void m7(float m7);
		void m8(float m8);
		void m9(float m9);
		void m10(float m10);
		void m11(float m11);
		void m12(float m12);
		void m13(float m13);
		void m14(float m14);
		void m15(float m15);
		float& operator[](const m0_enum);
		float& operator[](const m1_enum);
		float& operator[](const m2_enum);
		float& operator[](const m3_enum);
		float& operator[](const m4_enum);
		float& operator[](const m5_enum);
		float& operator[](const m6_enum);
		float& operator[](const m7_enum);
		float& operator[](const m8_enum);
		float& operator[](const m9_enum);
		float& operator[](const m10_enum);
		float& operator[](const m11_enum);
		float& operator[](const m12_enum);
		float& operator[](const m13_enum);
		float& operator[](const m14_enum);
		float& operator[](const m15_enum);

		void set(Vec3& a, Vec3& b, Vec3& c);

		// Sample of my protos
 			
 			// bracket operators	
			//float &operator[] (const enum m0_enum);
			//const float operator[] (const enum m0_enum) const;
 			
			// Accessor	
			//void m0(const float v);
			//const float m0() const;
			
			// Comparison
			//bool isEqual(const Mat3 &A, const float epsilon = MATH_TOLERANCE) const;

		// For printing
		void Print(const char *pName) const;


	private:
		
		friend Mat4;
		friend Vec3;
		friend Vec4;

		union
		{
			/*     | m0  m1  m2   0 | */
			/* m = | m4  m5  m6   0 | */
			/*     | m8  m9  m10  0 | */
			/*     | 0   0   0    1 | */

			struct
			{
				Vec4 _rows[4];
			};


			struct
			{
				Vec4 _v0;
				Vec4 _v1;
				Vec4 _v2;
				Vec4 _v3;
			};

			struct
			{
				float _m0;
				float _m1;
				float _m2;
				float _m3;
				float _m4;
				float _m5;
				float _m6;
				float _m7;
				float _m8;
				float _m9;
				float _m10;
				float _m11;
				float _m12;
				float _m13;
				float _m14;
				float _m15;
			};
		};
	};
}

#endif

//--- End of File ---
