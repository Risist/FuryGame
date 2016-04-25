#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include <stdlib.h>
#include <ctime>
#include "Vector2D.h"
#include "ISerializable.h"
#include "XMLloader.h"
#include "Color.h"

template< class Type>
inline bool inIntervalOO(Type a1, Type a2, Type b1, Type b2)
{
	return (b1 > a1 && b1 < a2) || (b2 > a1 && b2 < a2) ||
		(a1 > b1 && a1 < b2) || (a2 > b1 && a2 < b2);
}
template< class Type>
inline bool inIntervalOD(Type a1, Type a2, Type b1, Type b2)
{
	return (b1 > a1 && b1 <= a2) || (b2 > a1 && b2 <= a2) ||
		(a1 > b1 && a1 <= b2) || (a2 > b1 && a2 <= b2);
}
template< class Type>
inline bool inIntervalDO(Type a1, Type a2, Type b1, Type b2)
{
	return (b1 >= a1 && b1 < a2) || (b2 >= a1 && b2 < a2) ||
		(a1 >= b1 && a1 < b2) || (a2 >= b1 && a2 < b2);
}
template< class Type>
inline bool inIntervalDD(Type a1, Type a2, Type b1, Type b2)
{
	return (b1 >= a1 && b1 <= a2) || (b2 >= a1 && b2 <= a2) ||
		(a1 >= b1 && a1 <= b2) || (a2 >= b1 && a2 <= b2);
}

template< class Type>
inline Type clamp(Type value, Type min, Type max)
{
	if (value > max)
		return max;
	else if (value < min)
		return min;
	return value;
}

inline float randRange(float min, float max)
{
	return (double)rand() / RAND_MAX * (max - min) + min;
}



/**/
inline istream& operator>>(istream& stream, Vector2D& v)
{
	stream >> v.x;
	stream >> v.y;
	return stream;
}
inline ostream& operator<<(ostream& stream, const Vector2D& v)
{
	stream << v.x << " ";
	stream << v.y;
	return stream;
}/**/

inline float minimalAngleDiffirence(float angle1, float angle2)
{
	float diffirence = angle2 - angle1;
	
	// remainder after division
	diffirence += -((int)(diffirence / 360)) * 360;

	if (diffirence > 180) diffirence -= 360;

	else if (diffirence < -180) diffirence += 360;

	/*debug*
	cout << "myAngle " << myAngle << "\n";
	cout << "forceAngle " << forceAngle << "\n";
	cout << "diffirence " << diffirence << "\n";
	/**/

	return diffirence;
}