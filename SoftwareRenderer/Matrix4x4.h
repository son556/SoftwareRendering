#pragma once

#include "Vector4.h"

class Matrix4x4
{
public:
	float	m[4][4];
	Matrix4x4() {}
	Matrix4x4(const Matrix4x4& ref);
	Matrix4x4& operator=(const Matrix4x4& ref);
	float& operator[](int idx);
	Matrix4x4	operator*(Matrix4x4 const& m);
	Vector4		operator*(Vector4 const& v);
	Matrix4x4 Trnaspose();
	Matrix4x4 inverse();
};

