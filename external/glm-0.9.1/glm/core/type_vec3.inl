///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-22
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/type_tvec3.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace detail
	{
		template <typename T>
		inline typename tvec3<T>::size_type tvec3<T>::value_size()
		{
			return 3;
		}

		//////////////////////////////////////
		// Accesses

		template <typename T>
		inline typename tvec3<T>::value_type & 
		tvec3<T>::operator[]
		(
			size_type i
		)
		{
			assert(i < value_size());
			return (&x)[i];
		}

		template <typename T>
		inline typename tvec3<T>::value_type const & 
		tvec3<T>::operator[]
		(
			size_type i
		) const
		{
			assert(i < value_size());
			return (&x)[i];
		}

		//////////////////////////////////////
		// Implicit basic constructors

		template <typename T>
		inline tvec3<T>::tvec3() :
			x(value_type(0)),
			y(value_type(0)),
			z(value_type(0))
		{}

		template <typename T>
		inline tvec3<T>::tvec3
		(
			ctor
		)
		{}

		template <typename T>
		inline tvec3<T>::tvec3
		(
			tvec3<T> const & v
		) :
			x(v.x),
			y(v.y),
			z(v.z)
		{}

		//////////////////////////////////////
		// Explicit basic constructors

		template <typename T>
		inline tvec3<T>::tvec3
		(
			value_type const & s
		) :
			x(s),
			y(s),
			z(s)
		{}

		template <typename T>
		inline tvec3<T>::tvec3
		(
			value_type const & s0, 
			value_type const & s1, 
			value_type const & s2
		) :
			x(s0),
			y(s1),
			z(s2)
		{}

		//////////////////////////////////////
		// Swizzle constructors

		template <typename T>
		inline tvec3<T>::tvec3
		(
			tref3<T> const & r
		) :
			x(r.x),
			y(r.y),
			z(r.z)
		{}

		//////////////////////////////////////
		// Convertion scalar constructors
		
		template <typename T>
		template <typename U> 
		inline tvec3<T>::tvec3
		(
			U const & s
		) :
			x(value_type(s)),
			y(value_type(s)),
			z(value_type(s))
		{}

		template <typename T>
		template <typename A, typename B, typename C> 
		inline tvec3<T>::tvec3
		(
			A const & x, 
			B const & y, 
			C const & z
		) :
			x(value_type(x)),
			y(value_type(y)),
			z(value_type(z))
		{}

		//////////////////////////////////////
		// Convertion vector constructors

		template <typename T>
		template <typename A, typename B> 
		inline tvec3<T>::tvec3
		(
			tvec2<A> const & v, 
			B const & s
		) :
			x(value_type(v.x)),
			y(value_type(v.y)),
			z(value_type(s))
		{}

		template <typename T>
		template <typename A, typename B> 
		inline tvec3<T>::tvec3
		(	
			A const & s, 
			tvec2<B> const & v
		) :
			x(value_type(s)),
			y(value_type(v.x)),
			z(value_type(v.y))
		{}

		template <typename T>
		template <typename U> 
		inline tvec3<T>::tvec3
		(
			tvec3<U> const & v
		) :
			x(value_type(v.x)),
			y(value_type(v.y)),
			z(value_type(v.z))
		{}

		template <typename T>
		template <typename U> 
		inline tvec3<T>::tvec3
		(
			tvec4<U> const & v
		) :
			x(value_type(v.x)),
			y(value_type(v.y)),
			z(value_type(v.z))
		{}

		//////////////////////////////////////
		// Unary arithmetic operators

		template <typename T>
		inline tvec3<T>& tvec3<T>::operator= 
		(
			tvec3<T> const & v
		)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T>& tvec3<T>::operator= 
		(
			tvec3<U> const & v
		)
		{
			this->x = T(v.x);
			this->y = T(v.y);
			this->z = T(v.z);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator+=
		(
			U const & s
		)
		{
			this->x += T(s);
			this->y += T(s);
			this->z += T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator+=
		(
			tvec3<U> const & v
		)
		{
			this->x += T(v.x);
			this->y += T(v.y);
			this->z += T(v.z);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator-=
		(
			U const & s
		)
		{
			this->x -= T(s);
			this->y -= T(s);
			this->z -= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator-=
		(
			tvec3<U> const & v
		)
		{
			this->x -= T(v.x);
			this->y -= T(v.y);
			this->z -= T(v.z);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator*=
		(
			U const & s
		)
		{
			this->x *= T(s);
			this->y *= T(s);
			this->z *= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator*=
		(
			tvec3<U> const & v
		)
		{
			this->x *= T(v.x);
			this->y *= T(v.y);
			this->z *= T(v.z);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator/=
		(
			U const & s
		)
		{
			this->x /= T(s);
			this->y /= T(s);
			this->z /= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator/=
		(
			tvec3<U> const & v
		)
		{
			this->x /= T(v.x);
			this->y /= T(v.y);
			this->z /= T(v.z);
			return *this;
		}

		template <typename T>
		inline tvec3<T> & tvec3<T>::operator++()
		{
			++this->x;
			++this->y;
			++this->z;
			return *this;
		}

		template <typename T>
		inline tvec3<T> & tvec3<T>::operator--()
		{
			--this->x;
			--this->y;
			--this->z;
			return *this;
		}

		//////////////////////////////////////
		// Boolean operators

		template <typename T> 
		inline bool operator==
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
		}

		template <typename T> 
		inline bool operator!=
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
		}

		//////////////////////////////////////
		// Unary bit operators

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator%=
		(
			U const & s
		)
		{
			this->x %= s;
			this->y %= s;
			this->z %= s;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator%=
		(
			tvec3<U> const & v
		)
		{
			this->x %= v.x;
			this->y %= v.y;
			this->z %= v.z;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator&=
		(	
			U const & s
		)
		{
			this->x &= s;
			this->y &= s;
			this->z &= s;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator&=
		(
			tvec3<U> const & v
		)
		{
			this->x &= v.x;
			this->y &= v.y;
			this->z &= v.z;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator|=
		(
			U const & s
		)
		{
			this->x |= s;
			this->y |= s;
			this->z |= s;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator|=
		(
			tvec3<U> const & v
		)
		{
			this->x |= v.x;
			this->y |= v.y;
			this->z |= v.z;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator^=
		(
			U const & s
		)
		{
			this->x ^= s;
			this->y ^= s;
			this->z ^= s;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator^=
		(
			tvec3<U> const & v
		)
		{
			this->x ^= v.x;
			this->y ^= v.y;
			this->z ^= v.z;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator<<=
		(
			U const & s
		)
		{
			this->x <<= s;
			this->y <<= s;
			this->z <<= s;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator<<=
		(
			tvec3<U> const & v
		)
		{
			this->x <<= T(v.x);
			this->y <<= T(v.y);
			this->z <<= T(v.z);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator>>=
		(
			U const & s
		)
		{
			this->x >>= T(s);
			this->y >>= T(s);
			this->z >>= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec3<T> & tvec3<T>::operator>>=
		(
			tvec3<U> const & v
		)
		{
			this->x >>= T(v.x);
			this->y >>= T(v.y);
			this->z >>= T(v.z);
			return *this;
		}

		//////////////////////////////////////
		// Swizzle operators

		template <typename T>
		inline typename tvec3<T>::value_type 
		tvec3<T>::swizzle
		(
			comp x
		) const
		{
			return (*this)[x];
		}

		template <typename T>
		inline tvec2<T> tvec3<T>::swizzle
		(
			comp x, 
			comp y
		) const
		{
			return tvec2<T>(
				(*this)[x],
				(*this)[y]);
		}

		template <typename T>
		inline tvec3<T> tvec3<T>::swizzle
		(
			comp x, 
			comp y, 
			comp z
		) const
		{
			return tvec3<T>(
				(*this)[x],
				(*this)[y],
				(*this)[z]);
		}

		template <typename T>
		inline tvec4<T> tvec3<T>::swizzle
		(
			comp x, 
			comp y, 
			comp z, 
			comp w
		) const
		{
			return tvec4<T>(
				(*this)[x],
				(*this)[y],
				(*this)[z],
				(*this)[w]);
		}

		template <typename T>
		inline tref3<T> tvec3<T>::swizzle
		(
			comp x, 
			comp y, 
			comp z
		)
		{
			return tref3<T>(
				(*this)[x],
				(*this)[y],
				(*this)[z]);
		}

		//////////////////////////////////////
		// Binary arithmetic operators

		template <typename T> 
		inline tvec3<T> operator+
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x + T(s),
				v.y + T(s),
				v.z + T(s));
		}

		template <typename T> 
		inline tvec3<T> operator+ 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) + v.x,
				T(s) + v.y,
				T(s) + v.z);
		}

		template <typename T> 
		inline tvec3<T> operator+ 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x + T(v2.x),
				v1.y + T(v2.y),
				v1.z + T(v2.z));
		}

		//operator-
		template <typename T> 
		inline tvec3<T> operator- 
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x - T(s),
				v.y - T(s),
				v.z - T(s));
		}

		template <typename T> 
		inline tvec3<T> operator- 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) - v.x,
				T(s) - v.y,
				T(s) - v.z);
		}

		template <typename T> 
		inline tvec3<T> operator- 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x - T(v2.x),
				v1.y - T(v2.y),
				v1.z - T(v2.z));
		}

		//operator*
		template <typename T> 
		inline tvec3<T> operator*
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x * T(s),
				v.y * T(s),
				v.z * T(s));
		}

		template <typename T> 
		inline tvec3<T> operator* 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) * v.x,
				T(s) * v.y,
				T(s) * v.z);
		}

		template <typename T> 
		inline tvec3<T> operator* 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x * T(v2.x),
				v1.y * T(v2.y),
				v1.z * T(v2.z));
		}

		//operator/
		template <typename T> 
		inline tvec3<T> operator/
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x / T(s),
				v.y / T(s),
				v.z / T(s));
		}

		template <typename T> 
		inline tvec3<T> operator/ 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) / v.x,
				T(s) / v.y,
				T(s) / v.z);
		}

		template <typename T> 
		inline tvec3<T> operator/ 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x / T(v2.x),
				v1.y / T(v2.y),
				v1.z / T(v2.z));
		}

		// Unary constant operators
		template <typename T> 
		inline tvec3<T> operator- 
		(
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				-v.x, 
				-v.y, 
				-v.z);
		}

		template <typename T> 
		inline tvec3<T> operator++ 
		(
			tvec3<T> const & v, 
			int
		)
		{
			return tvec3<T>(
				v.x + T(1), 
				v.y + T(1), 
				v.z + T(1));
		}

		template <typename T> 
		inline tvec3<T> operator-- 
		(
			tvec3<T> const & v, 
			int
		)
		{
			return tvec3<T>(
				v.x - T(1), 
				v.y - T(1), 
				v.z - T(1));
		}

		//////////////////////////////////////
		// Binary bit operators

		template <typename T>
		inline tvec3<T> operator% 
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x % T(s),
				v.y % T(s),
				v.z % T(s));
		}

		template <typename T>
		inline tvec3<T> operator%
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) % v.x,
				T(s) % v.y,
				T(s) % v.z);
		}

		template <typename T>
		inline tvec3<T> operator% 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x % T(v2.x),
				v1.y % T(v2.y),
				v1.z % T(v2.z));
		}

		template <typename T>
		inline tvec3<T> operator& 
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x & T(s),
				v.y & T(s),
				v.z & T(s));
		}

		template <typename T>
		inline tvec3<T> operator& 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) & v.x,
				T(s) & v.y,
				T(s) & v.z);
		}

		template <typename T>
		inline tvec3<T> operator& 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x & T(v2.x),
				v1.y & T(v2.y),
				v1.z & T(v2.z));
		}

		template <typename T>
		inline tvec3<T> operator| 
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x | T(s),
				v.y | T(s),
				v.z | T(s));
		}

		template <typename T>
		inline tvec3<T> operator| 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) | v.x,
				T(s) | v.y,
				T(s) | v.z);
		}

		template <typename T>
		inline tvec3<T> operator| 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x | T(v2.x),
				v1.y | T(v2.y),
				v1.z | T(v2.z));
		}
		
		template <typename T>
		inline tvec3<T> operator^ 
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x ^ T(s),
				v.y ^ T(s),
				v.z ^ T(s));
		}

		template <typename T>
		inline tvec3<T> operator^ 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) ^ v.x,
				T(s) ^ v.y,
				T(s) ^ v.z);
		}

		template <typename T>
		inline tvec3<T> operator^ 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x ^ T(v2.x),
				v1.y ^ T(v2.y),
				v1.z ^ T(v2.z));
		}

		template <typename T>
		inline tvec3<T> operator<< 
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x << T(s),
				v.y << T(s),
				v.z << T(s));
		}

		template <typename T>
		inline tvec3<T> operator<< 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				T(s) << v.x,
				T(s) << v.y,
				T(s) << v.z);
		}

		template <typename T>
		inline tvec3<T> operator<< 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x << T(v2.x),
				v1.y << T(v2.y),
				v1.z << T(v2.z));
		}

		template <typename T>
		inline tvec3<T> operator>> 
		(
			tvec3<T> const & v, 
			T const & s
		)
		{
			return tvec3<T>(
				v.x >> T(s),
				v.y >> T(s),
				v.z >> T(s));
		}

		template <typename T>
		inline tvec3<T> operator>> 
		(
			T const & s, 
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				s >> T(v.x),
				s >> T(v.y),
				s >> T(v.z));
		}

		template <typename T>
		inline tvec3<T> operator>> 
		(
			tvec3<T> const & v1, 
			tvec3<T> const & v2
		)
		{
			return tvec3<T>(
				v1.x >> T(v2.x),
				v1.y >> T(v2.y),
				v1.z >> T(v2.z));
		}

		template <typename T> 
		inline tvec3<T> operator~ 
		(
			tvec3<T> const & v
		)
		{
			return tvec3<T>(
				~v.x,
				~v.y,
				~v.z);
		}

		//////////////////////////////////////
		// tref definition

		template <typename T> 
		inline tref3<T>::tref3(T & x, T & y, T & z) :
			x(x),
			y(y),
			z(z)
		{}

		template <typename T> 
		inline tref3<T>::tref3
		(
			tref3<T> const & r
		) :
			x(r.x),
			y(r.y),
			z(r.z)
		{}

		template <typename T> 
		inline tref3<T>::tref3
		(
			tvec3<T> const & v
		) :
			x(v.x),
			y(v.y),
			z(v.z)
		{}

		template <typename T> 
		inline tref3<T> & tref3<T>::operator=
		(
			tref3<T> const & r
		)
		{
			x = r.x;
			y = r.y;
			z = r.z;
			return *this;
		}

		template <typename T> 
		inline tref3<T> & tref3<T>::operator=
		(
			tvec3<T> const & v
		)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

	}//namespace detail
}//namespace glm
