//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
	// add magic

	Vec3::Vec3()
		: _vx(0.0f), _vy(0.0f), _vz(0.0f)
	{ }

	Vec3::Vec3(float x, float y, float z)
		: _vx(x), _vy(y), _vz(z)
	{ }

	Vec3::Vec3(const Vec3& rhs)
		: _vx(rhs._vx), _vy(rhs._vy), _vz(rhs._vz)
	{ }


	Vec3::Vec3(const Vec4& rhs)

		: _vx(rhs._vx), _vy(rhs._vy), _vz(rhs._vz)
	{ }

	Vec3& Vec3::operator=(const Vec3& rhs)
	{
		if (this != &rhs)
		{
			this->_vx = rhs._vx;
			this->_vy = rhs._vy;
			this->_vz = rhs._vz;
		}
		return *this;
	}

	Vec3::~Vec3()
	{ }

	bool Vec3::isEqual(const Vec3& rhs)
	{
		return isEqual(rhs, MATH_TOLERANCE);
	}

	bool Vec3::isEqual(const Vec3& rhs, float epsilon)
	{
		return (Util::isEqual(this->_vx, rhs._vx, epsilon) &&
			Util::isEqual(this->_vy, rhs._vy, epsilon) &&
			Util::isEqual(this->_vz, rhs._vz, epsilon));
	}

	bool Vec3::isZero()
	{
		return isZero(MATH_TOLERANCE);
	}

	bool Vec3::isZero(float epsilon)
	{
		return (Util::isZero(this->_vx, epsilon) &&
			Util::isZero(this->_vy, epsilon) &&
			Util::isZero(this->_vz, epsilon));
	}

	Vec3 Vec3::operator+(const Vec3& rhs)
	{
		return Vec3(this->_vx + rhs._vx, this->_vy + rhs._vy, this->_vz + rhs._vz);
	}

	void Vec3::operator+=(const Vec3& rhs)
	{
		this->_vx += rhs._vx;
		this->_vy += rhs._vy;
		this->_vz += rhs._vz;
	}

	Vec3 Vec3::operator+()
	{
		return Vec3(this->_vx, this->_vy, this->_vz);
	}

	Vec3 Vec3::operator-(const Vec3& rhs)
	{
		return Vec3(this->_vx - rhs._vx, this->_vy - rhs._vy, this->_vz - rhs._vz);
	}

	void Vec3::operator-=(const Vec3& rhs)
	{
		this->_vx -= rhs._vx;
		this->_vy -= rhs._vy;
		this->_vz -= rhs._vz;
	}

	Vec3 Vec3::operator-()
	{
		return Vec3(-this->_vx, -this->_vy, -this->_vz);
	}

	Vec3 Vec3::operator*(float rhs)
	{
		return Vec3(this->_vx * rhs, this->_vy * rhs, this->_vz * rhs);
	}

	void Vec3::operator*=(float rhs)
	{
		this->_vx *= rhs;
		this->_vy *= rhs;
		this->_vz *= rhs;
	}

	Vec3 Vec3::operator*(const Mat3& rhs)
	{
		return Vec3(
			this->_vx * rhs[m0] + this->_vy * rhs[m4] + this->_vz * rhs[m8],// + this->_vw * rhs[m12],
			this->_vx * rhs[m1] + this->_vy * rhs[m5] + this->_vz * rhs[m9],// + this->_vw * rhs[m13],
			this->_vx * rhs[m2] + this->_vy * rhs[m6] + this->_vz * rhs[m10]);// + this->_vw * rhs[m14]);
	}

	Vec4 Vec3::operator*(const Mat4& rhs)
	{
		return Vec4(
			this->_vx * rhs[m0] + this->_vy * rhs[m4] + this->_vz * rhs[m8] + rhs[m12],
			this->_vx * rhs[m1] + this->_vy * rhs[m5] + this->_vz * rhs[m9] + rhs[m13],
			this->_vx * rhs[m2] + this->_vy * rhs[m6] + this->_vz * rhs[m10] + rhs[m14],
			this->_vx * rhs[m3] + this->_vy * rhs[m7] + this->_vz * rhs[m11] + rhs[m15]);
	}

	void Vec3::operator*=(const Mat3& rhs)
	{
		*this = *this * rhs;
	}

	Vec3 Vec3::operator*(const Quat& rhs)
	{
		Vec3 v = Vec3();
		rhs.Lqcvq(*this, v);
		return v;
	}

	void Vec3::operator*=(const Quat& rhs)
	{
		rhs.Lqcvq(*this, *this);
	}

	Vec3& Vec3::norm()
	{
		float mag = this->len();
		this->_vx /= mag;
		this->_vy /= mag;
		this->_vz /= mag;
		return *this;
	}

	Vec3 Vec3::getNorm() const
	{
		float mag = this->len();
		return Vec3(this->_vx / mag, this->_vy / mag, this->_vz / mag);
	}

	Vec3Proxy Vec3::len() const
	{
		return Vec3Proxy(this->_vx, this->_vy, this->_vz);
	}

	float Vec3::magSqr() const
	{
		return (this->_vx * this->_vx) + (this->_vy * this->_vy) + (this->_vz * this->_vz);
	}

	float Vec3::dot(const Vec3& rhs) const
	{
		return (this->_vx * rhs._vx) + (this->_vy * rhs._vy) + (this->_vz * rhs._vz);
	}

	Vec3 Vec3::cross(const Vec3& rhs) const
	{
		return Vec3(
			this->_vy * rhs[vz] - this->_vz * rhs[vy],
			-(this->_vx * rhs[vz] - this->_vz * rhs[vx]),
			this->_vx * rhs[vy] - this->_vy * rhs[vx]);
	}

	float Vec3::getAngle(const Vec3& rhs) const
	{
		float dot = this->dot(rhs);
		float magA = this->len();
		Vec3 b = rhs;
		float magB = b.len();
		return Trig::acos(dot / (magA * magB));
	}

	// Getters
	float Vec3::x() const { return this->_vx; }
	float Vec3::y() const { return this->_vy; }
	float Vec3::z() const { return this->_vz; }
	float Vec3::operator[](const x_enum) const { return this->_vx; }
	float Vec3::operator[](const y_enum) const { return this->_vy; }
	float Vec3::operator[](const z_enum) const { return this->_vz; }

	// Setters
	float& Vec3::x() { return this->_vx; }
	float& Vec3::y() { return this->_vy; }
	float& Vec3::z() { return this->_vz; }
	void Vec3::x(float x) { this->_vx = x; }
	void Vec3::y(float y) { this->_vy = y; }
	void Vec3::z(float z) { this->_vz = z; }
	float& Vec3::operator[](const x_enum) { return this->_vx; }
	float& Vec3::operator[](const y_enum) { return this->_vy; }
	float& Vec3::operator[](const z_enum) { return this->_vz; }

	void Vec3::set(float x, float y, float z)
	{
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
	}

	void Vec3::set(const Vec3& rhs)
	{
		this->_vx = rhs._vx;
		this->_vy = rhs._vy;
		this->_vz = rhs._vz;
	}

	void Vec3::Print(const char *pName) const
	{
		Debug::Print(pName, *this);
	}
}

//--- End of File ---
