//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

#include "Mat4.h"
#include "Debug.h"

//------------------------------------------------------------------------
// 
//  This class contains functions and data structure for a 4-dimensional
//  Quaternions.  The quaternions are internally stored interms of the
//  imaginary components (x,y,z) and the real components (real).
// 
//  In the Math library, quaternions can be thought of as "rotational"
//  matrices, everything that you can represent with rotational matrices
//  you can use with quaternions.  Such as quaternion concatenation,
//  inverses, transpose, normalize, multiplying with matrices, and with
//  vectors.
// 
//------------------------------------------------------------------------
namespace Azul
{
	class Quat final : public Align16
	{
	public:
		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Special
		{
			Zero,
			Identity
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

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

	public:

        // add magic

		Quat();
		Quat(float x, float y, float z, float w);
		Quat(const Vec3& v);
		Quat(const Vec3& v, float real);
		Quat(const Vec4& v);
		Quat(const Mat4& m);
		Quat(enum Rot1 axis, float theta);
		Quat(enum Special type);
		Quat(enum Rot, const Vec3& axis, float angle);
		Quat(Orient orient, const Vec3& dof, const Vec3& up);
		Quat(Rot3 combo, float x, float y, float z);
		Quat(const Quat& other);
		Quat& operator=(const Quat& other);
		~Quat();

		bool isEqual(const Quat& rhs) const;
		bool isEqual(const Quat& rhs, float tolerance) const;
		bool isNegEqual(const Quat& rhs) const;
		bool isNegEqual(const Quat& rhs, float tolerance) const;
		bool isEquivalent(const Quat& rhs) const;
		bool isEquivalent(const Quat& rhs, float tolerance) const;
		bool isConjugateEqual(const Quat& rhs) const;
		bool isConjugateEqual(const Quat& rhs, float tolerance) const;
		bool isIdentity() const;
		bool isIdentity(float tolerance) const;
		bool isNormalized() const;
		bool isNormalized(float tolerance) const;
		bool isZero() const;
		bool isZero(float tolerance) const;

		Quat operator+(const Quat& rhs);
		void operator+=(const Quat& rhs);
		Quat operator+(const float rhs);
		void operator+=(const float rhs);
		Quat operator+();
		friend Quat operator+(const float lhs, const Quat& rhs)
		{
			float x = lhs + rhs.qx();
			float y = lhs + rhs.qy();
			float z = lhs + rhs.qz();
			float w = lhs + rhs.real();
			return Quat(x, y, z, w);
		}
		Quat operator-(const Quat& rhs);
		void operator-=(const Quat& rhs);
		Quat operator-(const float rhs);
		void operator-=(const float &rhs);
		Quat operator-();
		friend Quat operator-(const float lhs, const Quat& rhs)
		{
			float x = lhs - rhs.qx();
			float y = lhs - rhs.qy();
			float z = lhs - rhs.qz();
			float w = lhs - rhs.real();
			return Quat(x, y, z, w);
		}
		Quat operator*(const Quat& rhs);
		void operator*=(const Quat& rhs);
		Mat4 operator*(const Mat4& rhs);
		void operator*=(const Mat4& rhs);
		Quat operator*(const float rhs);
		void operator*=(const float rhs);
		friend Quat operator*(const float lhs, const Quat& rhs)
		{
			return Quat(
				lhs * rhs[x],
				lhs * rhs[y],
				lhs * rhs[z],
				lhs * rhs[w]
			);
		}
		friend Quat operator*(const Quat& lhs, const float rhs)
		{
			return Quat(
				lhs[x] * rhs,
				lhs[y] * rhs,
				lhs[z] * rhs,
				lhs[w] * rhs
			);
		}
		Quat operator/(const Quat& rhs);
		void operator/=(const Quat& rhs);
		Quat operator/(const float rhs);
		void operator/=(const float rhs);
		friend Quat operator/(const float lhs, const Quat& rhs)
		{
			return Quat(
				lhs / rhs[x],
				lhs / rhs[y],
				lhs / rhs[z],
				lhs / rhs[w]
			);
		}
		void Lqcvq(const Vec3& vIn, Vec3& vOut) const;
		void Lqvqc(const Vec3& vIn, Vec3& vOut) const;

		Quat getConj() const;
		void conj();
		Quat getT() const;
		void T();
		float mag() const;
		float magSquared() const;
		float invMag() const;
		Quat getNorm() const;
		Quat norm();
		Quat getInv() const;
		void inv();
		float dot(const Quat& q) const;
		float getAngle() const;
		void getAxis(Vec3& v) const;

		// Setters
		float& qx();
		float& qy();
		float& qz();
		float& real();
		void qx(float x);
		void qy(float y);
		void qz(float z);
		void real(float w);
		float& operator[](const x_enum);
		float& operator[](const y_enum);
		float& operator[](const z_enum);
		float& operator[](const w_enum);
		void set(float x, float y, float z);
		void set(float x, float y, float z, float w);
		void setVec3(const Vec3& v);
		void set(const Vec3& v, float real);
		void set(const Vec4& v);
		void set(const Mat4& m);
		void set(const Quat& q);
		void set(enum Rot1 axis, float theta);
		void set(enum Special type);
		void set(enum Rot, const Vec3& axis, float angle);
		void set(Orient orient, const Vec3& dof, const Vec3& up);
		void set(Rot3 combo, float x, float y, float z);

		// Getters
		float qx() const;
		float qy() const;
		float qz() const;
		float real() const;
		Vec3 getVec3() const;
		void getVec3(Vec3& v);
		Vec4 getVec4() const;
		void getVec4(Vec4& v);
		float operator[](const x_enum) const;
		float operator[](const y_enum) const;
		float operator[](const z_enum) const;
		float operator[](const w_enum) const;

	private:
		friend Vec4;
		friend Mat4;

		// anonymous union
		union
		{
			__m128	_mq;

			// anonymous struct
			struct
			{
				float _qx;
				float _qy;
				float _qz;
				float _qw;
			};

			struct
			{
				Vec3  _qV3;
			};

			struct
			{
				Vec4 _qV4;
			};
		};

	};
}

#endif 

//--- End of File ---
