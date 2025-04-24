#pragma once

#include "Vector3.h"

class Vector4
{
public:
	Vector4() = default;
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 const& v, float w);
	Vector4(const Vector4& ref);
	Vector4& operator=(const Vector4& ref);
	Vector4	operator+(const Vector4& ref) const;
	Vector4	operator-(const Vector4& ref) const;
	Vector4	operator-() const;
	Vector4	operator*(float f) const;
	float	operator*(const Vector4& ref) const;
	Vector4	operator/(float f) const;
	operator Color() const;
	float	lengthSqr() const;
	float	length() const;
	Vector4	normalized() const;
	Vector4 mul(Vector4 const& v4) const;
	int same(const Vector4& ref);

public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};

