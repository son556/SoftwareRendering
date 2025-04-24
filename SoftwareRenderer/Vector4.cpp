#include "pch.h"
#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(Vector3 const& v, float w) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}

Vector4::Vector4(const Vector4& ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
}

Vector4& Vector4::operator=(const Vector4& ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
	return *this;
}

Vector4	Vector4::operator+(const Vector4& ref) const {
	Vector4	ret;

	ret.x = this->x + ref.x;
	ret.y = this->y + ref.y;
	ret.z = this->z + ref.z;
	ret.w = this->w + ref.w;
	return (ret);
}

Vector4	Vector4::operator-(const Vector4& ref) const {
	Vector4	ret;

	ret.x = this->x - ref.x;
	ret.y = this->y - ref.y;
	ret.z = this->z - ref.z;
	ret.w = this->w - ref.w;
	return (ret);
}

Vector4	Vector4::operator-() const {
	Vector4	ret;

	ret.x = -this->x;
	ret.y = -this->y;
	ret.z = -this->z;
	ret.w = -this->w;
	return (ret);
}

Vector4	Vector4::operator*(float f) const {
	Vector4	ret;

	ret.x = this->x * f;
	ret.y = this->y * f;
	ret.z = this->z * f;
	ret.w = this->w * f;
	return (ret);
}

float	Vector4::operator*(const Vector4& ref) const {
	return (ref.x * this->x + ref.y * this->y + ref.z * this->z + 
		ref.w * this->w);
}

Vector4	Vector4::operator/(float f) const {
	Vector4	ret;

	ret.x = this->x / f;
	ret.y = this->y / f;
	ret.z = this->z / f;
	ret.w = this->w / f;
	return (ret);
}

Vector4::operator Color() const {
	return (Color(this->x, this->y, this->z, this->w));
}

float	Vector4::lengthSqr() const {
	return (*this * *this);
}

float	Vector4::length() const {
	return (sqrt(this->lengthSqr()));
}

Vector4	Vector4::normalized() const {
	return (*this / this->length());
}

Vector4 Vector4::mul(Vector4 const& v4) const
{
	return Vector4(this->x * v4.x, this->y * v4.y, 
		this->z * v4.z, this->w * v4.w);
}

int Vector4::same(const Vector4& ref)
{
	float offset = 0.00001;
	float x = abs(this->x - ref.x);
	if (x >= offset)
		return -1;
	float y = abs(this->y - ref.y);
	if (y >= offset)
		return -2;
	float z = abs(this->z - ref.z);
	if (z >= offset)
		return -3;
	float w = abs(this->w - ref.w);
	if (w >= offset)
		return -4;
	return 1;
}
