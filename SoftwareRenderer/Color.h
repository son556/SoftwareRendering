#pragma once
class Color
{
public:
	float	r;
	float	g;
	float	b;
	float	a;
	Color() = default;
	Color(float r, float g, float b, float a);
	Color	operator+(const Color& ref) const;
	Color	operator-(const Color& ref) const;
	Color	operator-() const;
	Color	operator*(float f) const;
	Color	operator*(const Color& ref) const;
	Color	operator/(float f) const;
};

