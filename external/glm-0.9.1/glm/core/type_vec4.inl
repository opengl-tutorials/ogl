///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-23
// Updated : 2010-02-05
// Licence : This source is under MIT License
// File    : glm/core/type_tvec4.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace detail
	{
		template <typename T>
		inline typename tvec4<T>::size_type tvec4<T>::value_size()
		{
			return 4;
		}

		//////////////////////////////////////
		// Accesses

		template <typename T>
		inline typename tvec4<T>::value_type & 
		tvec4<T>::operator[]
		(
			size_type i
		)
		{
			assert(i < value_size());
			return (&x)[i];
		}

		template <typename T>
		inline typename tvec4<T>::value_type const & 
		tvec4<T>::operator[]
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
		inline tvec4<T>::tvec4() :
			x(value_type(0)),
			y(value_type(0)),
			z(value_type(0)),
			w(value_type(0))
		{}

		template <typename T> 
		inline tvec4<T>::tvec4
		(
			ctor
		)
		{}

		template <typename T>
		inline tvec4<T>::tvec4
		(
			type const & v
		) :
			x(v.x),
			y(v.y),
			z(v.z),
			w(v.w)
		{}

		//////////////////////////////////////
		// Explicit basic constructors

		template <typename T>
		inline tvec4<T>::tvec4
		(
			value_type const & s
		) :
			x(s),
			y(s),
			z(s),
			w(s)
		{}

		template <typename T>
		inline tvec4<T>::tvec4
		(
			value_type const & s1, 
			value_type const & s2, 
			value_type const & s3, 
			value_type const & s4
		) :
			x(s1),
			y(s2),
			z(s3),
			w(s4)
		{}

		//////////////////////////////////////
		// Swizzle constructors

		template <typename T>
		inline tvec4<T>::tvec4
		(
			tref4<T> const & r
		) :
			x(r.x),
			y(r.y),
			z(r.z),
			w(r.w)
		{}

		//////////////////////////////////////
		// Convertion scalar constructors
		
		template <typename T>
		template <typename U> 
		inline tvec4<T>::tvec4
		(
			U const & x
		) :
			x(value_type(x)),
			y(value_type(x)),
			z(value_type(x)),
			w(value_type(x))
		{}

		template <typename T>
		template <typename A, typename B, typename C, typename D> 
		inline tvec4<T>::tvec4
		(
			A const & x, 
			B const & y, 
			C const & z, 
			D const & w
		) :
			x(value_type(x)),
			y(value_type(y)),
			z(value_type(z)),
			w(value_type(w))
		{}

		//////////////////////////////////////
		// Convertion vector constructors

		template <typename T>
		template <typename A, typename B, typename C> 
		inline tvec4<T>::tvec4
		(
			tvec2<A> const & v, 
			B const & s1, 
			C const & s2
		) :
			x(value_type(v.x)),
			y(value_type(v.y)),
			z(value_type(s1)),
			w(value_type(s2))
		{}

		template <typename T>
		template <typename A, typename B, typename C> 
		inline tvec4<T>::tvec4
		(
			A const & s1, 
			tvec2<B> const & v, 
			C const & s2
		) :
			x(value_type(s1)),
			y(value_type(v.x)),
			z(value_type(v.y)),
			w(value_type(s2))
		{}

		template <typename T>
		template <typename A, typename B, typename C> 
		inline tvec4<T>::tvec4
		(
			A const & s1, 
			B const & s2, 
			tvec2<C> const & v
		) :
			x(value_type(s1)),
			y(value_type(s2)),
			z(value_type(v.x)),
			w(value_type(v.y))
		{}

		template <typename T>
		template <typename A, typename B> 
		inline tvec4<T>::tvec4
		(
			tvec3<A> const & v, 
			B const & s
		) :
			x(value_type(v.x)),
			y(value_type(v.y)),
			z(value_type(v.z)),
			w(value_type(s))
		{}

		template <typename T>
		template <typename A, typename B> 
		inline tvec4<T>::tvec4
		(
			A const & s, 
			tvec3<B> const & v
		) :
			x(value_type(s)),
			y(value_type(v.x)),
			z(value_type(v.y)),
			w(value_type(v.z))
		{}

		template <typename T>
		template <typename A, typename B> 
		inline tvec4<T>::tvec4
		(
			tvec2<A> const & v1, 
			tvec2<B> const & v2
		) :
			x(value_type(v1.x)),
			y(value_type(v1.y)),
			z(value_type(v2.x)),
			w(value_type(v2.y))
		{}

		template <typename T>
		template <typename U> 
		inline tvec4<T>::tvec4
		(
			tvec4<U> const & v
		) :
			x(value_type(v.x)),
			y(value_type(v.y)),
			z(value_type(v.z)),
			w(value_type(v.w))
		{}

		//////////////////////////////////////
		// Unary arithmetic operators

		template <typename T>
		inline tvec4<T> & tvec4<T>::operator= 
		(
			tvec4<T> const & v
		)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator= 
		(
			tvec4<U> const & v
		)
		{
			this->x = T(v.x);
			this->y = T(v.y);
			this->z = T(v.z);
			this->w = T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator+=
		(
			U const & s
		)
		{
			this->x += T(s);
			this->y += T(s);
			this->z += T(s);
			this->w += T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator+=
		(
			tvec4<U> const & v
		)
		{
			this->x += T(v.x);
			this->y += T(v.y);
			this->z += T(v.z);
			this->w += T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator-=
		(
			U const & s
		)
		{
			this->x -= T(s);
			this->y -= T(s);
			this->z -= T(s);
			this->w -= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator-=
		(
			tvec4<U> const & v
		)
		{
			this->x -= T(v.x);
			this->y -= T(v.y);
			this->z -= T(v.z);
			this->w -= T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator*=
		(
			U const & s
		)
		{
			this->x *= T(s);
			this->y *= T(s);
			this->z *= T(s);
			this->w *= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator*=
		(
			tvec4<U> const & v
		)
		{
			this->x *= T(v.x);
			this->y *= T(v.y);
			this->z *= T(v.z);
			this->w *= T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator/=
		(
			U const & s
		)
		{
			this->x /= T(s);
			this->y /= T(s);
			this->z /= T(s);
			this->w /= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator/=
		(
			tvec4<U> const & v
		)
		{
			this->x /= T(v.x);
			this->y /= T(v.y);
			this->z /= T(v.z);
			this->w /= T(v.w);
			return *this;
		}

		template <typename T>
		inline tvec4<T> & tvec4<T>::operator++()
		{
			++this->x;
			++this->y;
			++this->z;
			++this->w;
			return *this;
		}

		template <typename T>
		inline tvec4<T> & tvec4<T>::operator--()
		{
			--this->x;
			--this->y;
			--this->z;
			--this->w;
			return *this;
		}

		//////////////////////////////////////
		// Unary bit operators

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator%=
		(
			U const & s
		)
		{
			this->x %= T(s);
			this->y %= T(s);
			this->z %= T(s);
			this->w %= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator%=
		(
			tvec4<U> const & v
		)
		{
			this->x %= T(v.x);
			this->y %= T(v.y);
			this->z %= T(v.z);
			this->w %= T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator&=
		(
			U const & s
		)
		{
			this->x &= T(s);
			this->y &= T(s);
			this->z &= T(s);
			this->w &= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator&=
		(
			tvec4<U> const & v
		)
		{
			this->x &= T(v.x);
			this->y &= T(v.y);
			this->z &= T(v.z);
			this->w &= T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator|=
		(
			U const & s
		)
		{
			this->x |= T(s);
			this->y |= T(s);
			this->z |= T(s);
			this->w |= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator|=
		(
			tvec4<U> const & v
		)
		{
			this->x |= T(v.x);
			this->y |= T(v.y);
			this->z |= T(v.z);
			this->w |= T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator^=
		(
			U const & s
		)
		{
			this->x ^= T(s);
			this->y ^= T(s);
			this->z ^= T(s);
			this->w ^= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator^=
		(
			tvec4<U> const & v
		)
		{
			this->x ^= T(v.x);
			this->y ^= T(v.y);
			this->z ^= T(v.z);
			this->w ^= T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator<<=
		(
			U const & s
		)
		{
			this->x <<= T(s);
			this->y <<= T(s);
			this->z <<= T(s);
			this->w <<= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator<<=
		(
			tvec4<U> const & v
		)
		{
			this->x <<= T(v.x);
			this->y <<= T(v.y);
			this->z <<= T(v.z);
			this->w <<= T(v.w);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator>>=
		(
			U const & s
		)
		{
			this->x >>= T(s);
			this->y >>= T(s);
			this->z >>= T(s);
			this->w >>= T(s);
			return *this;
		}

		template <typename T>
		template <typename U> 
		inline tvec4<T> & tvec4<T>::operator>>=
		(
			tvec4<U> const & v
		)
		{
			this->x >>= T(v.x);
			this->y >>= T(v.y);
			this->z >>= T(v.z);
			this->w >>= T(v.w);
			return *this;
		}

		//////////////////////////////////////
		// Swizzle operators

		template <typename T>
		inline typename tvec4<T>::value_type 
		tvec4<T>::swizzle
		(	
			comp x
		) const
		{
			return (*this)[x];
		}

		template <typename T>
		inline tvec2<T> tvec4<T>::swizzle
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
		inline tvec3<T> tvec4<T>::swizzle
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
		inline tvec4<T> tvec4<T>::swizzle
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
		inline tref4<T> tvec4<T>::swizzle
		(
			comp x, 
			comp y, 
			comp z, 
			comp w
		)
		{
			return tref4<T>(
				(*this)[x],
				(*this)[y],
				(*this)[z],
				(*this)[w]);
		}

		//////////////////////////////////////
		// Binary arithmetic operators

		template <typename T> 
		inline tvec4<T> operator+ 
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x + s,
				v.y + s,
				v.z + s,
				v.w + s);
		}

		template <typename T> 
		inline tvec4<T> operator+ 
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s + v.x,
				s + v.y,
				s + v.z,
				s + v.w);
		}

		template <typename T> 
		inline tvec4<T> operator+ 
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x + v2.x,
				v1.y + v2.y,
				v1.z + v2.z,
				v1.w + v2.w);
		}

		//operator-
		template <typename T> 
		inline tvec4<T> operator- 
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x - s,
				v.y - s,
				v.z - s,
				v.w - s);
		}

		template <typename T> 
		inline tvec4<T> operator- 
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s - v.x,
				s - v.y,
				s - v.z,
				s - v.w);
		}

		template <typename T> 
		inline tvec4<T> operator- 
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x - v2.x,
				v1.y - v2.y,
				v1.z - v2.z,
				v1.w - v2.w);
		}

		//operator*
		template <typename T> 
		inline tvec4<T> operator* 
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x * s,
				v.y * s,
				v.z * s,
				v.w * s);
		}

		template <typename T> 
		inline tvec4<T> operator* 
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s * v.x,
				s * v.y,
				s * v.z,
				s * v.w);
		}

		template <typename T> 
		inline tvec4<T> operator*
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x * v2.x,
				v1.y * v2.y,
				v1.z * v2.z,
				v1.w * v2.w);
		}

		//operator/
		template <typename T> 
		inline tvec4<T> operator/ 
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x / s,
				v.y / s,
				v.z / s,
				v.w / s);
		}

		template <typename T> 
		inline tvec4<T> operator/ 
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s / v.x,
				s / v.y,
				s / v.z,
				s / v.w);
		}

		template <typename T> 
		inline tvec4<T> operator/ 
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x / v2.x,
				v1.y / v2.y,
				v1.z / v2.z,
				v1.w / v2.w);
		}

		// Unary constant operators
		template <typename T> 
		inline tvec4<T> operator- 
		(
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				-v.x, 
				-v.y, 
				-v.z, 
				-v.w);
		}

		template <typename T> 
		inline tvec4<T> operator++ 
		(
			tvec4<T> const & v, 
			int
		)
		{
			typename tvec4<T>::value_type One(1);
			return tvec4<T>(
				v.x + One, 
				v.y + One, 
				v.z + One, 
				v.w + One);
		}

		template <typename T> 
		inline tvec4<T> operator-- 
		(
			tvec4<T> const & v, 
			int
		)
		{
			typename tvec4<T>::value_type One(1);
			return tvec4<T>(
				v.x - One, 
				v.y - One, 
				v.z - One, 
				v.w - One);
		}

		//////////////////////////////////////
		// Boolean operators

		template <typename T> 
		inline bool operator==
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
		}

		template <typename T> 
		inline bool operator!=
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w);
		}

		//////////////////////////////////////
		// Binary bit operators

		template <typename T>
		inline tvec4<T> operator% 
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x % s,
				v.y % s,
				v.z % s,
				v.w % s);
		}

		template <typename T>
		inline tvec4<T> operator% 
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s % v.x,
				s % v.y,
				s % v.z,
				s % v.w);
		}

		template <typename T>
		inline tvec4<T> operator%
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x % v2.x,
				v1.y % v2.y,
				v1.z % v2.z,
				v1.w % v2.w);
		}

		template <typename T>
		inline tvec4<T> operator& 
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x & s,
				v.y & s,
				v.z & s,
				v.w & s);
		}

		template <typename T>
		inline tvec4<T> operator& 
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s & v.x,
				s & v.y,
				s & v.z,
				s & v.w);
		}

		template <typename T>
		inline tvec4<T> operator&
		(
			tvec4<T> const & v1,
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x & v2.x,
				v1.y & v2.y,
				v1.z & v2.z,
				v1.w & v2.w);
		}

		template <typename T>
		inline tvec4<T> operator|
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x | s,
				v.y | s,
				v.z | s,
				v.w | s);
		}

		template <typename T>
		inline tvec4<T> operator|
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s | v.x,
				s | v.y,
				s | v.z,
				s | v.w);
		}

		template <typename T>
		inline tvec4<T> operator|
		(
			tvec4<T> const & v1, 
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x | v2.x,
				v1.y | v2.y,
				v1.z | v2.z,
				v1.w | v2.w);
		}
		
		template <typename T>
		inline tvec4<T> operator^
		(
			tvec4<T> const & v, 
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x ^ s,
				v.y ^ s,
				v.z ^ s,
				v.w ^ s);
		}

		template <typename T>
		inline tvec4<T> operator^
		(
			typename tvec4<T>::value_type const & s, 
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s ^ v.x,
				s ^ v.y,
				s ^ v.z,
				s ^ v.w);
		}

		template <typename T>
		inline tvec4<T> operator^
		(
			tvec4<T> const & v1,
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x ^ v2.x,
				v1.y ^ v2.y,
				v1.z ^ v2.z,
				v1.w ^ v2.w);
		}

		template <typename T>
		inline tvec4<T> operator<<
		(
			tvec4<T> const & v,
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x << s,
				v.y << s,
				v.z << s,
				v.w << s);
		}

		template <typename T>
		inline tvec4<T> operator<<
		(
			typename tvec4<T>::value_type const & s,
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s << v.x,
				s << v.y,
				s << v.z,
				s << v.w);
		}

		template <typename T>
		inline tvec4<T> operator<<
		(
			tvec4<T> const & v1,
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x << v2.x,
				v1.y << v2.y,
				v1.z << v2.z,
				v1.w << v2.w);
		}

		template <typename T>
		inline tvec4<T> operator>>
		(
			tvec4<T> const & v,
			typename tvec4<T>::value_type const & s
		)
		{
			return tvec4<T>(
				v.x >> s,
				v.y >> s,
				v.z >> s,
				v.w >> s);
		}

		template <typename T>
		inline tvec4<T> operator>>
		(
			typename tvec4<T>::value_type const & s,
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				s >> v.x,
				s >> v.y,
				s >> v.z,
				s >> v.w);
		}

		template <typename T>
		inline tvec4<T> operator>>
		(
			tvec4<T> const & v1,
			tvec4<T> const & v2
		)
		{
			return tvec4<T>(
				v1.x >> v2.x,
				v1.y >> v2.y,
				v1.z >> v2.z,
				v1.w >> v2.w);
		}

		template <typename T> 
		inline tvec4<T> operator~
		(
			tvec4<T> const & v
		)
		{
			return tvec4<T>(
				~v.x,
				~v.y,
				~v.z,
				~v.w);
		}

		//////////////////////////////////////
		// tref definition

		template <typename T> 
		tref4<T>::tref4
		(
			T & x, 
			T & y, 
			T & z, 
			T & w
		) :
			x(x),
			y(y),
			z(z),
			w(w)
		{}

		template <typename T> 
		tref4<T>::tref4
		(
			tref4<T> const & r
		) :
			x(r.x),
			y(r.y),
			z(r.z),
			w(r.w)
		{}

		template <typename T> 
		tref4<T>::tref4
		(
			tvec4<T> const & v
		) :
			x(v.x),
			y(v.y),
			z(v.z),
			w(v.w)
		{}

		template <typename T> 
		tref4<T>& tref4<T>::operator= 
		(
			tref4<T> const & r
		)
		{
			x = r.x;
			y = r.y;
			z = r.z;
			w = r.w;
			return *this;
		}

		template <typename T> 
		tref4<T>& tref4<T>::operator= 
		(
			tvec4<T> const & v
		)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
			return *this;
		}

	}//namespace detail
}//namespace glm
