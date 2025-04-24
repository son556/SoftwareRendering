#include "pch.h"
#include "Quaternion.h"
#include "Vector4.h"


Quaternion::Quaternion(Vector3 const& axis, float degree)
{
	float const	c = cosf(degree / 360 * M_PI);
	float const	s = sinf(degree / 360 * M_PI);
	this->w = c;
	this->x = axis.x * s;
	this->y = axis.y * s;
	this->z = axis.z * s;
}

Quaternion::Quaternion(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion Quaternion::operator*(Quaternion const& q) const
{
	Quaternion	ret(0, 0, 0, 0);

	ret.w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
	ret.x = this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y;
	ret.y = this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x;
	ret.z = this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w;
	return (ret);
}

Vector3 Quaternion::operator*(Vector3 const& v) const
{
	Quaternion	q(0, v.x, v.y, v.z);
	q = *this * q * ~*this;
	Vector3 res(q.x, q.y, q.z);
	return res;
}

Vector4 Quaternion::operator*(Vector4 const& v) const
{
	Quaternion	q(0, v.x, v.y, v.z);
	q = *this * q * ~*this;
	Vector4 res(q.x, q.y, q.z, v.w);
	return res;
}

Quaternion Quaternion::operator~() const
{
	return Quaternion(this->w, -this->x, -this->y, -this->z);
}


