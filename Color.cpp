#include "Color.h"

Color operator+(const Color& c1, const Color& c2)
{
	return Color(
		c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
		c1.a + c2.a
		);
}
Color operator-(const Color& c1, const Color& c2)
{
	return Color(
		c1.r - c2.r,
		c1.g - c2.g,
		c1.b - c2.b,
		c1.a - c2.a
		);
}
Color operator*(const Color& c1, const Color& c2)
{
	return Color(
		c1.r * c2.r,
		c1.g * c2.g,
		c1.b * c2.b,
		c1.a * c2.a
		);
}
Color operator/(const Color& c1, const Color& c2)
{
	return Color(
		c1.r / c2.r,
		c1.g / c2.g,
		c1.b / c2.b,
		c1.a / c2.a
		);
}

Color operator+(const Color& c1, float c2)
{
	return Color(
		c1.r + c2,
		c1.g + c2,
		c1.b + c2,
		c1.a + c2
		);
}
Color operator-(const Color& c1, float c2)
{
	return Color(
		c1.r - c2,
		c1.g - c2,
		c1.b - c2,
		c1.a - c2
		);
}
Color operator*(const Color& c1, float c2)
{
	return Color(
		c1.r * c2,
		c1.g * c2,
		c1.b * c2,
		c1.a * c2
		);
}
Color operator/(const Color& c1, float c2)
{
	return Color(
		c1.r / c2,
		c1.g / c2,
		c1.b / c2,
		c1.a / c2
		);
}

void operator+=(Color& c1, const Color& c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	c1.a += c2.a;
}
void operator-=(Color& c1, const Color& c2)
{
	c1.r -= c2.r;
	c1.g -= c2.g;
	c1.b -= c2.b;
	c1.a -= c2.a;
}
void operator*=(Color& c1, const Color& c2)
{
	c1.r *= c2.r;
	c1.g *= c2.g;
	c1.b *= c2.b;
	c1.a *= c2.a;
}
void operator/=(Color& c1, const Color& c2)
{
	c1.r /= c2.r;
	c1.g /= c2.g;
	c1.b /= c2.b;
	c1.a /= c2.a;
}

void operator+=(Color& c1, float& c2)
{
	c1.r += c2;
	c1.g += c2;
	c1.b += c2;
	c1.a += c2;
}
void operator-=(Color& c1, float& c2)
{
	c1.r -= c2;
	c1.g -= c2;
	c1.b -= c2;
	c1.a -= c2;
}
void operator*=(Color& c1, float& c2)
{
	c1.r *= c2;
	c1.g *= c2;
	c1.b *= c2;
	c1.a *= c2;
}
void operator/=(Color& c1, float& c2)
{
	c1.r /= c2;
	c1.g /= c2;
	c1.b /= c2;
	c1.a /= c2;
}