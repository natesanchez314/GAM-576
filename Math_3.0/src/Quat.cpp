//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{

	// Do your magic here

	Quat::Quat()
		:_qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(1.0f)
	{ }

	Quat::Quat(float x, float y, float z, float w)
		: _qx(x), _qy(y), _qz(z), _qw(w)
	{ }

	Quat::Quat(const Vec3& v)
		: _qV3(v)
	{ }

	Quat::Quat(const Vec3& v, float real)
		: _qV4(v, real)
	{ }

	Quat::Quat(const Vec4& v)
		: _qV4(v)
	{ }

	Quat::Quat(const Mat4& m)
	{
		float tr = m[m0] + m[m5] + m[m10];
		float s;

		if (tr > 0.0f)
		{
			s = 2 * Trig::sqrt(tr + 1.0f);
			this->_qx = -(m[m9] - m[m6]) / s;
			this->_qy = -(m[m2] - m[m8]) / s;
			this->_qz = -(m[m4] - m[m1]) / s;
			this->_qw = 0.25f * s;
		}
		else if (m[m0] > m[m5] && m[m0] > m[m10])
		{
			s = 2 * Trig::sqrt(1.0f + m[m0] - m[m5] - m[m10]);
			this->_qx = 0.25f * s;
			this->_qy = (m[m1] + m[m4]) / s;
			this->_qz = (m[m2] + m[m8]) / s;
			this->_qw = -(m[m9] - m[m6]) / s;
		}
		else if (m[m5] > m[m10])
		{
			s = 2 * Trig::sqrt(1.0f + m[m5] - m[m0] - m[m10]);
			this->_qx = (m[m1] + m[m4]) / s;
			this->_qy = 0.25f * s;
			this->_qz = (m[m6] + m[m9]) / s;
			this->_qw = -(m[m2] - m[m8]) / s;
		}
		else
		{
			s = 2 * Trig::sqrt(1.0f + m[m10] - m[m0] - m[m5]);
			this->_qx = (m[m2] + m[m8]) / s;
			this->_qy = (m[m6] + m[m9]) / s;
			this->_qz = 0.25f * s;
			this->_qw = -(m[m4] - m[m1]) / s;
		}
	}

	Quat::Quat(enum Rot1 axis, float theta)
	{
		if (axis == Rot1::X)
			this->set(Rot::AxisAngle, Vec3(1, 0, 0), theta);
		else if (axis == Rot1::Y)
			this->set(Rot::AxisAngle, Vec3(0, 1, 0), theta);
		else
			this->set(Rot::AxisAngle, Vec3(0, 0, 1), theta);
	}

	Quat::Quat(enum Special type)
	{
		if (type == Special::Identity)
		{
			this->_qx = 0.0f;
			this->_qy = 0.0f;
			this->_qz = 0.0f;
			this->_qw = 1.0f;
		}
		else
		{
			this->_qx = 0.0f;
			this->_qy = 0.0f;
			this->_qz = 0.0f;
			this->_qw = 0.0f;
		}
	}

	Quat::Quat(enum Rot, const Vec3& axis, float angle)
	{
		float a = 0.5f * angle;
		float s = Trig::sin(a);
		float c = Trig::cos(a);

		Vec3 v = axis.getNorm();
		v *= s;
		this->set(v, c);
	}

	Quat::Quat(Orient orient, const Vec3& dof, const Vec3& up)
	{
		Mat4 m;
		if (orient == Orient::LocalToWorld)
			m = Mat4(Mat4::Orient::LocalToWorld, dof, up);
		else
			m = Mat4(Mat4::Orient::WorldToLocal, dof, up);
		this->set(m);
	}

	Quat::Quat(Rot3 combo, float x, float y, float z)
	{
		if (combo == Rot3::XYZ)
		{
			Quat qX = Quat(Rot1::X, x);
			Quat qY = Quat(Rot1::Y, y);
			Quat qZ = Quat(Rot1::Z, z);
			*this = qX * qY * qZ;
		}
	}

	Quat::Quat(const Quat& other)
		: _qx(other._qx), _qy(other._qy), _qz(other._qz), _qw(other._qw)
	{ }

	Quat& Quat::operator=(const Quat& other)
	{
		this->_qx = other._qx;
		this->_qy = other._qy;
		this->_qz = other._qz;
		this->_qw = other._qw;

		return *this;
	}

	Quat::~Quat()
	{ }

	bool Quat::isEqual(const Quat& rhs) const
	{
		return this->isEqual(rhs, MATH_TOLERANCE);
	}

	bool Quat::isEqual(const Quat& rhs, float tolerance) const
	{
		return (Util::isEqual(this->_qx, rhs._qx, tolerance) &&
			Util::isEqual(this->_qy, rhs._qy, tolerance) &&
			Util::isEqual(this->_qz, rhs._qz, tolerance) &&
			Util::isEqual(this->_qw, rhs._qw, tolerance));
	}

	bool Quat::isNegEqual(const Quat& rhs) const
	{
		return this->isNegEqual(rhs, MATH_TOLERANCE);
	}

	bool Quat::isNegEqual(const Quat& rhs, float tolerance) const
	{
		return (Util::isEqual(this->_qx, -rhs._qx, tolerance) &&
			Util::isEqual(this->_qy, -rhs._qy, tolerance) &&
			Util::isEqual(this->_qz, -rhs._qz, tolerance) &&
			Util::isEqual(this->_qw, -rhs._qw, tolerance));
	}

	bool Quat::isEquivalent(const Quat& rhs) const
	{
		return this->isEquivalent(rhs, MATH_TOLERANCE);
	}

	bool Quat::isEquivalent(const Quat& rhs, float tolerance) const
	{
		return this->isEqual(rhs, tolerance) || this->isNegEqual(rhs, tolerance);
	}

	bool Quat::isConjugateEqual(const Quat& rhs) const
	{
		return isConjugateEqual(rhs, MATH_TOLERANCE);
	}

	bool Quat::isConjugateEqual(const Quat& rhs, float tolerance) const
	{
		return (Util::isEqual(this->_qx, -rhs._qx, tolerance) &&
			Util::isEqual(this->_qy, -rhs._qy, tolerance) &&
			Util::isEqual(this->_qz, -rhs._qz, tolerance) &&
			Util::isEqual(this->_qw, rhs._qw, tolerance));
	}

	bool Quat::isIdentity() const
	{
		return isIdentity(MATH_TOLERANCE);
	}

	bool Quat::isIdentity(float tolerance) const
	{
		return (Util::isZero(this->_qx, tolerance) &&
			Util::isZero(this->_qy, tolerance) &&
			Util::isZero(this->_qz, tolerance) &&
			Util::isOne(this->_qw, tolerance));
	}

	bool Quat::isNormalized() const
	{
		return isNormalized(MATH_TOLERANCE);
	}

	bool Quat::isNormalized(float tolerance) const
	{
		return Util::isOne(this->magSquared(), tolerance);
	}

	bool Quat::isZero() const
	{
		return isZero(MATH_TOLERANCE);
	}

	bool Quat::isZero(float tolerance) const
	{
		return (Util::isZero(this->_qx, tolerance) &&
			Util::isZero(this->_qy, tolerance) &&
			Util::isZero(this->_qz, tolerance) &&
			Util::isZero(this->_qw, tolerance));
	}

	Quat Quat::operator+(const Quat& rhs)
	{
		return Quat(
			this->_qx + rhs._qx,
			this->_qy + rhs._qy,
			this->_qz + rhs._qz,
			this->_qw + rhs._qw
		);
	}

	void Quat::operator+=(const Quat& rhs)
	{
		this->_qx += rhs._qx;
		this->_qy += rhs._qy;
		this->_qz += rhs._qz;
		this->_qw += rhs._qw;
	}

	Quat Quat::operator+(const float rhs)
	{
		return Quat(
			this->_qx + rhs,
			this->_qy + rhs,
			this->_qz + rhs,
			this->_qw + rhs
		);
	}

	void Quat::operator+=(const float rhs)
	{
		this->_qx += rhs;
		this->_qy += rhs;
		this->_qz += rhs;
		this->_qw += rhs;
	}

	Quat Quat::operator+()
	{
		return Quat(this->_qx, this->_qy, this->_qz, this->_qw);
	}

	Quat Quat::operator-(const Quat& rhs)
	{
		return Quat(
			this->_qx - rhs._qx,
			this->_qy - rhs._qy,
			this->_qz - rhs._qz,
			this->_qw - rhs._qw
		);
	}

	void Quat::operator-=(const Quat& rhs)
	{
		this->_qx -= rhs._qx;
		this->_qy -= rhs._qy;
		this->_qz -= rhs._qz;
		this->_qw -= rhs._qw;
	}

	Quat Quat::operator-(const float rhs)
	{
		return Quat(
			this->_qx - rhs,
			this->_qy - rhs,
			this->_qz - rhs,
			this->_qw - rhs
		);
	}

	void Quat::operator-=(const float& rhs)
	{
		this->_qx -= rhs;
		this->_qy -= rhs;
		this->_qz -= rhs;
		this->_qw -= rhs;
	}

	Quat Quat::operator-()
	{
		return Quat(-this->_qx, -this->_qy, -this->_qz, -this->_qw);
	}

	Quat Quat::operator*(const Quat& rhs)
	{
		Vec3 v = rhs._qV3.cross(this->_qV3) + (rhs._qw * this->_qV3) + (this->_qw * rhs._qV3);
		float s = this->_qw * rhs._qw - this->_qV3.dot(rhs._qV3);
		return Quat(v, s);
	}

	void Quat::operator*=(const Quat& rhs)
	{
		Vec3 v = rhs._qV3.cross(this->_qV3) + (rhs._qw * this->_qV3) + (this->_qw * rhs._qV3);
		float s = this->_qw * rhs._qw - this->_qV3.dot(rhs._qV3);
		this->_qV3 = v;
		this->_qw = s;
	}

	Mat4 Quat::operator*(const Mat4& rhs)
	{
		Mat4 m(*this);
		m *= rhs;
		return m;
	}

	void Quat::operator*=(const Mat4& rhs)
	{
		Mat4 m(*this);
		*this = Quat(m * rhs);
	}

	Quat Quat::operator*(const float rhs)
	{
		return Quat(
			this->_qx * rhs,
			this->_qy * rhs,
			this->_qz * rhs,
			this->_qw * rhs
		);
	}

	void Quat::operator*=(const float rhs)
	{
		this->_qx *= rhs;
		this->_qy *= rhs;
		this->_qz *= rhs;
		this->_qw *= rhs;
	}

	Quat Quat::operator/(const Quat& rhs)
	{
		return Quat(
			this->_qx / rhs._qx,
			this->_qy / rhs._qy,
			this->_qz / rhs._qz,
			this->_qw / rhs._qw
		);
	}

	void Quat::operator/=(const Quat& rhs)
	{
		this->_qx /= rhs._qx;
		this->_qy /= rhs._qy;
		this->_qz /= rhs._qz;
		this->_qw /= rhs._qw;
	}

	Quat Quat::operator/(const float rhs)
	{
		return Quat(
			this->_qx / rhs,
			this->_qy / rhs,
			this->_qz / rhs,
			this->_qw / rhs
		);
	}

	void Quat::operator/=(const float rhs)
	{
		this->_qx /= rhs;
		this->_qy /= rhs;
		this->_qz /= rhs;
		this->_qw /= rhs;
	}

	void Quat::Lqcvq(const Vec3& vIn, Vec3& vOut) const
	{
		vOut = 2.0f * this->_qw * (this->_qV3.cross(vIn)) + (this->_qw * this->_qw - this->_qV3.dot(this->_qV3)) * vIn + 2.0f * (this->_qV3.dot(vIn)) * this->_qV3;
	}

	void Quat::Lqvqc(const Vec3& vIn, Vec3& vOut) const
	{
		vOut = 2.0f * this->_qw * (vIn.cross(this->_qV3)) + (this->_qw * this->_qw - this->_qV3.dot(this->_qV3)) * vIn + 2.0f * (this->_qV3.dot(vIn)) * this->_qV3;
	}

	Quat Quat::getConj() const
	{
		return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
	}

	void Quat::conj()
	{
		this->_qx = -this->_qx;
		this->_qy = -this->_qy;
		this->_qz = -this->_qz;
	}

	Quat Quat::getT() const
	{
		Mat4 m(*this);
		m.T();
		return Quat(m);
	}

	void Quat::T()
	{
		Mat4 m(*this);
		m.T();
		this->set(m);
	}

	float Quat::mag() const
	{
		return Trig::sqrt(this->magSquared());
	}

	float Quat::magSquared() const
	{
		return this->_qx * this->_qx + this->_qy * this->_qy + this->_qz * this->_qz + this->_qw * this->_qw;
	}

	float Quat::invMag() const
	{
		return Trig::rsqrt(this->magSquared());
	}

	Quat Quat::getNorm() const
	{
		float mag = this->mag();
		return Quat(
			this->_qx / mag,
			this->_qy / mag,
			this->_qz / mag,
			this->_qw / mag
		);
	}

	Quat Quat::norm()
	{
		float mag = this->mag();
		this->_qx /= mag;
		this->_qy /= mag;
		this->_qz /= mag;
		this->_qw /= mag;
		return *this;
	}

	Quat Quat::getInv() const
	{
		return this->getConj() / this->magSquared();
	}

	void Quat::inv()
	{
		*this = this->getConj() / this->magSquared();
	}

	float Quat::dot(const Quat& q) const
	{
		return this->_qx * q._qx + this->_qy * q._qy + this->_qz * q._qz + this->_qw * q._qw;
	}

	float Quat::getAngle() const
	{
		return 2.0f * Trig::acos(this->_qw);
	}

	void Quat::getAxis(Vec3& v) const
	{
		v = this->_qV3.getNorm();
	}

	// Setters
	float& Quat::qx() { return this->_qx; }
	float& Quat::qy() { return this->_qy; }
	float& Quat::qz() { return this->_qz; }
	float& Quat::real() { return this->_qw; }
	void Quat::qx(float x) { this->_qx = x; }
	void Quat::qy(float y) { this->_qy = y; }
	void Quat::qz(float z) { this->_qz = z; }
	void Quat::real(float w) { this->_qw = w; }
	float& Quat::operator[](const x_enum) { return this->_qx; }
	float& Quat::operator[](const y_enum) { return this->_qy; }
	float& Quat::operator[](const z_enum) { return this->_qz; }
	float& Quat::operator[](const w_enum) { return this->_qw; }

	void Quat::set(float x, float y, float z) 
	{
		this->_qx = x;
		this->_qy = y;
		this->_qz = z;
	}

	void Quat::set(float x, float y, float z, float w)
	{
		this->_qx = x;
		this->_qy = y;
		this->_qz = z;
		this->_qw = w;
	}

	void Quat::setVec3(const Vec3& v)
	{
		this->_qV3.set(v);
	}

	void Quat::set(const Vec3& v, float real)
	{
		this->_qV4.set(v, real);
	}

	void Quat::set(const Vec4& v)
	{
		this->_qV4.set(v);
	}

	void Quat::set(const Mat4& m)
	{
		float tr = m[m0] + m[m5] + m[m10];
		float s;

		if (tr > 0.0f)
		{
			s = 2 * Trig::sqrt(tr + 1.0f);
			this->_qx = -(m[m9] - m[m6]) / s;
			this->_qy = -(m[m2] - m[m8]) / s;
			this->_qz = -(m[m4] - m[m1]) / s;
			this->_qw = 0.25f * s;
		}
		else if (m[m0] > m[m5] && m[m0] > m[m10])
		{
			s = 2 * Trig::sqrt(1.0f + m[m0] - m[m5] - m[m10]);
			this->_qx = 0.25f * s;
			this->_qy = (m[m1] + m[m4]) / s;
			this->_qz = (m[m2] + m[m8]) / s;
			this->_qw = -(m[m9] - m[m6]) / s;
		}
		else if (m[m5] > m[m10])
		{
			s = 2 * Trig::sqrt(1.0f + m[m5] - m[m0] - m[m10]);
			this->_qx = (m[m1] + m[m4]) / s;
			this->_qy = 0.25f * s;
			this->_qz = (m[m6] + m[m9]) / s;
			this->_qw = -(m[m2] - m[m8]) / s;
		}
		else
		{
			s = 2 * Trig::sqrt(1.0f + m[m10] - m[m0] - m[m5]);
			this->_qx = (m[m2] + m[m8]) / s;
			this->_qy = (m[m6] + m[m9]) / s;
			this->_qz = 0.25f * s;
			this->_qw = -(m[m4] - m[m1]) / s;
		}
	}

	void Quat::set(const Quat& q)
	{
		this->_qx = q._qx;
		this->_qy = q._qz;
		this->_qz = q._qz;
		this->_qw = q._qw;
	}

	void Quat::set(enum Rot1 axis, float theta)
	{
		if (axis == Rot1::X)
			this->set(Rot::AxisAngle, Vec3(1, 0, 0), theta);
		else if (axis == Rot1::Y)
			this->set(Rot::AxisAngle, Vec3(0, 1, 0), theta);
		else
			this->set(Rot::AxisAngle, Vec3(0, 0, 1), theta);
	}

	void Quat::set(enum Special type)
	{
		if (type == Special::Identity)
		{
			this->_qx = 0.0f;
			this->_qy = 0.0f;
			this->_qz = 0.0f;
			this->_qw = 1.0f;
		}
		else
		{
			this->_qx = 0.0f;
			this->_qy = 0.0f;
			this->_qz = 0.0f;
			this->_qw = 0.0f;
		}
	}

	void Quat::set(enum Rot, const Vec3& axis, float angle)
	{
		float a = 0.5f * angle;
		float s = Trig::sin(a);
		float c = Trig::cos(a);

		Vec3 v = axis.getNorm();
		v *= s;
		this->set(v, c);
	}

	void Quat::set(Orient orient, const Vec3& dof, const Vec3& up)
	{
		Mat4 m;
		if (orient == Orient::LocalToWorld)
			m = Mat4(Mat4::Orient::LocalToWorld, dof, up);
		else
			m = Mat4(Mat4::Orient::WorldToLocal, dof, up);
		this->set(m);
	}

	void Quat::set(Rot3 combo, float x, float y, float z)
	{
		if (combo == Rot3::XYZ)
		{
			Quat qX = Quat(Rot1::X, x);
			Quat qY = Quat(Rot1::Y, y);
			Quat qZ = Quat(Rot1::Z, z);
			*this = qX * qY * qZ;
		}
	}

	// Getters
	float Quat::qx() const { return this->_qx; }
	float Quat::qy() const { return this->_qy; }
	float Quat::qz() const { return this->_qz; } 
	float Quat::real() const { return this->_qw; } 
	Vec3 Quat::getVec3() const { return this->_qV3; }
	void Quat::getVec3(Vec3& v) { v = this->_qV3; }
	Vec4 Quat::getVec4() const { return this->_qV4; }
	void Quat::getVec4(Vec4& v) { v = this->_qV4; }
	float Quat::operator[](const x_enum) const { return this->_qx; }
	float Quat::operator[](const y_enum) const { return this->_qy; }
	float Quat::operator[](const z_enum) const { return this->_qz; }
	float Quat::operator[](const w_enum) const { return this->_qw; }
}

//--- End of File ---
