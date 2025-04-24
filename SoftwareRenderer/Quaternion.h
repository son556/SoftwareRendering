#pragma once

class Vector3;
class Vector4;

class Quaternion
{
public:
	Quaternion(Vector3 const& axis, float degree);
	~Quaternion() = default;
	Quaternion	operator*(Quaternion const& q) const;
	Vector3		operator*(Vector3 const& v) const;
	Vector4		operator*(Vector4 const& v) const;
	Quaternion	operator~() const;

private:
	Quaternion() = delete;
	Quaternion(float w, float x, float y, float z);
	Quaternion(Quaternion const&) = default;
	Quaternion& operator=(Quaternion const&) = default;

public:
	float w;
	float x;
	float y;
	float z;
};

