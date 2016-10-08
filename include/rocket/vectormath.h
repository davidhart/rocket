#pragma once
#ifndef ROCKET_VECTORMATH_INCLUDED
#define ROCKET_VECTORMATH_INCLUDED

namespace Rocket
{
	template<typename T> class tvec2
	{
	public:
		T x;
		T y;

		tvec2();
		tvec2(T x, T y);
	};

	template<typename T> class tvec3
	{
	public:
		T x;
		T y;
		T z;

		tvec3();
		tvec3(T x, T y, T z);
		tvec3(const tvec2<T>& v, T z);
	};

	template<typename T> class tvec4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		tvec4();
		tvec4(T x, T y, T z, T w);
		tvec4(const tvec2<T>& v, T z, T w);
		tvec4(const tvec3<T>& v, T w);
	};

	// tvec2 implementation
	template<typename T> inline tvec2<T>::tvec2() :
		x(0), y(0)
	{
	}

	template<typename T> inline tvec2<T>::tvec2(T x, T y) :
		x(x), y(y)
	{
	}


	// tvec3 implementation
	template<typename T> inline tvec3<T>::tvec3() :
		x(0), y(0), z(0)
	{
	}

	template<typename T> inline tvec3<T>::tvec3(T x, T y, T z) :
		x(x), y(y), z(z)
	{
	}

	template<typename T> inline tvec3<T>::tvec3(const tvec2<T>& v, T z) :
		x(v.x), y(v.y), z(z)
	{
	}


	// tvec4 implementation
	template<typename T> inline tvec4<T>::tvec4() :
		x(0), y(0), z(0), w(0)
	{
	}

	template<typename T> inline tvec4<T>::tvec4(T x, T y, T z, T w) :
		x(x), y(y), z(z), w(w)
	{
	}

	template<typename T> inline tvec4<T>::tvec4(const tvec2<T>& v, T z, T w) :
		x(v.x), y(v.y), z(z), w(w)
	{
	}

	template<typename T> inline tvec4<T>::tvec4(const tvec3<T>& v, T w) :
		x(v.x), y(v.y), z(v.z), w(w)
	{
	}

	typedef tvec2<float> vec2;
	typedef tvec3<float> vec3;
	typedef tvec4<float> vec4;

	typedef tvec2<int> ivec2;
	typedef tvec3<int> ivec3;
	typedef tvec4<int> ivec4;
}

#endif