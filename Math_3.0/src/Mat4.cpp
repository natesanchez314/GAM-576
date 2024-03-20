//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
	// Do your magic here

	Mat4::Mat4()
		: _v0({ 0.0f, 0.0f, 0.0f, 0.0f }), _v1({ 0.0f, 0.0f, 0.0f, 0.0f }), _v2({ 0.0f, 0.0f, 0.0f, 0.0f }), _v3({ 0.0f, 0.0f, 0.0f, 0.0f })
	{
		this->SetHintGeneral();
	}

	Mat4::Mat4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15)
		: _m0(m0), _m1(m1), _m2(m2), _m3(m3), _m4(m4), _m5(m5), _m6(m6), _m7(m7), _m8(m8), _m9(m9), _m10(m10), _m11(m11), _m12(m12), _m13(m13), _m14(m14), _m15(m15)
	{
		this->SetHintGeneral();
	}

	Mat4::Mat4(Vec4 v0, Vec4 v1, Vec4 v2, Vec4 v3)
		: _v0(v0), _v1(v1), _v2(v2), _v3(v3)
	{
		this->SetHintGeneral();
	}

	Mat4::Mat4(const Quat& q)
	{
		float XxX = q[x] * q[x];
		float XxY = q[x] * q[y];
		float XxZ = q[x] * q[z];
		float XxW = q[x] * q[w];
		float YxY = q[y] * q[y];
		float YxZ = q[y] * q[z];
		float YxW = q[y] * q[w];
		float ZxZ = q[z] * q[z];
		float ZxW = q[z] * q[w];

		this->_m0 = 1.0f - (2.0f * (YxY + ZxZ));
		this->_m1 = 2.0f * (XxY + ZxW);
		this->_m2 = 2.0f * (XxZ - YxW);
		this->_m3 = 0.0f;

		this->_m4 = 2.0f * (XxY - ZxW);
		this->_m5 = 1.0f - (2.0f * (XxX + ZxZ));
		this->_m6 = 2.0f * (YxZ + XxW);
		this->_m7 = 0.0f;

		this->_m8 = 2.0f * (XxZ + YxW);
		this->_m9 = 2.0f * (YxZ - XxW);
		this->_m10 = 1.0f - (2.0f * (XxX + YxY));
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	Mat4::Mat4(Special type)
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
		this->SetHintGeneral();
	}

	Mat4::Mat4(enum Rot, const Vec4& v, float angle)
	{
		const float angle_a = 0.5f * angle;
		float cos_a;
		float sin_a;

		cos_a = cosf(angle_a);
		sin_a = sinf(angle_a);

		Vec4 qV = v;
		qV.norm();

		qV *= sin_a;

		Vec4 Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];
		Q[w] = cos_a;

		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_v0.set(1.0f - (yy + zz), xy + wz, xz - wy, 0.0f);
		this->_v1.set(xy - wz, 1.0f - (xx + zz), yz + wx, 0.0f);
		this->_v2.set(xz + wy, yz - wx, 1.0f - (xx + yy), 0.0f);
		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

		SetHintRot();
	}

	Mat4::Mat4(enum Trans, float x, float y, float z)
		: _m0(1.0f), _m1(0.0f), _m2(0.0f), _m3(0.0f),
		_m4(0.0f), _m5(1.0f), _m6(0.0f), _m7(0.0f),
		_m8(0.0f), _m9(0.0f), _m10(1.0f), _m11(0.0f),
		_m12(x), _m13(y), _m14(z), _m15(1.0f)
	{
		SetHintTrans();
	}

	Mat4::Mat4(enum Trans, const Vec4& Vec4)
		: _m0(1.0f), _m1(0.0f), _m2(0.0f), _m3(0.0f),
		_m4(0.0f), _m5(1.0f), _m6(0.0f), _m7(0.0f),
		_m8(0.0f), _m9(0.0f), _m10(1.0f), _m11(0.0f),
		_m12(Vec4[x]), _m13(Vec4[y]), _m14(Vec4[z]), _m15(1.0f)
	{
		SetHintTrans();
	}

	Mat4::Mat4(enum Scale, float x, float y, float z)
		: _m0(x), _m1(0.0f), _m2(0.0f), _m3(0.0f),
		_m4(0.0f), _m5(y), _m6(0.0f), _m7(0.0f),
		_m8(0.0f), _m9(0.0f), _m10(z), _m11(0.0f),
		_m12(0.0f), _m13(0.0f), _m14(0.0f), _m15(1.0f)
	{
		SetHintScale();
	}

	Mat4::Mat4(enum Scale, const Vec4& Vec4)
		: _m0(Vec4[x]), _m1(0.0f), _m2(0.0f), _m3(0.0f),
		_m4(0.0f), _m5(Vec4[y]), _m6(0.0f), _m7(0.0f),
		_m8(0.0f), _m9(0.0f), _m10(Vec4[z]), _m11(0.0f),
		_m12(0.0f), _m13(0.0f), _m14(0.0f), _m15(1.0f)
	{
		SetHintScale();
	}

	Mat4::Mat4(Rot1 axis, float theta)
	{
		float sin = Trig::sin(theta);
		float cos = Trig::cos(theta);
		if (axis == Rot1::X)
		{
			this->_v0 = Vec4(1.0f, 0.0f, 0.0f, 0.0f); //0  1  2  3
			this->_v1 = Vec4(0.0f, cos, sin, 0.0f);   //4  5  6  7
			this->_v2 = Vec4(0.0f, -sin, cos, 0.0f);  //8  9  10 11
			this->_v3 = Vec4(0.0f, 0.0f, 0.0f, 1.0f); //12 13 14 15
		}
		else if (axis == Rot1::Y)
		{
			this->_v0 = Vec4(cos, 0.0f, -sin, 0.0f);  //0  1  2  3
			this->_v1 = Vec4(0.0f, 1.0f, 0.0f, 0.0f); //4  5  6  7
			this->_v2 = Vec4(sin, 0.0f, cos, 0.0f);	  //8  9  10 11
			this->_v3 = Vec4(0.0f, 0.0f, 0.0f, 1.0f); //12 13 14 15
		}
		else
		{
			this->_v0 = Vec4(cos, sin, 0.0f, 0.0f);	  //0  1  2  3
			this->_v1 = Vec4(-sin, cos, 0.0f, 0.0f);  //4  5  6  7
			this->_v2 = Vec4(0.0f, 0.0f, 1.0f, 0.0f); //8  9  10 11
			this->_v3 = Vec4(0.0f, 0.0f, 0.0f, 1.0f); //12 13 14 15
		}

		this->SetHintRot();
	}

	Mat4::Mat4(Orient orient, const Vec3& dof, const Vec3& up)
	{
		Vec3 a = up;
		Vec3 b = dof;
		Vec3 c = dof;

		a = a.cross(dof);
		b = b.cross(a);

		a.norm();
		b.norm();
		c.norm();

		if (orient == Orient::LocalToWorld)
		{
			this->_v0.set(a[x], a[y], a[z], 0.0f);
			this->_v1.set(b[x], b[y], b[z], 0.0f);
			this->_v2.set(c[x], c[y], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			this->_v0.set(a[x], b[x], c[x], 0.0f);
			this->_v1.set(a[y], b[y], c[y], 0.0f);
			this->_v2.set(a[z], b[z], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		this->SetHintRot();
	}

	Mat4::Mat4(Orient orient, const Vec4& dof, const Vec4& up)
	{
		Vec4 a = up;
		Vec4 b = dof;
		Vec4 c = dof;

		a = a.cross(dof);
		b = b.cross(a);

		a.norm();
		b.norm();
		c.norm();

		if (orient == Orient::LocalToWorld)
		{
			this->_v0.set(a[x], a[y], a[z], 0.0f);
			this->_v1.set(b[x], b[y], b[z], 0.0f);
			this->_v2.set(c[x], c[y], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			this->_v0.set(a[x], b[x], c[x], 0.0f);
			this->_v1.set(a[y], b[y], c[y], 0.0f);
			this->_v2.set(a[z], b[z], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		this->SetHintRot();
	}

	Mat4::Mat4(Rot3 combo, float x, float y, float z)
	{
		this->set(combo, x, y, z);
		this->SetHintRot();
	}

	Mat4::Mat4(const Mat4& rhs)
		: _v0(rhs._v0), _v1(rhs._v1), _v2(rhs._v2), _v3(rhs._v3)
	{
		this->SetAndCopyHint(rhs.GetHint());
	}

	Mat4& Mat4::operator=(const Mat4& rhs)
	{
		if (this != &rhs)
		{
			this->_v0 = rhs._v0;
			this->_v1 = rhs._v1;
			this->_v2 = rhs._v2;
			this->_v3 = rhs._v3;
		}

		this->SetAndCopyHint(rhs.GetHint());

		return *this;
	}

	Mat4::~Mat4()
	{ }

	bool Mat4::isEqual(const Mat4& rhs) const
	{
		return (this->_v0.isEqual(rhs._v0) && this->_v1.isEqual(rhs._v1) && this->_v2.isEqual(rhs._v2) && this->_v3.isEqual(rhs._v3));
	}

	bool Mat4::isIdentity() const
	{
		return isIdentity(MATH_TOLERANCE);
	}

	bool Mat4::isIdentity(float epsilon) const
	{
		if (Util::isOne(this->_m0, epsilon) && Util::isZero(this->_m1, epsilon) && Util::isZero(this->_m2, epsilon) && Util::isZero(this->_m3, epsilon) &&
			Util::isZero(this->_m4, epsilon) && Util::isOne(this->_m5, epsilon) && Util::isZero(this->_m6, epsilon) && Util::isZero(this->_m7, epsilon) &&
			Util::isZero(this->_m8, epsilon) && Util::isZero(this->_m9, epsilon) && Util::isOne(this->_m10, epsilon) && Util::isZero(this->_m11, epsilon) &&
			Util::isZero(this->_m12, epsilon) && Util::isZero(this->_m13, epsilon) && Util::isZero(this->_m14, epsilon) && Util::isOne(this->_m15, epsilon))
			return true;
		return false;
	}

	bool Mat4::isRotation() const
	{
		return isRotation(MATH_TOLERANCE);
	}

	bool Mat4::isRotation(float epsilon) const
	{
		Mat4 t = this->getT();
		Mat4 i = Mat4(*this) * t;
		return i.isIdentity(epsilon);
	}

	bool Mat4::privHasHint() const
	{
		if (this->_mHint != 0x0)
			return false;
		return true;
	}

	Mat4 Mat4::operator+(const Mat4& rhs)
	{
		return Mat4(
			this->_m0 + rhs._m0, this->_m1 + rhs._m1, this->_m2 + rhs._m2, this->_m3 + rhs._m3,
			this->_m4 + rhs._m4, this->_m5 + rhs._m5, this->_m6 + rhs._m6, this->_m7 + rhs._m7,
			this->_m8 + rhs._m8, this->_m9 + rhs._m9, this->_m10 + rhs._m10, this->_m11 + rhs._m11,
			this->_m12 + rhs._m12, this->_m13 + rhs._m13, this->_m14 + rhs._m14, this->_m15 + rhs._m15);
	}

	void Mat4::operator+=(const Mat4& rhs)
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

	Mat4 Mat4::operator+()
	{
		return Mat4(
			this->_m0, this->_m1, this->_m2, this->_m3,
			this->_m4, this->_m5, this->_m6, this->_m7,
			this->_m8, this->_m9, this->_m10, this->_m11,
			this->_m12, this->_m13, this->_m14, this->_m15);
	}

	Mat4 Mat4::operator-(const Mat4& rhs)
	{
		return Mat4(this->_m0 - rhs._m0, this->_m1 - rhs._m1, this->_m2 - rhs._m2, this->_m3 - rhs._m3,
			this->_m4 - rhs._m4, this->_m5 - rhs._m5, this->_m6 - rhs._m6, this->_m7 - rhs._m7,
			this->_m8 - rhs._m8, this->_m9 - rhs._m9, this->_m10 - rhs._m10, this->_m11 - rhs._m11,
			this->_m12 - rhs._m12, this->_m13 - rhs._m13, this->_m14 - rhs._m14, this->_m15 - rhs._m15);
	}

	void Mat4::operator-=(const Mat4& rhs)
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
		this->_m12 -= rhs._m12;
		this->_m13 -= rhs._m13;
		this->_m14 -= rhs._m14;
		this->_m15 -= rhs._m15;
	}

	Mat4 Mat4::operator-()
	{
		return Mat4(
			-this->_m0, -this->_m1, -this->_m2, -this->_m3,
			-this->_m4, -this->_m5, -this->_m6, -this->_m7,
			-this->_m8, -this->_m9, -this->_m10, -this->_m11,
			-this->_m12, -this->_m13, -this->_m14, -this->_m15);
	}

	Mat4 Mat4::operator*(const Mat4& rhs)
	{
		Mat4 m = Mat4(
			(this->_m0 * rhs._m0) + (this->_m1 * rhs._m4) + (this->_m2 * rhs._m8) + (this->_m3 * rhs._m12),
			(this->_m0 * rhs._m1) + (this->_m1 * rhs._m5) + (this->_m2 * rhs._m9) + (this->_m3 * rhs._m13),
			(this->_m0 * rhs._m2) + (this->_m1 * rhs._m6) + (this->_m2 * rhs._m10) + (this->_m3 * rhs._m14),
			(this->_m0 * rhs._m3) + (this->_m1 * rhs._m7) + (this->_m2 * rhs._m11) + (this->_m3 * rhs._m15),

			(this->_m4 * rhs._m0) + (this->_m5 * rhs._m4) + (this->_m6 * rhs._m8) + (this->_m7 * rhs._m12),
			(this->_m4 * rhs._m1) + (this->_m5 * rhs._m5) + (this->_m6 * rhs._m9) + (this->_m7 * rhs._m13),
			(this->_m4 * rhs._m2) + (this->_m5 * rhs._m6) + (this->_m6 * rhs._m10) + (this->_m7 * rhs._m14),
			(this->_m4 * rhs._m3) + (this->_m5 * rhs._m7) + (this->_m6 * rhs._m11) + (this->_m7 * rhs._m15),

			(this->_m8 * rhs._m0) + (this->_m9 * rhs._m4) + (this->_m10 * rhs._m8) + (this->_m11 * rhs._m12),
			(this->_m8 * rhs._m1) + (this->_m9 * rhs._m5) + (this->_m10 * rhs._m9) + (this->_m11 * rhs._m13),
			(this->_m8 * rhs._m2) + (this->_m9 * rhs._m6) + (this->_m10 * rhs._m10) + (this->_m11 * rhs._m14),
			(this->_m8 * rhs._m3) + (this->_m9 * rhs._m7) + (this->_m10 * rhs._m11) + (this->_m11 * rhs._m15),

			(this->_m12 * rhs._m0) + (this->_m13 * rhs._m4) + (this->_m14 * rhs._m8) + (this->_m15 * rhs._m12),
			(this->_m12 * rhs._m1) + (this->_m13 * rhs._m5) + (this->_m14 * rhs._m9) + (this->_m15 * rhs._m13),
			(this->_m12 * rhs._m2) + (this->_m13 * rhs._m6) + (this->_m14 * rhs._m10) + (this->_m15 * rhs._m14),
			(this->_m12 * rhs._m3) + (this->_m13 * rhs._m7) + (this->_m14 * rhs._m11) + (this->_m15 * rhs._m15));
		m.SetAndCombineHints(this->GetHint(), rhs.GetHint());
		return m;
	}

	void Mat4::operator*=(const Mat4& rhs)
	{
		*this = *this * rhs;
		this->SetAndCombineHints(this->GetHint(), rhs.GetHint());
	}

	Mat4 Mat4::operator*(float rhs)
	{
		return Mat4(this->_m0 * rhs, this->_m1 * rhs, this->_m2 * rhs, this->_m3 * rhs,
			this->_m4 * rhs, this->_m5 * rhs, this->_m6 * rhs, this->_m7 * rhs,
			this->_m8 * rhs, this->_m9 * rhs, this->_m10 * rhs, this->_m11 * rhs,
			this->_m12 * rhs, this->_m13 * rhs, this->_m14 * rhs, this->_m15 * rhs);
	}

	void Mat4::operator*=(float rhs)
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

	Mat4 Mat4::operator*(const Quat& rhs)
	{
		return *this * Mat4(rhs);
	}

	void Mat4::operator*=(const Quat& rhs)
	{
		*this *= Mat4(rhs);
	}

	float Mat4::det() const
	{
		return (
			this->_m0 * (this->_m5 * (this->_m10 * this->_m15 - this->_m11 * this->_m14) - this->_m6 * (this->_m9 * this->_m15 - this->_m11 * this->_m13) + this->_m7 * (this->_m9 * this->_m14 - this->_m10 * this->_m13)) -
			this->_m1 * (this->_m4 * (this->_m10 * this->_m15 - this->_m11 * this->_m14) - this->_m6 * (this->_m8 * this->_m15 - this->_m11 * this->_m12) + this->_m7 * (this->_m8 * this->_m14 - this->_m10 * this->_m12)) +
			this->_m2 * (this->_m4 * (this->_m9 * this->_m15 - this->_m11 * this->_m13) - this->_m5 * (this->_m8 * this->_m15 - this->_m11 * this->_m12) + this->_m7 * (this->_m8 * this->_m13 - this->_m9 * this->_m12)) -
			this->_m3 * (this->_m4 * (this->_m9 * this->_m14 - this->_m10 * this->_m13) - this->_m5 * (this->_m8 * this->_m14 - this->_m10 * this->_m12) + this->_m6 * (this->_m8 * this->_m13 - this->_m9 * this->_m12)));
	}

	void Mat4::T()
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

	Mat4 Mat4::getT() const
	{
		return Mat4(
			this->_m0, this->_m4, this->_m8, this->_m12,
			this->_m1, this->_m5, this->_m9, this->_m13,
			this->_m2, this->_m6, this->_m10, this->_m14,
			this->_m3, this->_m7, this->_m11, this->_m15);
	}

	void Mat4::inv()
	{
		*this = this->getInv();
	}

	Mat4 Mat4::getInv() const
	{
		Mat4 m;

		switch (GetHint())
		{
			case Hint::Generalize:
			{
				m._m0 = (_m5 * _m10 * _m15) + (_m6 * _m11 * _m13) + (_m7 * _m9 * _m14) - (_m5 * _m11 * _m14) - (_m6 * _m9 * _m15) - (_m7 * _m10 * _m13);
				m._m1 = (_m1 * _m11 * _m14) + (_m2 * _m9 * _m15) + (_m3 * _m10 * _m13) - (_m1 * _m10 * _m15) - (_m2 * _m11 * _m13) - (_m3 * _m9 * _m14);
				m._m2 = (_m1 * _m6 * _m15) + (_m2 * _m7 * _m13) + (_m3 * _m5 * _m14) - (_m1 * _m7 * _m14) - (_m2 * _m5 * _m15) - (_m3 * _m6 * _m13);
				m._m3 = (_m1 * _m7 * _m10) + (_m2 * _m5 * _m11) + (_m3 * _m6 * _m9) - (_m1 * _m6 * _m11) - (_m2 * _m7 * _m9) - (_m3 * _m5 * _m10);
				m._m4 = (_m4 * _m11 * _m14) + (_m6 * _m8 * _m15) + (_m7 * _m10 * _m12) - (_m4 * _m10 * _m15) - (_m6 * _m11 * _m12) - (_m7 * _m8 * _m14);
				m._m5 = (_m0 * _m10 * _m15) + (_m2 * _m11 * _m12) + (_m3 * _m8 * _m14) - (_m0 * _m11 * _m14) - (_m2 * _m8 * _m15) - (_m3 * _m10 * _m12);
				m._m6 = (_m0 * _m7 * _m14) + (_m2 * _m4 * _m15) + (_m3 * _m6 * _m12) - (_m0 * _m6 * _m15) - (_m2 * _m7 * _m12) - (_m3 * _m4 * _m14);
				m._m7 = (_m0 * _m6 * _m11) + (_m2 * _m7 * _m8) + (_m3 * _m4 * _m10) - (_m0 * _m7 * _m10) - (_m2 * _m4 * _m11) - (_m3 * _m6 * _m8);
				m._m8 = (_m4 * _m9 * _m15) + (_m5 * _m11 * _m12) + (_m7 * _m8 * _m13) - (_m4 * _m11 * _m13) - (_m5 * _m8 * _m15) - (_m7 * _m9 * _m12);
				m._m9 = (_m0 * _m11 * _m13) + (_m1 * _m8 * _m15) + (_m3 * _m9 * _m12) - (_m0 * _m9 * _m15) - (_m1 * _m11 * _m12) - (_m3 * _m8 * _m13);
				m._m10 = (_m0 * _m5 * _m15) + (_m1 * _m7 * _m12) + (_m3 * _m4 * _m13) - (_m0 * _m7 * _m13) - (_m1 * _m4 * _m15) - (_m3 * _m5 * _m12);
				m._m11 = (_m0 * _m7 * _m9) + (_m1 * _m4 * _m11) + (_m3 * _m5 * _m8) - (_m0 * _m5 * _m11) - (_m1 * _m7 * _m8) - (_m3 * _m4 * _m9);
				m._m12 = (_m4 * _m10 * _m13) + (_m5 * _m8 * _m14) + (_m6 * _m9 * _m12) - (_m4 * _m9 * _m14) - (_m5 * _m10 * _m12) - (_m6 * _m8 * _m13);
				m._m13 = (_m0 * _m9 * _m14) + (_m1 * _m10 * _m12) + (_m2 * _m8 * _m13) - (_m0 * _m10 * _m13) - (_m1 * _m8 * _m14) - (_m2 * _m9 * _m12);
				m._m14 = (_m0 * _m6 * _m13) + (_m1 * _m4 * _m14) + (_m2 * _m5 * _m12) - (_m0 * _m5 * _m14) - (_m1 * _m6 * _m12) - (_m2 * _m4 * _m13);
				m._m15 = (_m0 * _m5 * _m10) + (_m1 * _m6 * _m8) + (_m2 * _m4 * _m9) - (_m0 * _m6 * _m9) - (_m1 * _m4 * _m10) - (_m2 * _m5 * _m8);

				return ((1.0f / this->det()) * m);
			}
			case Hint::Rot:
			{
				m._m0 = this->_m0;
				m._m1 = this->_m4;
				m._m2 = this->_m8;
				m._m3 = 0.0f;
				m._m4 = this->_m1;
				m._m5 = this->_m5;
				m._m6 = this->_m9;
				m._m7 = 0.0f;
				m._m8 = this->_m2;
				m._m9 = this->_m6;
				m._m10 = this->_m10;
				m._m11 = 0.0f;
				m._m12 = 0.0f;
				m._m13 = 0.0f;
				m._m14 = 0.0f;
				m._m15 = 1.0f;
				break;
			}
			case Hint::Trans:
			{
				m._m0 = 1.0f;
				m._m1 = 0.0f;
				m._m2 = 0.0f;
				m._m3 = 0.0f;
				m._m4 = 0.0f;
				m._m5 = 1.0f;
				m._m6 = 0.0f;
				m._m7 = 0.0f;
				m._m8 = 0.0f;
				m._m9 = 0.0f;
				m._m10 = 1.0f;
				m._m11 = 0.0f;
				m._m12 = -this->_m12;
				m._m13 = -this->_m13;
				m._m14 = -this->_m14;
				m._m15 = 1.0f;
				break;
			}
			case Hint::RotTrans:
			{
				m._m0 = this->_m0;
				m._m1 = this->_m4;
				m._m2 = this->_m8;
				m._m3 = 0.0f;
				m._m4 = this->_m1;
				m._m5 = this->_m5;
				m._m6 = this->_m9;
				m._m7 = 0.0f;
				m._m8 = this->_m2;
				m._m9 = this->_m6;
				m._m10 = this->_m10;
				m._m11 = 0.0f;
				m._m12 = -this->_m12 * this->_m0 - this->_m13 * this->_m1 - this->_m14 * this->_m2;
				m._m13 = -this->_m12 * this->_m4 - this->_m13 * this->_m5 - this->_m14 * this->_m6;
				m._m14 = -this->_m12 * this->_m8 - this->_m13 * this->_m9 - this->_m14 * this->_m10;
				m._m15 = 1.0f;
				break;
			}
			case Hint::Scale:
			{
				m._m0 = 1.0f / this->_m0;
				m._m1 = 0.0f;
				m._m2 = 0.0f;
				m._m3 = 0.0f;
				m._m4 = 0.0f;
				m._m5 = 1.0f / this->_m5;
				m._m6 = 0.0f;
				m._m7 = 0.0f;
				m._m8 = 0.0f;
				m._m9 = 0.0f;
				m._m10 = 1.0f / this->_m10;
				m._m11 = 0.0f;
				m._m12 = 0.0f;
				m._m13 = 0.0f;
				m._m14 = 0.0f;
				m._m15 = 1.0f;
				break;
			}
			case Hint::RotScale:
			{
				float det = this->_m0 * (this->_m5 * this->_m10 - this->_m6 * this->_m9) -
					this->_m1 * (this->_m4 * this->_m10 - this->_m6 * this->_m8) +
					this->_m2 * (this->_m4 * this->_m9 - this->_m5 * this->_m8);

				float invDet = 1.0f / det;

				float m0 = (this->_m5 * this->_m10 - this->_m6 * this->_m9);
				float m1 = (this->_m2 * this->_m9 - this->_m1 * this->_m10);
				float m2 = (this->_m1 * this->_m6 - this->_m2 * this->_m5);
				float m4 = (this->_m6 * this->_m8 - this->_m4 * this->_m10);
				float m5 = (this->_m0 * this->_m10 - this->_m2 * this->_m8);
				float m6 = (this->_m2 * this->_m4 - this->_m0 * this->_m6);
				float m8 = (this->_m4 * this->_m9 - this->_m5 * this->_m8);
				float m9 = (this->_m1 * this->_m8 - this->_m0 * this->_m9);
				float m10 = (this->_m0 * this->_m5 - this->_m1 * this->_m4);

				m._m0 = m0 * invDet;
				m._m1 = m1 * invDet;
				m._m2 = m2 * invDet;
				m._m3 = 0.0f;
				m._m4 = m4 * invDet;
				m._m5 = m5 * invDet;
				m._m6 = m6 * invDet;
				m._m7 = 0.0f;
				m._m8 = m8 * invDet;
				m._m9 = m9 * invDet;
				m._m10 = m10 * invDet;
				m._m11 = 0.0f;
				m._m12 = 0.0f;
				m._m13 = 0.0f;
				m._m14 = 0.0f;
				m._m15 = 1.0f;
				break;
			}
			case Hint::TransScale:
			{
				float m0 = 1.0f / this->_m0;
				float m5 = 1.0f / this->_m5;
				float m10 = 1.0f / this->_m10;
				m._m0 = m0;
				m._m1 = 0.0f;
				m._m2 = 0.0f;
				m._m3 = 0.0f;
				m._m4 = 0.0f;
				m._m5 = m5;
				m._m6 = 0.0f;
				m._m7 = 0.0f;
				m._m8 = 0.0f;
				m._m9 = 0.0f;
				m._m10 = m10;
				m._m11 = 0.0f;
				m._m12 = -this->_m12 * m0;
				m._m13 = -this->_m13 * m5;
				m._m14 = -this->_m14 * m10;
				m._m15 = 1.0f;
				break;
			}
			case Hint::Affine:
			{
				float det = this->_m0 * (this->_m5 * this->_m10 - this->_m6 * this->_m9) -
					this->_m1 * (this->_m4 * this->_m10 - this->_m6 * this->_m8) +
					this->_m2 * (this->_m4 * this->_m9 - this->_m5 * this->_m8);

				float invDet = 1.0f / det;

				float m0 = (this->_m5 * this->_m10 - this->_m6 * this->_m9) * invDet;
				float m1 = (this->_m2 * this->_m9 - this->_m1 * this->_m10) * invDet;
				float m2 = (this->_m1 * this->_m6 - this->_m2 * this->_m5) * invDet;
				float m4 = (this->_m6 * this->_m8 - this->_m4 * this->_m10) * invDet;
				float m5 = (this->_m0 * this->_m10 - this->_m2 * this->_m8) * invDet;
				float m6 = (this->_m2 * this->_m4 - this->_m0 * this->_m6) * invDet;
				float m8 = (this->_m4 * this->_m9 - this->_m5 * this->_m8) * invDet;
				float m9 = (this->_m1 * this->_m8 - this->_m0 * this->_m9) * invDet;
				float m10 = (this->_m0 * this->_m5 - this->_m1 * this->_m4) * invDet;

				m._m0 = m0;
				m._m1 = m1;
				m._m2 = m2;
				m._m3 = 0.0f;
				m._m4 = m4;
				m._m5 = m5;
				m._m6 = m6;
				m._m7 = 0.0f;
				m._m8 = m8;
				m._m9 = m9;
				m._m10 = m10;
				m._m11 = 0.0f;
				m._m12 = -this->_m12 * m0 - this->_m13 * m4 - this->_m14 * m8;
				m._m13 = -this->_m12 * m1 - this->_m13 * m5 - this->_m14 * m9;
				m._m14 = -this->_m12 * m2 - this->_m13 * m6 - this->_m14 * m10;
				m._m15 = 1.0f;
				break;
			}
			default:
			{
				m._m0 = (_m5 * _m10 * _m15) + (_m6 * _m11 * _m13) + (_m7 * _m9 * _m14) - (_m5 * _m11 * _m14) - (_m6 * _m9 * _m15) - (_m7 * _m10 * _m13);
				m._m1 = (_m1 * _m11 * _m14) + (_m2 * _m9 * _m15) + (_m3 * _m10 * _m13) - (_m1 * _m10 * _m15) - (_m2 * _m11 * _m13) - (_m3 * _m9 * _m14);
				m._m2 = (_m1 * _m6 * _m15) + (_m2 * _m7 * _m13) + (_m3 * _m5 * _m14) - (_m1 * _m7 * _m14) - (_m2 * _m5 * _m15) - (_m3 * _m6 * _m13);
				m._m3 = (_m1 * _m7 * _m10) + (_m2 * _m5 * _m11) + (_m3 * _m6 * _m9) - (_m1 * _m6 * _m11) - (_m2 * _m7 * _m9) - (_m3 * _m5 * _m10);
				m._m4 = (_m4 * _m11 * _m14) + (_m6 * _m8 * _m15) + (_m7 * _m10 * _m12) - (_m4 * _m10 * _m15) - (_m6 * _m11 * _m12) - (_m7 * _m8 * _m14);
				m._m5 = (_m0 * _m10 * _m15) + (_m2 * _m11 * _m12) + (_m3 * _m8 * _m14) - (_m0 * _m11 * _m14) - (_m2 * _m8 * _m15) - (_m3 * _m10 * _m12);
				m._m6 = (_m0 * _m7 * _m14) + (_m2 * _m4 * _m15) + (_m3 * _m6 * _m12) - (_m0 * _m6 * _m15) - (_m2 * _m7 * _m12) - (_m3 * _m4 * _m14);
				m._m7 = (_m0 * _m6 * _m11) + (_m2 * _m7 * _m8) + (_m3 * _m4 * _m10) - (_m0 * _m7 * _m10) - (_m2 * _m4 * _m11) - (_m3 * _m6 * _m8);
				m._m8 = (_m4 * _m9 * _m15) + (_m5 * _m11 * _m12) + (_m7 * _m8 * _m13) - (_m4 * _m11 * _m13) - (_m5 * _m8 * _m15) - (_m7 * _m9 * _m12);
				m._m9 = (_m0 * _m11 * _m13) + (_m1 * _m8 * _m15) + (_m3 * _m9 * _m12) - (_m0 * _m9 * _m15) - (_m1 * _m11 * _m12) - (_m3 * _m8 * _m13);
				m._m10 = (_m0 * _m5 * _m15) + (_m1 * _m7 * _m12) + (_m3 * _m4 * _m13) - (_m0 * _m7 * _m13) - (_m1 * _m4 * _m15) - (_m3 * _m5 * _m12);
				m._m11 = (_m0 * _m7 * _m9) + (_m1 * _m4 * _m11) + (_m3 * _m5 * _m8) - (_m0 * _m5 * _m11) - (_m1 * _m7 * _m8) - (_m3 * _m4 * _m9);
				m._m12 = (_m4 * _m10 * _m13) + (_m5 * _m8 * _m14) + (_m6 * _m9 * _m12) - (_m4 * _m9 * _m14) - (_m5 * _m10 * _m12) - (_m6 * _m8 * _m13);
				m._m13 = (_m0 * _m9 * _m14) + (_m1 * _m10 * _m12) + (_m2 * _m8 * _m13) - (_m0 * _m10 * _m13) - (_m1 * _m8 * _m14) - (_m2 * _m9 * _m12);
				m._m14 = (_m0 * _m6 * _m13) + (_m1 * _m4 * _m14) + (_m2 * _m5 * _m12) - (_m0 * _m5 * _m14) - (_m1 * _m6 * _m12) - (_m2 * _m4 * _m13);
				m._m15 = (_m0 * _m5 * _m10) + (_m1 * _m6 * _m8) + (_m2 * _m4 * _m9) - (_m0 * _m6 * _m9) - (_m1 * _m4 * _m10) - (_m2 * _m5 * _m8);

				return ((1.0f / this->det()) * m);
			}
		}
		return m;
	}

	void Mat4::set(const Vec4& a, const Vec4& b, const Vec4& c, const Vec4& d)
	{
		this->_v0 = a;
		this->_v1 = b;
		this->_v2 = c;
		this->_v3 = d;
		this->SetHintGeneral();
	}

	void Mat4::set(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15)
	{
		this->_m0 = m0;
		this->_m1 = m1;
		this->_m2 = m2;
		this->_m3 = m3;
		this->_m4 = m4;
		this->_m5 = m5;
		this->_m6 = m6;
		this->_m7 = m7;
		this->_m8 = m8;
		this->_m9 = m9;
		this->_m10 = m10;
		this->_m11 = m11;
		this->_m12 = m12;
		this->_m13 = m13;
		this->_m14 = m14;
		this->_m15 = m15;
	}

	void Mat4::set(enum Special type)
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

	void Mat4::set(enum Trans, float x, float y, float z)
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
		this->_m12 = x;
		this->_m13 = y;
		this->_m14 = z;
		this->_m15 = 1.0f;
		this->SetHintTrans();
	}

	void Mat4::set(enum Trans, const Vec4& Vec4)
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
		this->_m12 = Vec4[x];
		this->_m13 = Vec4[y];
		this->_m14 = Vec4[z];
		this->_m15 = 1.0f;
		this->SetHintTrans();
	}

	void Mat4::set(enum Scale, float x, float y, float z)
	{
		this->_m0 = x;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		this->_m4 = 0.0f;
		this->_m5 = y;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;
		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = z;
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		this->SetHintScale();
	}

	void Mat4::set(enum Scale, const Vec4& Vec4)
	{
		this->_m0 = Vec4[x];
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		this->_m4 = 0.0f;
		this->_m5 = Vec4[y];
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;
		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = Vec4[z];
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		this->SetHintScale();
	}

	void Mat4::set(Rot1 axis, float theta)
	{
		float sin = Trig::sin(theta);
		float cos = Trig::cos(theta);
		if (axis == Rot1::X)
		{
			this->_v0 = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
			this->_v1 = Vec4(0.0f, cos, sin, 0.0f);
			this->_v2 = Vec4(0.0f, -sin, cos, 0.0f);
			this->_v3 = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (axis == Rot1::Y)
		{
			this->_v0 = Vec4(cos, 0.0f, -sin, 0.0f);
			this->_v1 = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
			this->_v2 = Vec4(sin, 0.0f, cos, 0.0f);
			this->_v3 = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			this->_v0 = Vec4(cos, sin, 0.0f, 0.0f);
			this->_v1 = Vec4(-sin, cos, 0.0f, 0.0f);
			this->_v2 = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
			this->_v3 = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		this->SetHintRot();
	}

	void Mat4::set(Orient orient, const Vec3& dof, const Vec3& up)
	{
		Vec3 a = up;
		Vec3 b = dof;
		Vec3 c = dof;

		a = a.cross(dof);
		b = b.cross(a);

		a.norm();
		b.norm();
		c.norm();

		if (orient == Orient::LocalToWorld)
		{
			this->_v0.set(a[x], a[y], a[z], 0.0f);
			this->_v1.set(b[x], b[y], b[z], 0.0f);
			this->_v2.set(c[x], c[y], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			this->_v0.set(a[x], b[x], c[x], 0.0f);
			this->_v1.set(a[y], b[y], c[y], 0.0f);
			this->_v2.set(a[z], b[z], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		this->SetHintRot();
	}

	void Mat4::set(Orient orient, const Vec4& dof, const Vec4& up)
	{
		Vec4 a = up;
		Vec4 b = dof;
		Vec4 c = dof;

		a = a.cross(dof);
		b = b.cross(a);

		a.norm();
		b.norm();
		c.norm();

		if (orient == Orient::LocalToWorld)
		{
			this->_v0.set(a[x], a[y], a[z], 0.0f);
			this->_v1.set(b[x], b[y], b[z], 0.0f);
			this->_v2.set(c[x], c[y], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			this->_v0.set(a[x], b[x], c[x], 0.0f);
			this->_v1.set(a[y], b[y], c[y], 0.0f);
			this->_v2.set(a[z], b[z], c[z], 0.0f);
			this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		}
		this->SetHintRot();
	}

	void Mat4::set(Rot3 combo, float x, float y, float z)
	{
		if (combo == Rot3::XYZ)
		{
			Mat4 mX = Mat4(Rot1::X, x);
			Mat4 mY = Mat4(Rot1::Y, y);
			Mat4 mZ = Mat4(Rot1::Z, z);
			*this = mX * mY * mZ;
		}
		this->SetHintRot();
	}

	void Mat4::set(enum Rot, const Vec3& v, float angle)
	{
		const float angle_a = 0.5f * angle;
		float cos_a;
		float sin_a;

		cos_a = cosf(angle_a);
		sin_a = sinf(angle_a);

		Vec3 qV = v;
		qV.norm();

		qV *= sin_a;

		Vec3 Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];

		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = cos_a * x2;
		wy = cos_a * y2;
		wz = cos_a * z2;

		this->_v0.set(1.0f - (yy + zz), xy + wz, xz - wy, 0.0f);
		this->_v1.set(xy - wz, 1.0f - (xx + zz), yz + wx, 0.0f);
		this->_v2.set(xz + wy, yz - wx, 1.0f - (xx + yy), 0.0f);
		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		this->SetHintRot();
	}

	void Mat4::set(enum Rot, const Vec4& v, float angle)
	{
		const float angle_a = 0.5f * angle;
		float cos_a;
		float sin_a;

		cos_a = cosf(angle_a);
		sin_a = sinf(angle_a);

		Vec4 qV = v;
		qV.norm();

		qV *= sin_a;

		Vec4 Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];
		Q[w] = cos_a;

		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_v0.set(1.0f - (yy + zz), xy + wz, xz - wy, 0.0f);
		this->_v1.set(xy - wz, 1.0f - (xx + zz), yz + wx, 0.0f);
		this->_v2.set(xz + wy, yz - wx, 1.0f - (xx + yy), 0.0f);
		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
		this->SetHintRot();
	}

	void Mat4::set(const Row row, const Vec4& Vec4)
	{
		if (row == Row::i0)
			this->_v0 = Vec4;
		else if (row == Row::i1)
			this->_v1 = Vec4;
		else if (row == Row::i2)
			this->_v2 = Vec4;
		else
			this->_v3 = Vec4;
	}

	void Mat4::set(const Quat& q)
	{
		float XxX = q[x] * q[x];
		float XxY = q[x] * q[y];
		float XxZ = q[x] * q[z];
		float XxW = q[x] * q[w];
		float YxY = q[y] * q[y];
		float YxZ = q[y] * q[z];
		float YxW = q[y] * q[w];
		float ZxZ = q[z] * q[z];
		float ZxW = q[z] * q[w];

		this->_m0 = 1.0f - (2.0f * (YxY + ZxZ));
		this->_m1 =			2.0f * (XxY + ZxW);
		this->_m2 =			2.0f * (XxZ - YxW);
		this->_m3 = 0.0f;

		this->_m4 =			2.0f * (XxY - ZxW);
		this->_m5 = 1.0f - (2.0f * (XxX + ZxZ));
		this->_m6 =			2.0f * (YxZ + XxW);
		this->_m7 = 0.0f;

		this->_m8 =			 2.0f * (XxZ + YxW);
		this->_m9 =			 2.0f * (YxZ - XxW);
		this->_m10 = 1.0f - (2.0f * (XxX + YxY));
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	Vec4& Mat4::get(const Row row) const
	{
		if (row == Row::i0)
			return (Vec4&)this->_v0;
		else if (row == Row::i1)
			return (Vec4&)this->_v1;
		else if (row == Row::i2)
			return (Vec4&)this->_v2;
		else
			return (Vec4&)this->_v3;
	}

	// Getters
	float Mat4::m0(void) const { return this->_m0; }
	float Mat4::m1(void) const { return this->_m1; }
	float Mat4::m2(void) const { return this->_m2; }
	float Mat4::m3(void) const { return this->_m3; }
	float Mat4::m4(void) const { return this->_m4; }
	float Mat4::m5(void) const { return this->_m5; }
	float Mat4::m6(void) const { return this->_m6; }
	float Mat4::m7(void) const { return this->_m7; }
	float Mat4::m8(void) const { return this->_m8; }
	float Mat4::m9(void) const { return this->_m9; }
	float Mat4::m10(void) const { return this->_m10; }
	float Mat4::m11(void) const { return this->_m11; }
	float Mat4::m12(void) const { return this->_m12; }
	float Mat4::m13(void) const { return this->_m13; }
	float Mat4::m14(void) const { return this->_m14; }
	float Mat4::m15(void) const { return this->_m15; }
	float Mat4::operator[](const m0_enum) const { return this->_m0; }
	float Mat4::operator[](const m1_enum) const { return this->_m1; }
	float Mat4::operator[](const m2_enum) const { return this->_m2; }
	float Mat4::operator[](const m3_enum) const { return this->_m3; }
	float Mat4::operator[](const m4_enum) const { return this->_m4; }
	float Mat4::operator[](const m5_enum) const { return this->_m5; }
	float Mat4::operator[](const m6_enum) const { return this->_m6; }
	float Mat4::operator[](const m7_enum) const { return this->_m7; }
	float Mat4::operator[](const m8_enum) const { return this->_m8; }
	float Mat4::operator[](const m9_enum) const { return this->_m9; }
	float Mat4::operator[](const m10_enum) const { return this->_m10; }
	float Mat4::operator[](const m11_enum) const { return this->_m11; }
	float Mat4::operator[](const m12_enum) const { return this->_m12; }
	float Mat4::operator[](const m13_enum) const { return this->_m13; }
	float Mat4::operator[](const m14_enum) const { return this->_m14; }
	float Mat4::operator[](const m15_enum) const { return this->_m15; }

	// Setters
	float& Mat4::m0(void) { this->SetHintGeneral(); return this->_m0; }
	float& Mat4::m1(void) { this->SetHintGeneral(); return this->_m1; }
	float& Mat4::m2(void) { this->SetHintGeneral(); return this->_m2; }
	float& Mat4::m3(void) { this->SetHintGeneral(); return this->_m3; }
	float& Mat4::m4(void) { this->SetHintGeneral(); return this->_m4; }
	float& Mat4::m5(void) { this->SetHintGeneral(); return this->_m5; }
	float& Mat4::m6(void) { this->SetHintGeneral(); return this->_m6; }
	float& Mat4::m7(void) { this->SetHintGeneral(); return this->_m7; }
	float& Mat4::m8(void) { this->SetHintGeneral(); return this->_m8; }
	float& Mat4::m9(void) { this->SetHintGeneral(); return this->_m9; }
	float& Mat4::m10(void) { this->SetHintGeneral(); return this->_m10; }
	float& Mat4::m11(void) { this->SetHintGeneral(); return this->_m11; }
	float& Mat4::m12(void) { this->SetHintGeneral(); return this->_m12; }
	float& Mat4::m13(void) { this->SetHintGeneral(); return this->_m13; }
	float& Mat4::m14(void) { this->SetHintGeneral(); return this->_m14; }
	float& Mat4::m15(void) { this->SetHintGeneral(); return this->_m15; }
	void Mat4::m0(float m0) { this->_m0 = m0; this->SetHintGeneral(); }
	void Mat4::m1(float m1) { this->_m1 = m1; this->SetHintGeneral(); }
	void Mat4::m2(float m2) { this->_m2 = m2; this->SetHintGeneral(); }
	void Mat4::m3(float m3) { this->_m3 = m3; this->SetHintGeneral(); }
	void Mat4::m4(float m4) { this->_m4 = m4; this->SetHintGeneral(); }
	void Mat4::m5(float m5) { this->_m5 = m5; this->SetHintGeneral(); }
	void Mat4::m6(float m6) { this->_m6 = m6; this->SetHintGeneral(); }
	void Mat4::m7(float m7) { this->_m7 = m7; this->SetHintGeneral(); }
	void Mat4::m8(float m8) { this->_m8 = m8; this->SetHintGeneral(); }
	void Mat4::m9(float m9) { this->_m9 = m9; this->SetHintGeneral(); }
	void Mat4::m10(float m10) { this->_m10 = m10; this->SetHintGeneral(); }
	void Mat4::m11(float m11) { this->_m11 = m11; this->SetHintGeneral(); }
	void Mat4::m12(float m12) { this->_m12 = m12; this->SetHintGeneral(); }
	void Mat4::m13(float m13) { this->_m13 = m13; this->SetHintGeneral(); }
	void Mat4::m14(float m14) { this->_m14 = m14; this->SetHintGeneral(); }
	void Mat4::m15(float m15) { this->_m15 = m15; this->SetHintGeneral(); }
	float& Mat4::operator[](const m0_enum) { this->SetHintGeneral(); return this->_m0; }
	float& Mat4::operator[](const m1_enum) { this->SetHintGeneral(); return this->_m1; }
	float& Mat4::operator[](const m2_enum) { this->SetHintGeneral(); return this->_m2; }
	float& Mat4::operator[](const m3_enum) { this->SetHintGeneral(); return this->_m3; }
	float& Mat4::operator[](const m4_enum) { this->SetHintGeneral(); return this->_m4; }
	float& Mat4::operator[](const m5_enum) { this->SetHintGeneral(); return this->_m5; }
	float& Mat4::operator[](const m6_enum) { this->SetHintGeneral(); return this->_m6; }
	float& Mat4::operator[](const m7_enum) { this->SetHintGeneral(); return this->_m7; }
	float& Mat4::operator[](const m8_enum) { this->SetHintGeneral(); return this->_m8; }
	float& Mat4::operator[](const m9_enum) { this->SetHintGeneral(); return this->_m9; }
	float& Mat4::operator[](const m10_enum) { this->SetHintGeneral(); return this->_m10; }
	float& Mat4::operator[](const m11_enum) { this->SetHintGeneral(); return this->_m11; }
	float& Mat4::operator[](const m12_enum) { this->SetHintGeneral(); return this->_m12; }
	float& Mat4::operator[](const m13_enum) { this->SetHintGeneral(); return this->_m13; }
	float& Mat4::operator[](const m14_enum) { this->SetHintGeneral(); return this->_m14; }
	float& Mat4::operator[](const m15_enum) { this->SetHintGeneral(); return this->_m15; }

	void Mat4::SetHintGeneral()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p &= (uint32_t)(0xFFFFFFF8);
	}

	void Mat4::SetHintRot()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p |= (uint32_t)(Hint::Rot);
	}

	void Mat4::SetHintTrans()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p |= (uint32_t)(Hint::Trans);
	}

	void Mat4::SetHintRotTrans()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p |= (uint32_t)(Hint::RotTrans);
	}

	void Mat4::SetHintScale()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p |= (uint32_t)(Hint::Scale);
	}

	void Mat4::SetHintRotScale()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p |= (uint32_t)(Hint::RotScale);
	}

	void Mat4::SetHintTransScale()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p |= (uint32_t)(Hint::TransScale);
	}

	void Mat4::SetHintAffine()
	{
		uint32_t* p = (uint32_t*)&this->_m15;
		*p |= (uint32_t)(Hint::Affine);
	}

	void Mat4::SetAndCombineHints(Hint a, Hint b)
	{
		Hint h;
		if (a == Hint::Generalize || b == Hint::Generalize)
			h = Hint::Generalize;
		else
			h = (Hint)((uint32_t)a | (uint32_t)b);
		uint32_t* p = (uint32_t*)&this->_m15;
		*p &= (uint32_t)(0xFFFFFFF8);
		*p |= (uint32_t)h;
	}


	void Mat4::SetAndCopyHint(Hint h)
	{
		if (h == Hint::Generalize)
			this->SetHintGeneral();
		else if (h == Hint::Rot)
			this->SetHintRot();
		else if (h == Hint::Trans)
			this->SetHintTrans();
		else if (h == Hint::RotTrans)
			this->SetHintRotTrans();
		else if (h == Hint::Scale)
			this->SetHintScale();
		else if (h == Hint::RotScale)
			this->SetHintRotScale();
		else if (h == Hint::TransScale)
			this->SetHintTransScale();
		else
			this->SetHintAffine();
	}

	Mat4::Hint Mat4::GetHint() const
	{
		const uint32_t* p = (const uint32_t*)&this->_m15;
		if ((*p & 0xFFFFFFF8) == 0x3f800000 || (*p & 0xFFFFFFF8) == 0x3f7ffff8)
			return (Hint)(*p & 0x7);
		else
			return Hint::Generalize;
	}

	void Mat4::PrintHint()
	{
		Hint h = this->GetHint();
		if (h == Hint::Generalize)
			Trace::out2("General\n");
		else if (h == Hint::Rot)
			Trace::out2("Rotation\n");
		else if (h == Hint::Trans)
			Trace::out2("Translation\n");
		else if (h == Hint::RotTrans)
			Trace::out2("Rotation + Translation\n");
		else if (h == Hint::Scale)
			Trace::out2("Scale\n");
		else if (h == Hint::RotScale)
			Trace::out2("Rotation + Scale\n");
		else if (h == Hint::TransScale)
			Trace::out2("Translation + Scale\n");
		else
			Trace::out2("Affine\n");
	}

	void Mat4::Print(const char *pName) const
	{
		Debug::Print(pName, *this);
	}

}

// ---  End of File ---
