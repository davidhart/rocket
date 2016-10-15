#pragma once
#ifndef ROCKET_VECTORMATH_INCLUDED
#define ROCKET_VECTORMATH_INCLUDED

namespace Rocket
{
#pragma pack(push, 1)
	template<typename T> class tvec2
	{
	public:
		T x;
		T y;

		tvec2();
		tvec2(T x, T y);
		tvec2(const T* data);

		T* data();
		const T* data() const;
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
		tvec3(const T* data);

		static tvec3<T> Right();
		static tvec3<T> Up();
		static tvec3<T> Forward();

		T* data();
		const T* data() const;
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
		tvec4(const T* data);

		T* data();
		const T* data() const;
	};

	typedef tvec2<float> vec2;
	typedef tvec3<float> vec3;
	typedef tvec4<float> vec4;

	typedef tvec2<int> ivec2;
	typedef tvec3<int> ivec3;
	typedef tvec4<int> ivec4;

	template<typename T> class tmat4
	{
	public:
		tmat4();
		tmat4(const T* data);
		tmat4(const tvec4<T>& row0, const tvec4<T>& row1, const tvec4<T>& row2, const tvec4<T>& row3);

		T* data();
		const T* data() const;
		tvec4<T> operator[](int row) const;

		static tmat4<T> Identity();
		static tmat4<T> AxisAngle(const tvec3<T>& axis, T angle);

	private:
		T values[16];
	};

	typedef tmat4<float> mat4;
#pragma pack(pop)

	// tvec2 implementation
	template<typename T> inline tvec2<T>::tvec2() :
		x(0), y(0)
	{
	}

	template<typename T> inline tvec2<T>::tvec2(T x, T y) :
		x(x), y(y)
	{
	}

	template<typename T> inline tvec2<T>::tvec2(const T* data)
	{
		memcpy(&x, data, sizeof(T) * 2);
	}

	template<typename T> inline T* tvec2<T>::data()
	{
		return &x;
	}

	template<typename T> inline const T* tvec2<T>::data() const
	{
		return &x;
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

	template<typename T> inline tvec3<T>::tvec3(const T* data)
	{
		memcpy(&x, data, sizeof(T) * 3);
	}

	template<typename T> inline T* tvec3<T>::data()
	{
		return &x;
	}

	template<typename T> inline const T* tvec3<T>::data() const
	{
		return &x;
	}

	template<typename T> inline tvec3<T> tvec3<T>::Right()
	{
		return tvec3<T>(1, 0, 0);
	}

	template<typename T> inline tvec3<T> tvec3<T>::Up()
	{
		return tvec3<T>(0, 1, 0);
	}

	template<typename T> inline tvec3<T> tvec3<T>::Forward()
	{
		return tvec3<T>(0, 0, 1);
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

	template<typename T> inline tvec4<T>::tvec4(const T* data)
	{
		memcpy(&x, data, sizeof(T) * 4);
	}

	template<typename T> inline T* tvec4<T>::data()
	{
		return &x;
	}

	template<typename T> inline const T* tvec4<T>::data() const
	{
		return &x;
	}

	// tmat4 implementation
	template<typename T> inline tmat4<T>::tmat4()
	{
		T def[]=
		{ 
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		};

		memcpy(values, def, sizeof(def));
	}

	template <typename T> inline tmat4<T>::tmat4(const T* data)
	{
		memcpy(values, data, sizeof(T) * 16);
	}

	template <typename T> inline tmat4<T>::tmat4(const tvec4<T>& row0, const tvec4<T>& row1, const tvec4<T>& row2, const tvec4<T>& row3)
	{
		memcpy(values, row0.data(), sizeof(T) * 4);
		memcpy(values + 4, row1.data(), sizeof(T) * 4);
		memcpy(values + 8, row2.data(), sizeof(T) * 4);
		memcpy(values + 12, row3.data(), sizeof(T) * 4);
	}

	template <typename T> inline T* tmat4<T>::data()
	{
		return values;
	}

	template <typename T> inline const T* tmat4<T>::data() const
	{
		return values;
	}

	template <typename T> inline tvec4<T> tmat4<T>::operator[](int row) const
	{
		return tvec4<T>(values[row * 4]);
	}


	template<typename T> inline tmat4<T> tmat4<T>::Identity()
	{
		T def[] =
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		return tmat4<T>(def);
	}

	template<typename T> inline tmat4<T> tmat4<T>::AxisAngle(const tvec3<T>& axis, T angle)
	{
		T c = std::cos(angle);
		T s = std::sin(angle);
		T t = 1 - c;

		T def[] =
		{
			c + axis.x * t,	
				t*axis.x*axis.y - axis.z*s, 
					t*axis.x*axis.z + axis.y * s, 
						0,

			t*axis.x * axis.y + axis.z * s,
				t*axis.y * axis.y + c, 
					t*axis.y * axis.z - axis.x * s, 
						0,

			t * axis.x * axis.z - axis.y * s, 
				t * axis.y * axis.z + axis.x * s, 
					t * axis.z * axis.z + c, 
						0,

			0, 0, 0, 1
		};

		return tmat4<T>(def);
	}
}

#endif