#include "pch.h"
#include "Color.h"

Color::Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color	Color::operator+(const Color& ref) const {
	return Color(this->r + ref.r,
		this->g + ref.g,
		this->b + ref.b,
		this->a + ref.a);
}

Color	Color::operator-(const Color& ref) const {
	return Color(this->r - ref.r,
		this->g - ref.g,
		this->b - ref.b,
		this->a - ref.a);
}

Color	Color::operator-() const {
	return Color(this->r * -1, this->g * -1, this->b * -1, this->a * -1);
}

Color	Color::operator*(float f) const {
	return Color(this->r * f,
		this->g * f,
		this->b * f,
		this->a * f);
}

Color	Color::operator*(const Color& ref) const {
	return Color(this->r * ref.r,
		this->g * ref.g,
		this->b * ref.b,
		this->a * ref.a);
}
Color	Color::operator/(float f) const {
	return Color(this->r / f,
		this->g / f,
		this->b / f,
		this->a / f);
}
