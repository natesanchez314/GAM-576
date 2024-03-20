//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Do your magic here

	Vec4::Vec4()
		: _vx(0.0f), _vy(0.0f), _vz(0.0f), _vw(0.0f)
	{ }

	Vec4::Vec4(float x, float y, float z)
		: _vx(x), _vy(y), _vz(z), _vw(1.0f)
	{ }

	Vec4::Vec4(float x, float y, float z, float w)
		: _vx(x), _vy(y), _vz(z), _vw(w)
	{ }


	Vec4::Vec4(const Vec3& vec3)
		: _vx(vec3._vx), _vy(vec3._vy), _vz(vec3._vz), _vw(1.0f)
	{ }

	Vec4::Vec4(const Vec3& vec3, float w)
		: _vx(vec3._vx), _vy(vec3._vy), _vz(vec3._vz), _vw(w)
	{ }

	Vec4::Vec4(const Vec4& rhs)
		: _vx(rhs._vx), _vy(rhs._vy), _vz(rhs._vz), _vw(rhs._vw)
	{ }

	Vec4& Vec4::operator=(const Vec4& rhs)
	{
		if (this != &rhs)
		{
			this->_vx = rhs._vx;
			this->_vy = rhs._vy;
			this->_vz = rhs._vz;
			this->_vw = rhs._vw;
		}
		return *this;
	}

	Vec4::~Vec4()
	{ }

	bool Vec4::isEqual(const Vec4& rhs) const
	{
		return isEqual(rhs, MATH_TOLERANCE);
	}

	bool Vec4::isEqual(const Vec4& rhs, float epsilon) const
	{
		return (Util::isEqual(this->_vx, rhs._vx, epsilon) &&
			Util::isEqual(this->_vy, rhs._vy, epsilon) &&
			Util::isEqual(this->_vz, rhs._vz, epsilon) &&
			Util::isEqual(this->_vw, rhs._vw, epsilon));
	}

	bool Vec4::isZero() const
	{
		return isZero(MATH_TOLERANCE);
	}

	bool Vec4::isZero(float epsilon) const
	{
		return (Util::isZero(this->_vx, epsilon) &&
			Util::isZero(this->_vy, epsilon) &&
			Util::isZero(this->_vz, epsilon) &&
			Util::isZero(this->_vw, epsilon));
	}

	Vec4 Vec4::operator+(const Vec4& rhs)
	{
		return Vec4(this->_vx + rhs._vx, this->_vy + rhs._vy, this->_vz + rhs._vz, this->_vw + rhs._vw);
	}

	void Vec4::operator+=(const Vec4& rhs)
	{
		this->_vx += rhs._vx;
		this->_vy += rhs._vy;
		this->_vz += rhs._vz;
		this->_vw += rhs._vw;
	}

	Vec4 Vec4::operator+()
	{
		return Vec4(this->_vx, this->_vy, this->_vz, this->_vw);
	}

	Vec4 Vec4::operator-(const Vec4& rhs)
	{
		return Vec4(this->_vx - rhs._vx, this->_vy - rhs._vy, this->_vz - rhs._vz, this->_vw - rhs._vw);
	}

	void Vec4::operator-=(const Vec4& rhs)
	{
		this->_vx -= rhs._vx;
		this->_vy -= rhs._vy;
		this->_vz -= rhs._vz;
		this->_vw -= rhs._vw;
	}

	Vec4 Vec4::operator-()
	{
		return Vec4(-this->_vx, -this->_vy, -this->_vz, -this->_vw);
	}

	Vec4 Vec4::operator*(float rhs)
	{
		return Vec4(this->_vx * rhs, this->_vy * rhs, this->_vz * rhs, this->_vw * rhs);
	}

	Vec4 Vec4::operator*(const Mat4& rhs)
	{
		return Vec4(
			this->_vx * rhs[m0] + this->_vy * rhs[m4] + this->_vz * rhs[m8] + this->_vw * rhs[m12],
			this->_vx * rhs[m1] + this->_vy * rhs[m5] + this->_vz * rhs[m9] + this->_vw * rhs[m13],
			this->_vx * rhs[m2] + this->_vy * rhs[m6] + this->_vz * rhs[m10] + this->_vw * rhs[m14],
			this->_vx * rhs[m3] + this->_vy * rhs[m7] + this->_vz * rhs[m11] + this->_vw * rhs[m15]);
	}

	void Vec4::operator*=(float rhs)
	{
		this->_vx *= rhs;
		this->_vy *= rhs;
		this->_vz *= rhs;
		this->_vw *= rhs;
	}

	void Vec4::operator*=(const Mat4& rhs)
	{
		*this = *this * rhs;
	}

	Vec4& Vec4::norm()
	{
		float mag = this->len();
		this->_vx /= mag;
		this->_vy /= mag;
		this->_vz /= mag;
		this->_vw /= mag;
		return *this;
	}

	Vec4 Vec4::getNorm() const
	{
		float mag = this->len();
		return Vec4(this->_vx / mag, this->_vy / mag, this->_vz / mag, this->_vw / mag);
	}

	Vec4Proxy Vec4::len() const
	{
		return Vec4Proxy(this->_vx, this->_vy, this->_vz, this->_vw);
	}

	float Vec4::magSqr() const
	{
		return (this->_vx * this->_vx) + (this->_vy * this->_vy) + (this->_vz * this->_vz) + (this->_vw * this->_vw);
	}

	float Vec4::dot(const Vec4& rhs) const
	{
		return (this->_vx * rhs._vx) + (this->_vy * rhs._vy) + (this->_vz * rhs._vz) + (this->_vw * rhs._vw);
	}

	Vec4 Vec4::cross(const Vec4& rhs) const
	{
		return Vec4(
			this->_vy * rhs[vz] - this->_vz * rhs[vy],
			-(this->_vx * rhs[vz] - this->_vz * rhs[vx]),
			this->_vx * rhs[vy] - this->_vy * rhs[vx]);
	}

	float Vec4::getAngle(const Vec4& rhs) const
	{
		float dot = this->dot(rhs);
		float magA = this->len();
		Vec4 b = rhs;
		float magB = b.len();
		return Trig::acos(dot / (magA * magB));
	}

	// Getters
	float Vec4::x() const { return this->_vx; }
	float Vec4::y() const { return this->_vy; }
	float Vec4::z() const { return this->_vz; }
	float Vec4::w() const { return this->_vw; }
	float Vec4::operator[](const x_enum) const { return this->_vx; }
	float Vec4::operator[](const y_enum) const { return this->_vy; }
	float Vec4::operator[](const z_enum) const { return this->_vz; }
	float Vec4::operator[](const w_enum) const { return this->_vw; }

	// Setters
	float& Vec4::x() { return this->_vx; }
	float& Vec4::y() { return this->_vy; }
	float& Vec4::z() { return this->_vz; }
	float& Vec4::w() { return this->_vw; }
	void Vec4::x(float x) { this->_vx = x; }
	void Vec4::y(float y) { this->_vy = y; }
	void Vec4::z(float z) { this->_vz = z; }
	void Vec4::w(float w) { this->_vw = w; }
	float& Vec4::operator[](const x_enum) { return this->_vx; }
	float& Vec4::operator[](const y_enum) { return this->_vy; }
	float& Vec4::operator[](const z_enum) { return this->_vz; }
	float& Vec4::operator[](const w_enum) { return this->_vw; }

	void Vec4::set(float x, float y, float z)
	{
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
		this->_vw = 1.0f;
	}

	void Vec4::set(float x, float y, float z, float w)
	{
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
		this->_vw = w;
	}

	void Vec4::set(const Vec4& rhs)
	{
		this->_vx = rhs._vx;
		this->_vy = rhs._vy;
		this->_vz = rhs._vz;
		this->_vw = rhs._vw;
	}

	void Vec4::set(const Vec3& vec3)
	{
		this->_vx = vec3._vx;
		this->_vy = vec3._vy;
		this->_vz = vec3._vz;
		this->_vw = 1.0f;
	}

	void Vec4::set(const Vec3& vec3, float w)
	{
		this->_vx = vec3._vx;
		this->_vy = vec3._vy;
		this->_vz = vec3._vz;
		this->_vw = w;
	}

	void Vec4::Print(const char *pName) const
	{
		Debug::Print(pName, *this);
	}
}

//--- End of File ---
