#pragma once
#ifndef ROCKET_VECTORMATH_INCLUDED
#define ROCKET_VECTORMATH_INCLUDED

#include <cmath>
#include <cstring>

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

		T* data();
		const T* data() const;

		static tvec3<T> Right();
		static tvec3<T> Up();
		static tvec3<T> Forward();

		static T Dot(const tvec3<T>& lhs, const tvec3<T>& rhs);
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
		
		static T Dot(const tvec4<T>& lhs, const tvec4<T>& rhs);
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
		T at(int row, int column) const;
		tvec4<T> row(int row) const;
		tvec4<T> col(int column) const;

		tmat4<T> operator* (const tmat4<T>& rhs) const;
		tmat4<T>& operator*= (const tmat4<T>& rhs);

		static tmat4<T> Identity();
		static tmat4<T> AxisAngle(const tvec3<T>& axis, T angle);
		static tmat4<T> Ortho(T left, T right, T top, T bottom, T near, T far);

	private:
		T values[16];
	};

	typedef tmat4<float> mat4;
#pragma pack(pop)

	// util
	template <typename T> inline T rocket_dot(T x0, T y0, T z0, T x1, T y1, T z1)
	{
		return x0 * x1 + y0 * y1 + z0 * z1;
	}

	template<typename T> inline T rocket_dot(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1)
	{
		return x0 * x1 + y0 * y1 + z0 * z1 + w0 * w1;
	}

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
        std::memcpy(&x, data, sizeof(T) * 2);
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
        std::memcpy(&x, data, sizeof(T) * 3);
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

	template<typename T> inline T tvec3<T>::Dot(const tvec3<T>& lhs, const tvec3<T>& rhs)
	{
		return rocket_dot(lhs.x, lhs.y, lhs.z, rhs.x, rhs.y, rhs.z);
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
        std::memcpy(&x, data, sizeof(T) * 4);
	}

	template<typename T> inline T* tvec4<T>::data()
	{
		return &x;
	}

	template<typename T> inline const T* tvec4<T>::data() const
	{
		return &x;
	}

	template<typename T> inline T tvec4<T>::Dot(const tvec4<T>& lhs, const tvec4<T>& rhs)
	{
		return rocket_dot<T>(lhs.x, lhs.y, lhs.z, lhs.w, rhs.x, rhs.y, rhs.z, rhs.w);
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

        std::memcpy(values, def, sizeof(def));
	}

	template <typename T> inline tmat4<T>::tmat4(const T* data)
	{
        std::memcpy(values, data, sizeof(T) * 16);
	}

	template <typename T> inline tmat4<T>::tmat4(const tvec4<T>& row0, const tvec4<T>& row1, const tvec4<T>& row2, const tvec4<T>& row3)
	{
        std::memcpy(values, row0.data(), sizeof(T) * 4);
        std::memcpy(values + 4, row1.data(), sizeof(T) * 4);
        std::memcpy(values + 8, row2.data(), sizeof(T) * 4);
        std::memcpy(values + 12, row3.data(), sizeof(T) * 4);
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
		return this->row(row);
	}

	template <typename T> inline T tmat4<T>::at(int row, int column) const
	{
		return values[row * 4 + column];
	}

	template <typename T> inline tvec4<T> tmat4<T>::row(int row) const
	{
		return tvec4<T>(values + (row * 4));
	}
	
	template <typename T> inline tvec4<T> tmat4<T>::col(int column) const
	{
		return tvec4<T>(at(0, column), at(1, column), at(2, column), at(3, column));
	}

	template <typename T> inline tmat4<T> tmat4<T>::operator*(const tmat4<T>& rhs) const
	{
		tvec4<T> l[] =
		{
			row(0),
			row(1),
			row(2),
			row(3)
		};

		tvec4<T> r[] =
		{
			rhs.col(0),
			rhs.col(1),
			rhs.col(2),
			rhs.col(3)
		};

		T data[] = 
		{
			tvec4<T>::Dot(l[0], r[0]), tvec4<T>::Dot(l[0], r[1]), tvec4<T>::Dot(l[0], r[2]), tvec4<T>::Dot(l[0], r[3]),
			tvec4<T>::Dot(l[1], r[0]), tvec4<T>::Dot(l[1], r[1]), tvec4<T>::Dot(l[1], r[2]), tvec4<T>::Dot(l[1], r[3]),
			tvec4<T>::Dot(l[2], r[0]), tvec4<T>::Dot(l[2], r[1]), tvec4<T>::Dot(l[2], r[2]), tvec4<T>::Dot(l[2], r[3]),
			tvec4<T>::Dot(l[3], r[0]), tvec4<T>::Dot(l[3], r[1]), tvec4<T>::Dot(l[3], r[2]), tvec4<T>::Dot(l[3], r[3]),
		};

		return tmat4<T>(data);
	}

	template <typename T> inline tmat4<T>& tmat4<T>::operator*=(const tmat4<T>& rhs)
	{
		*this = *this * rhs;
		return *this;
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

	template <typename T> inline tmat4<T> tmat4<T>::Ortho(T left, T right, T top, T bottom, T near, T far)
	{
		T width = right - left;
		T height = top - bottom;
		T depth = far - near;

		T def[] =
		{
			2 / width,	0,				0,				-(right + left) / width,
			0,			2 / height,		0,				-(top + bottom) / height,
			0,			0,				-2 / (depth),	-(far + near) / depth,
			0,			0,				0,				1
		};

		return tmat4<T>(def);
	}
}

#endif
