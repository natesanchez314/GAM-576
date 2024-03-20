//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
	// Do your magic here

	Mat3::Mat3()
		: _v0({ 0.0f, 0.0f, 0.0f }), _v1({ 0.0f, 0.0f, 0.0f }), _v2({ 0.0f, 0.0f, 0.0f }), _v3({ 0.0f, 0.0f, 0.0f })
	{ }

	Mat3::Mat3(float m0, float m1, float m2, float m4, float m5, float m6, float m8, float m9, float m10)
		: _m0(m0), _m1(m1), _m2(m2), _m3(0.0f), _m4(m4), _m5(m5), _m6(m6), _m7(0.0f), _m8(m8), _m9(m9), _m10(m10), _m11(0.0f), _m12(0.0f), _m13(0.0f), _m14(0.0f), _m15(1.0f)
	{ }

	Mat3::Mat3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11)
		: _m0(m0), _m1(m1), _m2(m2), _m3(m3), _m4(m4), _m5(m5), _m6(m6), _m7(m7), _m8(m8), _m9(m9), _m10(m10), _m11(m11), _m12(0.0f), _m13(0.0f), _m14(0.0f), _m15(1.0f)
	{ }

	Mat3::Mat3(Vec3 v0, Vec3 v1, Vec3 v2)
		: _v0(v0), _v1(v1), _v2(v2), _v3({ 0.0f, 0.0f, 0.0f })
	{ }

	Mat3::Mat3(Special type)
	{
		if (type == Special::Zero)
		{
			this->_m0 = 0.0f;
			this->_m1 = 0.0f;
			this->_m2 = 0.0f;
			this->_m3 = 0.0f;
			this->_m4 = 0.0f;
			this->_m5 = 0.0f;
			this->_m6 = 0.0f;
			this->_m7 = 0.0f;
			this->_m8 = 0.0f;
			this->_m9 = 0.0f;
			this->_m10 = 0.0f;
			this->_m11 = 0.0f;
			this->_m12 = 0.0f;
			this->_m13 = 0.0f;
			this->_m14 = 0.0f;
			this->_m15 = 0.0f;
		}
		else
		{
			this->_m0 = 1.0f;
			this->_m1 = 0.0f;
			this->_m2 = 0.0f;
			this->_m3 = 0.0f;
			this->_m4 = 0.0f;
			this->_m5 = 1.0f;
			this->_m6 = 0.0f;
			this->_m7 = 0.0f;
			this->_m8 = 0.0f;
			this->_m9 = 0.0f;
			this->_m10 = 1.0f;
			this->_m11 = 0.0f;
			this->_m12 = 0.0f;
			this->_m13 = 0.0f;
			this->_m14 = 0.0f;
			this->_m15 = 1.0f;
		}
	}

	Mat3::Mat3(const Mat3& rhs)
		: _v0(rhs._v0), _v1(rhs._v1), _v2(rhs._v2), _v3(rhs._v3)
	{ }


	Mat3::Mat3(const Mat4& rhs)
		: _v0(rhs._v0), _v1(rhs._v1), _v2(rhs._v2)
	{ }

	Mat3& Mat3::operator=(const Mat3& rhs)
	{
		if (this != &rhs)
		{
			this->_v0 = rhs._v0;
			this->_v1 = rhs._v1;
			this->_v2 = rhs._v2;
			this->_v3 = rhs._v3;
		}
		return *this;
	}

	Mat3::~Mat3()
	{ }

	bool Mat3::isEqual(const Mat3& rhs) const
	{
		return (this->_v0.isEqual(rhs._v0) && this->_v1.isEqual(rhs._v1) && this->_v2.isEqual(rhs._v2) && this->_v3.isEqual(rhs._v3));
	}

	bool Mat3::isIdentity() const
	{
		return isIdentity(MATH_TOLERANCE);
	}

	bool Mat3::isIdentity(float epsilon) const
	{
		if (Util::isOne(this->_m0, epsilon) && Util::isZero(this->_m1, epsilon) && Util::isZero(this->_m2, epsilon) && //Util::isZero(this->_m3, epsilon) &&
			Util::isZero(this->_m4, epsilon) && Util::isOne(this->_m5, epsilon) && Util::isZero(this->_m6, epsilon) && //Util::isZero(this->_m7, epsilon) &&
			Util::isZero(this->_m8, epsilon) && Util::isZero(this->_m9, epsilon) && Util::isOne(this->_m10, epsilon)) //&& Util::isZero(this->_m11, epsilon) &&
			//Util::isZero(this->_m12, epsilon) && Util::isZero(this->_m13, epsilon) && Util::isZero(this->_m14, epsilon) && Util::isOne(this->_m15, epsilon))
			return true;
		return false;
	}

	bool Mat3::isRotation() const
	{
		return isRotation(MATH_TOLERANCE);
	}

	bool Mat3::isRotation(float epsilon) const
	{
		Mat3 t = this->getT();
		Mat3 i = Mat3(*this) * t;
		return i.isIdentity(epsilon);
	}

	Mat3 Mat3::operator+(const Mat3& rhs)
	{
		return Mat3(
			this->_m0 + rhs._m0, this->_m1 + rhs._m1, this->_m2 + rhs._m2, this->_m3 + rhs._m3,
			this->_m4 + rhs._m4, this->_m5 + rhs._m5, this->_m6 + rhs._m6, this->_m7 + rhs._m7,
			this->_m8 + rhs._m8, this->_m9 + rhs._m9, this->_m10 + rhs._m10, this->_m11 + rhs._m11);
	}

	void Mat3::operator+=(const Mat3& rhs)
	{
		this->_m0 += rhs._m0;
		this->_m1 += rhs._m1;
		this->_m2 += rhs._m2;
		this->_m3 += rhs._m3;
		this->_m4 += rhs._m4;
		this->_m5 += rhs._m5;
		this->_m6 += rhs._m6;
		this->_m7 += rhs._m7;
		this->_m8 += rhs._m8;
		this->_m9 += rhs._m9;
		this->_m10 += rhs._m10;
		this->_m11 += rhs._m11;
		this->_m12 += rhs._m12;
		this->_m13 += rhs._m13;
		this->_m14 += rhs._m14;
		this->_m15 += rhs._m15;
	}

	Mat3 Mat3::operator+()
	{
		return Mat3(
			this->_m0, this->_m1, this->_m2, this->_m3,
			this->_m4, this->_m5, this->_m6, this->_m7,
			this->_m8, this->_m9, this->_m10, this->_m11);
	}

	Mat3 Mat3::operator-(const Mat3& rhs)
	{
		return Mat3(this->_m0 - rhs._m0, this->_m1 - rhs._m1, this->_m2 - rhs._m2, this->_m3 - rhs._m3,
			this->_m4 - rhs._m4, this->_m5 - rhs._m5, this->_m6 - rhs._m6, this->_m7 - rhs._m7,
			this->_m8 - rhs._m8, this->_m9 - rhs._m9, this->_m10 - rhs._m10, this->_m11 - rhs._m11);
	}

	void Mat3::operator-=(const Mat3& rhs)
	{
		this->_m0 -= rhs._m0;
		this->_m1 -= rhs._m1;
		this->_m2 -= rhs._m2;
		this->_m3 -= rhs._m3;
		this->_m4 -= rhs._m4;
		this->_m5 -= rhs._m5;
		this->_m6 -= rhs._m6;
		this->_m7 -= rhs._m7;
		this->_m8 -= rhs._m8;
		this->_m9 -= rhs._m9;
		this->_m10 -= rhs._m10;
		this->_m11 -= rhs._m11;
	}

	Mat3 Mat3::operator-()
	{
		return Mat3(
			-this->_m0, -this->_m1, -this->_m2, -this->_m3,
			-this->_m4, -this->_m5, -this->_m6, -this->_m7,
			-this->_m8, -this->_m9, -this->_m10, -this->_m11);
	}

	Mat3 Mat3::operator*(const Mat3& rhs)
	{
		return Mat3(
			(this->_m0 * rhs._m0) + (this->_m1 * rhs._m4) + (this->_m2 * rhs._m8),// + (this->_m3 * rhs._m12),
			(this->_m0 * rhs._m1) + (this->_m1 * rhs._m5) + (this->_m2 * rhs._m9),// + (this->_m3 * rhs._m13),
			(this->_m0 * rhs._m2) + (this->_m1 * rhs._m6) + (this->_m2 * rhs._m10),// + (this->_m3 * rhs._m14),
			//(this->_m0 * rhs._m3) + (this->_m1 * rhs._m7) + (this->_m2 * rhs._m11),// + (this->_m3 * rhs._m15),

			(this->_m4 * rhs._m0) + (this->_m5 * rhs._m4) + (this->_m6 * rhs._m8),// + (this->_m7 * rhs._m12),
			(this->_m4 * rhs._m1) + (this->_m5 * rhs._m5) + (this->_m6 * rhs._m9),// + (this->_m7 * rhs._m13),
			(this->_m4 * rhs._m2) + (this->_m5 * rhs._m6) + (this->_m6 * rhs._m10),// + (this->_m7 * rhs._m14),
			//(this->_m4 * rhs._m3) + (this->_m5 * rhs._m7) + (this->_m6 * rhs._m11),// + (this->_m7 * rhs._m15),

			(this->_m8 * rhs._m0) + (this->_m9 * rhs._m4) + (this->_m10 * rhs._m8),// + (this->_m11 * rhs._m12),
			(this->_m8 * rhs._m1) + (this->_m9 * rhs._m5) + (this->_m10 * rhs._m9),// + (this->_m11 * rhs._m13),
			(this->_m8 * rhs._m2) + (this->_m9 * rhs._m6) + (this->_m10 * rhs._m10));// + (this->_m11 * rhs._m14),
			//(this->_m8 * rhs._m3) + (this->_m9 * rhs._m7) + (this->_m10 * rhs._m11));// + (this->_m11 * rhs._m15));
	}

	void Mat3::operator*=(const Mat3& rhs)
	{
		*this = *this * rhs;
	}

	Mat3 Mat3::operator*(float rhs)
	{
		return Mat3(this->_m0 * rhs, this->_m1 * rhs, this->_m2 * rhs, this->_m3 * rhs,
			this->_m4 * rhs, this->_m5 * rhs, this->_m6 * rhs, this->_m7 * rhs,
			this->_m8 * rhs, this->_m9 * rhs, this->_m10 * rhs, this->_m11 * rhs);
	}

	void Mat3::operator*=(float rhs)
	{
		this->_m0 *= rhs;
		this->_m1 *= rhs;
		this->_m2 *= rhs;
		this->_m3 *= rhs;
		this->_m4 *= rhs;
		this->_m5 *= rhs;
		this->_m6 *= rhs;
		this->_m7 *= rhs;
		this->_m8 *= rhs;
		this->_m9 *= rhs;
		this->_m10 *= rhs;
		this->_m11 *= rhs;
		this->_m12 *= rhs;
		this->_m13 *= rhs;
		this->_m14 *= rhs;
		this->_m15 *= rhs;
	}

	float Mat3::det() const
	{
		return (
			this->_m0 * (this->_m5 * this->_m10 - this->_m6 * this->_m9) -
			this->_m1 * (this->_m4 * this->_m10 - this->_m6 * this->_m8) +
			this->_m2 * (this->_m4 * this->_m9 - this->_m5 * this->_m8));
	}

	void Mat3::T()
	{
		float tmp = this->_m1;
		this->_m1 = this->_m4;
		this->_m4 = tmp;
		tmp = this->_m2;
		this->_m2 = this->_m8;
		this->_m8 = tmp;
		tmp = this->_m3;
		this->_m3 = this->_m12;
		this->_m12 = tmp;
		tmp = this->_m6;
		this->_m6 = this->_m9;
		this->_m9 = tmp;
		tmp = this->_m7;
		this->_m7 = this->_m13;
		this->_m13 = tmp;
		tmp = this->_m11;
		this->_m11 = this->_m14;
		this->_m14 = tmp;
	}

	Mat3 Mat3::getT() const
	{
		return Mat3(
			this->_m0, this->_m4, this->_m8, this->_m12,
			this->_m1, this->_m5, this->_m9, this->_m13,
			this->_m2, this->_m6, this->_m10, this->_m14);
	}

	void Mat3::inv()
	{
		*this = this->getInv();
	}

	Mat3 Mat3::getInv() const
	{
		Mat3 m = Mat3(
			(this->_m5 * this->_m10 - this->_m6 * this->_m9),
			(this->_m2 * this->_m9 - this->_m1 * this->_m10),
			(this->_m1 * this->_m6 - this->_m2 * this->_m5),
			this->_m3,
			(this->_m6 * this->_m8 - this->_m4 * this->_m10),
			(this->_m0 * this->_m10 - this->_m2 * this->_m8),
			(this->_m2 * this->_m4 - this->_m0 * this->_m6),
			this->_m7,
			(this->_m4 * this->_m9 - this->_m5 * this->_m8),
			(this->_m1 * this->_m8 - this->_m0 * this->_m9),
			(this->_m0 * this->_m5 - this->_m1 * this->_m4),
			this->_m11
		);

		return ((1.0f / this->det()) * m);
	}

	void Mat3::set(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d)
	{
		this->_v0 = a;
		this->_v1 = b;
		this->_v2 = c;
		this->_v3 = d;
	}

	void Mat3::set(enum Special type)
	{
		if (type == Special::Zero)
		{
			this->_m0 = 0.0f;
			this->_m1 = 0.0f;
			this->_m2 = 0.0f;
			this->_m3 = 0.0f;
			this->_m4 = 0.0f;
			this->_m5 = 0.0f;
			this->_m6 = 0.0f;
			this->_m7 = 0.0f;
			this->_m8 = 0.0f;
			this->_m9 = 0.0f;
			this->_m10 = 0.0f;
			this->_m11 = 0.0f;
			this->_m12 = 0.0f;
			this->_m13 = 0.0f;
			this->_m14 = 0.0f;
			this->_m15 = 0.0f;
		}
		else
		{
			this->_m0 = 1.0f;
			this->_m1 = 0.0f;
			this->_m2 = 0.0f;
			this->_m3 = 0.0f;
			this->_m4 = 0.0f;
			this->_m5 = 1.0f;
			this->_m6 = 0.0f;
			this->_m7 = 0.0f;
			this->_m8 = 0.0f;
			this->_m9 = 0.0f;
			this->_m10 = 1.0f;
			this->_m11 = 0.0f;
			this->_m12 = 0.0f;
			this->_m13 = 0.0f;
			this->_m14 = 0.0f;
			this->_m15 = 1.0f;
		}
	}

	void Mat3::set(const Row row, const Vec3& Vec3)
	{
		if (row == Row::i0)
			this->_v0 = Vec3;
		else if (row == Row::i1)
			this->_v1 = Vec3;
		else if (row == Row::i2)
			this->_v2 = Vec3;
		else
			this->_v3 = Vec3;
	}

	Vec3& Mat3::get(const Row row) const
	{
		if (row == Row::i0)
			return (Vec3&)this->_v0;
		else if (row == Row::i1)
			return (Vec3&)this->_v1;
		else if (row == Row::i2)
			return (Vec3&)this->_v2;
		else
			return (Vec3&)this->_v3;
	}

	// Getters
	float Mat3::m0(void) const { return this->_m0; }
	float Mat3::m1(void) const { return this->_m1; }
	float Mat3::m2(void) const { return this->_m2; }
	float Mat3::m3(void) const { return this->_m3; }
	float Mat3::m4(void) const { return this->_m4; }
	float Mat3::m5(void) const { return this->_m5; }
	float Mat3::m6(void) const { return this->_m6; }
	float Mat3::m7(void) const { return this->_m7; }
	float Mat3::m8(void) const { return this->_m8; }
	float Mat3::m9(void) const { return this->_m9; }
	float Mat3::m10(void) const { return this->_m10; }
	float Mat3::m11(void) const { return this->_m11; }
	float Mat3::m12(void) const { return this->_m12; }
	float Mat3::m13(void) const { return this->_m13; }
	float Mat3::m14(void) const { return this->_m14; }
	float Mat3::m15(void) const { return this->_m15; }
	float Mat3::operator[](const m0_enum) const { return this->_m0; }
	float Mat3::operator[](const m1_enum) const { return this->_m1; }
	float Mat3::operator[](const m2_enum) const { return this->_m2; }
	float Mat3::operator[](const m3_enum) const { return this->_m3; }
	float Mat3::operator[](const m4_enum) const { return this->_m4; }
	float Mat3::operator[](const m5_enum) const { return this->_m5; }
	float Mat3::operator[](const m6_enum) const { return this->_m6; }
	float Mat3::operator[](const m7_enum) const { return this->_m7; }
	float Mat3::operator[](const m8_enum) const { return this->_m8; }
	float Mat3::operator[](const m9_enum) const { return this->_m9; }
	float Mat3::operator[](const m10_enum) const { return this->_m10; }
	float Mat3::operator[](const m11_enum) const { return this->_m11; }
	float Mat3::operator[](const m12_enum) const { return this->_m12; }
	float Mat3::operator[](const m13_enum) const { return this->_m13; }
	float Mat3::operator[](const m14_enum) const { return this->_m14; }
	float Mat3::operator[](const m15_enum) const { return this->_m15; }

	// Setters
	float& Mat3::m0(void) { return this->_m0; }
	float& Mat3::m1(void) { return this->_m1; }
	float& Mat3::m2(void) { return this->_m2; }
	float& Mat3::m3(void) { return this->_m3; }
	float& Mat3::m4(void) { return this->_m4; }
	float& Mat3::m5(void) { return this->_m5; }
	float& Mat3::m6(void) { return this->_m6; }
	float& Mat3::m7(void) { return this->_m7; }
	float& Mat3::m8(void) { return this->_m8; }
	float& Mat3::m9(void) { return this->_m9; }
	float& Mat3::m10(void) { return this->_m10; }
	float& Mat3::m11(void) { return this->_m11; }
	float& Mat3::m12(void) { return this->_m12; }
	float& Mat3::m13(void) { return this->_m13; }
	float& Mat3::m14(void) { return this->_m14; }
	float& Mat3::m15(void) { return this->_m15; }
	void Mat3::m0(float m0) { this->_m0 = m0; }
	void Mat3::m1(float m1) { this->_m1 = m1; }
	void Mat3::m2(float m2) { this->_m2 = m2; }
	void Mat3::m3(float m3) { this->_m3 = m3; }
	void Mat3::m4(float m4) { this->_m4 = m4; }
	void Mat3::m5(float m5) { this->_m5 = m5; }
	void Mat3::m6(float m6) { this->_m6 = m6; }
	void Mat3::m7(float m7) { this->_m7 = m7; }
	void Mat3::m8(float m8) { this->_m8 = m8; }
	void Mat3::m9(float m9) { this->_m9 = m9; }
	void Mat3::m10(float m10) { this->_m10 = m10; }
	void Mat3::m11(float m11) { this->_m11 = m11; }
	void Mat3::m12(float m12) { this->_m12 = m12; }
	void Mat3::m13(float m13) { this->_m13 = m13; }
	void Mat3::m14(float m14) { this->_m14 = m14; }
	void Mat3::m15(float m15) { this->_m15 = m15; }
	float& Mat3::operator[](const m0_enum) { return this->_m0; }
	float& Mat3::operator[](const m1_enum) { return this->_m1; }
	float& Mat3::operator[](const m2_enum) { return this->_m2; }
	float& Mat3::operator[](const m3_enum) { return this->_m3; }
	float& Mat3::operator[](const m4_enum) { return this->_m4; }
	float& Mat3::operator[](const m5_enum) { return this->_m5; }
	float& Mat3::operator[](const m6_enum) { return this->_m6; }
	float& Mat3::operator[](const m7_enum) { return this->_m7; }
	float& Mat3::operator[](const m8_enum) { return this->_m8; }
	float& Mat3::operator[](const m9_enum) { return this->_m9; }
	float& Mat3::operator[](const m10_enum) { return this->_m10; }
	float& Mat3::operator[](const m11_enum) { return this->_m11; }
	float& Mat3::operator[](const m12_enum) { return this->_m12; }
	float& Mat3::operator[](const m13_enum) { return this->_m13; }
	float& Mat3::operator[](const m14_enum) { return this->_m14; }
	float& Mat3::operator[](const m15_enum) { return this->_m15; }

	void Mat3::set(Vec3& a, Vec3& b, Vec3& c)
	{
		this->_v0 = a;
		this->_v1 = b;
		this->_v2 = c;
	}

	void Mat3::Print(const char *pName) const
	{
		Debug::Print(pName, *this);
	};

}

// ---  End of File ---
