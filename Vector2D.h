#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;

enum {clockwise = 1, anticlockwise = -1};

inline float getInverse(float v, float max, float whenZero = 0)
{
	if (v == 0)
		return whenZero;
	if( abs(1/v) > max)
		return max * ( v > 0 ? 1 : -1);
	

	return 1 / v;

}

class Vector2D : public Vector2f
{
public:
	Vector2D( float _x = 0, float _y = 0)
		: Vector2f(_x,_y)
	{

	}
	Vector2D( const Vector2f& v) : Vector2f( v ) {}

	//float x, y;
	static Vector2D random(const Vector2f& min, const Vector2D& max)
	{
		Vector2D r;
		r.x = (double)rand() / RAND_MAX * (double)(max.x - min.x) + (double)min.x;
		r.y = (double)rand() / RAND_MAX * (double)(max.y - min.y) + (double)min.y;
		return r;
	}


	Vector2D getInverse(const Vector2f& max)
	{
		return Vector2D(::getInverse(x, max.x), ::getInverse(y, max.y) );
	}

	void rotate(float angle, const Vector2f& center = Vector2D())
	{
		angle *= (float)M_PI /180.f;
		Vector2D v = (*this);
		x = center.x + ( v.x - center.x )*cos(angle) - ( v.y - center.y )*sin(angle) ;
		y = center.y + ( v.x - center.y )*sin(angle) + ( v.y - center.y )*cos(angle) ;
	}
	Vector2D getRotated(float angle, const Vector2f& center = Vector2D()) const
	{
		angle *= (float)M_PI /180;
		float _x = center.x + ( x - center.x )*cos(angle) - ( y - center.y )*sin(angle) ;
		float _y = center.y + ( x - center.y )*sin(angle) + ( y - center.y )*cos(angle) ;
		return Vector2D(_x, _y);
	}

	// returnes angle which this vector is directed
	float angle() const
	{
		// to avoid deviding by 0
		if (x == 0)
		{
			if (y >= 0)
				return 180;
			else
				return 0;
		}

		float alfa = atan(y / x) * 180 / M_PI;
		if (x > 0)
			alfa += 90;
		else if (x < 0)
			alfa += 270;

		return alfa;
	}
	// get angle between this and the other vector
	// returns value in range < -360 ; 360 >
	float angle(const Vector2f& other) const
	{
		return angle() - ((Vector2D)other).angle();
	}

	// sets x and y to zero
	void setZero()
	{
		x = 0;
		y = 0;
	}
	// returns true if x and y are zero
	// for float type checking for simple == Vector2D() cant work
	// because it is only approximation to noumber
	bool isZero() const
	{
		return x*x + y*y < std::numeric_limits<float>::min();
	}

	// returns the length of the vector
	float getLenght() const
	{
		return sqrt( getLenghtSq() );
	}
	// returns the length of the vector
	// squared version, faster to compute
	// try to use wether it is possible
	float getLenghtSq() const
	{
		return x*x + y*y;
	}

	// change the lenght of the vector to 1
	// not change the direction
	// does nothing if isZero() returnes true
	void normalise()
	{
		float vector_lenght = getLenght();
		if( vector_lenght > std::numeric_limits<float>::epsilon() )
		{
			x /= vector_lenght;
			y /= vector_lenght;
		}
	}

	// returnes a vector which lenght is equal to 1
	// the direction is the same
	// returnes this one if isZero() returnes true
	Vector2D normalised() const
	{
		float vector_lenght = getLenght();
		if( vector_lenght > std::numeric_limits<float>::epsilon() )
			return Vector2D( x/vector_lenght, y/vector_lenght);
		else
			return *this;
	}

	// the dot product of this and taken as a parametr vectors
	float dot( const Vector2f& other ) const
	{
		return x*other.x + y*other.y;
	}
	

	// returnes an perpendicular vector to this one
	Vector2D prep() const
	{
		return Vector2D( -y, x);
	}

	//returns positive if v2 is clockwise of this vector,
	//negative if anticlockwise (assuming the Y axis is pointing down,
	//X axis to right like a Window app)
	int Sign(const Vector2f& other)const
	{
		if(x*other.y > y*other.x)
			return clockwise;
		return anticlockwise;
	}

	// adjusts x and y so that the length of the vector does not exceed max
	void truncate( float max)
	{
		if( getLenght() > max)
		{
			normalise();
			(*this) *= max;
		}
	}

	// distance between this one and other vectors ( treats as points )
	float distance( const Vector2f& other ) const
	{
		return sqrt( distanceSq(other) );
	}
	float distanceSq( const Vector2f& other) const
	{
		float xSeparation = x - other.x;
		float ySeparation = y - other.y;
		return xSeparation*xSeparation + ySeparation*ySeparation;
	}
	
	// operators for intuitive use

	Vector2D operator-() const
	{
		return (*this) * -1;
	}

	void operator=( const Vector2f& other)
	{
		x = other.x;
		y = other.y;
	}
	void operator+=( const Vector2f& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=( const Vector2f& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=( const Vector2f& other)
	{
		x *= other.x;
		y *= other.y;
	}
	void operator/=( const Vector2f& other)
	{
		x /= other.x;
		y /= other.y;
	}
	
	void operator*=( float other)
	{
		x *= other;
		y *= other;
	}
	void operator/=( float other)
	{
		x /= other;
		y /= other;
	}


	Vector2D operator+( const Vector2f& other) const
	{
		return Vector2D( x + other.x , y + other.y );
	}
	Vector2D operator-( const Vector2f& other) const
	{
		return Vector2D( x - other.x , y - other.y );
	}
	Vector2D operator*( const Vector2f& other) const
	{
		return Vector2D( x * other.x , y * other.y );
	}
	Vector2D operator/( const Vector2f& other) const
	{
		return Vector2D( x / other.x , y / other.y );
	}

	Vector2D operator*( float other) const
	{
		return Vector2D( x * other, y * other);
	}
	Vector2D operator/( float other) const
	{
		return Vector2D( x / other, y / other);
	}

	bool operator==( const Vector2f& other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator!=( const Vector2f& other) const
	{
		return x != other.x || y != other.y;
	}

	
};






