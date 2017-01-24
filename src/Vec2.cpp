#include "Vec2.hpp"

template <class T>
inline void Vec2<T>::Set(T x, T y)
{
	this->x = x;
	this->y = y;
}
template <class T>
inline void Vec2<T>::Set(Vec2<T> v)
{
	this->x = v.x;
	this->y = v.y;
}

template <class T>
inline T Vec2<T>::Length()
{
	return sqrt(x * x + y * y);
}

template <class T>
inline T Vec2<T>::Dot(Vec2 v)
{
	return Vec2<T>(this->x * v.x + this->y * v.y);
}

template <class T>
inline Vec2<T> Vec2<T>::Normalise()
{
	return (*this) / Length();
}
