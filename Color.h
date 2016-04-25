#pragma once

#include <SFML\Graphics.hpp>
using namespace sf;

Color operator+(const Color& c1, const Color& c2);
Color operator-(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
Color operator/(const Color& c1, const Color& c2);

Color operator+(const Color& c1, float c2);
Color operator-(const Color& c1, float c2);
Color operator*(const Color& c1, float c2);
Color operator/(const Color& c1, float c2);

void operator+=(Color& c1, const Color& c2);
void operator-=(Color& c1, const Color& c2);
void operator*=(Color& c1, const Color& c2);
void operator/=(Color& c1, const Color& c2);

void operator+=(Color& c1, float& c2);
void operator-=(Color& c1, float& c2);
void operator*=(Color& c1, float& c2);
void operator/=(Color& c1, float& c2);
