//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_MATRIX_4x4_H
#define ENGINE_MATH_MATRIX_4x4_H

#include "Vec4.h"
#include "Vec3.h"
#include "Debug.h"

namespace Azul
{
	class Quat;

	class Mat4 final : public Align16
	{
	public:

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Trans
		{
			XYZ
		};

		enum class Scale
		{
			XYZ
		};

		enum class Rot
		{
			AxisAngle,
		};

		enum class Orient
		{
			LocalToWorld,
			WorldToLocal
		};

		enum class Row
		{
			i0,
			i1,
			i2,
			i3
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

		enum class Hint : uint32_t
		{
			Generalize = 0x0,   // generalize 4x4 inverse  (no flags)
			Rot = 0x1,               // matrix inverse is M.T()
			Trans = 0x2,             // matrix inverse is M(-trans)
			RotTrans = 0x3,          // rot and trans  A_inv is A.T() 
			Scale = 0x4,             // matrix invers is M(1/scale)
			RotScale = 0x5,          // Rot and Scale no translate
			TransScale = 0x6,        // Trans and Scale no Translate
			Affine     = 0x7    // generalize Affine
		};

	public:

		// Do your magic here

		Mat4();
		Mat4(Vec4 v0, Vec4 v1, Vec4 v2, Vec4 v3);
		Mat4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);
		Mat4(const Quat& q);
		Mat4(Special type);
		Mat4(enum Rot, const Vec4& v, float angle);
		Mat4(enum Trans, float x, float y, float z);
		Mat4(enum Trans, const Vec4& Vec4);
		Mat4(enum Scale, float x, float y, float z);
		Mat4(enum Scale, const Vec4& Vec4);
		Mat4(Rot1 axis, float theta);
		Mat4(Orient orient, const Vec3& dof, const Vec3& up);
		Mat4(Orient orient, const Vec4& dof, const Vec4& up);
		Mat4(Rot3 combo, float x, float y, float z);
		Mat4(const Mat4& other);
		Mat4& operator=(const Mat4& other);
		~Mat4();

		bool isEqual(const Mat4& other) const;
		bool isIdentity() const;
		bool isIdentity(float epsilon) const;
		bool isRotation() const;
		bool isRotation(float epsilon) const;
		bool privHasHint() const;

		Mat4 operator+(const Mat4& rhs);
		void operator+=(const Mat4& rhs);
		Mat4 operator+();
		Mat4 operator-(const Mat4& rhs);
		void operator-=(const Mat4& rhs);
		Mat4 operator-();
		Mat4 operator*(const Mat4& rhs);
		void operator*=(const Mat4& rhs);
		Mat4 operator*(float rhs);
		void operator*=(float rhs);
		friend Mat4 operator*(float lhs, const Mat4& rhs)
		{
			return Mat4(lhs * rhs._m0, lhs * rhs._m1, lhs * rhs._m2, lhs * rhs._m3,
				lhs * rhs._m4, lhs * rhs._m5, lhs * rhs._m6, lhs * rhs._m7,
				lhs * rhs._m8, lhs * rhs._m9, lhs * rhs._m10, lhs * rhs._m11,
				lhs * rhs._m12, lhs * rhs._m13, lhs * rhs._m14, lhs * rhs._m15);
		}
		Mat4 operator*(const Quat& rhs);
		void operator*=(const Quat& rhs);

		float det() const;
		void T();
		Mat4 getT() const;
		void inv();
		Mat4 getInv() const;
		void set(const Vec4& a, const Vec4& b, const Vec4& c, const Vec4& d);
		void set(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);
		void set(enum Special type);
		void set(enum Trans, float x, float y, float z);
		void set(enum Trans, const Vec4& Vec4);
		void set(enum Scale, float x, float y, float z);
		void set(enum Scale, const Vec4& Vec4);
		void set(Rot1 axis, float theta);
		void set(Orient orient, const Vec3& dof, const Vec3& up);
		void set(Orient orient, const Vec4& dof, const Vec4& up);
		void set(Rot3 combo, float a, float b, float c);
		void set(enum Rot, const Vec3& v, float angle);
		void set(enum Rot, const Vec4& v, float angle);
		void set(const Row row, const Vec4& Vec4);
		void set(const Quat& q);
		Vec4& get(const Row row) const;

		void PrintHint();

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

	private:
		// Hint stuff
		void SetHintGeneral();
		void SetHintRot();
		void SetHintTrans();
		void SetHintRotTrans();
		void SetHintScale();
		void SetHintRotScale();
		void SetHintTransScale();
		void SetHintAffine();
		void SetAndCombineHints(Hint a, Hint b);
		void SetAndCopyHint(Hint h);
		Hint GetHint() const;

	public:
				// Sample of my protos
				
				//Mat4(const Trans, const float tx, const float ty, const float tz);
				//explicit Mat4(const Special type);

				// Set 
				//void set(const Row type, const Vec4 &V);

				// bracket operators	
				//float &operator[] (const enum m0_enum);
				//const float operator[] (const enum m0_enum) const;

				// Accessor	
				//void m0( const float v);
				//const float m0() const;

				// Comparison
				//const bool isRotation(const float epsilon = MATH_TOLERANCE) const;

				// Scale operators
				//Mat4 operator * (const float s) const;
				//friend Mat4 operator *(const float scale, const Mat4 &A);
				//void operator *= (const float scale);

		// For printing
		void Print(const char *pName) const;

	private:

		friend Mat3;
		friend Vec3;
		friend Vec4;

		union
		{
			/*     | m0  m1  m2   m3  | */
			/* m = | m4  m5  m6   m7  | */
			/*     | m8  m9  m10  m11 | */
			/*     | m12 m13 m14  m15 | */

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
				union
				{
					float _m15;
					uint32_t _mHint;
				};
			};
		};
	};
}

#endif

//--- End of File ---
