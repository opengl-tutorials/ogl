///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-25
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/type_vec1.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace detail
	{
		template <typename T>
		inline typename tvec1<T>::size_type tvec1<T>::value_size()
		{
			return 1;
		}

		//////////////////////////////////////
		// Accesses

		template <typename T>
		inline typename tvec1<T>::value_type & tvec1<T>::operator[]
		(
			size_type i
		)
		{
			assert(i < value_size());
			return (&x)[i];
		}

		template <typename T>
		inline typename tvec1<T>::value_type const & tvec1<T>::operator[]
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
		inline tvec1<T>::tvec1() :
			x(value_type(0))
		{}

		template <typename T>
		inline tvec1<T>::tvec1
		(
			ctor
		)
		{}

		template <typename T>
		inline tvec1<T>::tvec1
		(
			tvec1<T> const & v
		) :
			x(v.x)
		{}

		//////////////////////////////////////
		// Explicit basic constructors

		template <typename T>
		inline tvec1<T>::tvec1
		(
			value_type const & s
		) :
			x(s)
		{}

		//////////////////////////////////////
		// Swizzle constructors

		template <typename T>
		inline tvec1<T>::tvec1
		(
			tref1<T> const & r
		) :
			x(r.x)
		{}

		//////////////////////////////////////
		// Convertion scalar constructors
		
		template <typename T>
		template <typename U> 
		inline tvec1<T>::tvec1
		(
			U const & s
		) :
			x(value_type(s))
		{}

		//////////////////////////////////////
		// Convertion vector constructors

		template <typename T>
		template <typename U> 
		inline tvec1<T>::tvec1
		(
			tvec2<U> const & v
		) :
			x(value_type(v.x))
		{}

		template <typename T>
		template <typename U> 
		inline tvec1<T>::tvec1
		(
			tvec3<U> const & v
		) :
			x(value_type(v.x))
		{}

		template <typename T>
		template <typename U> 
		inline tvec1<T>::tvec1
		(
			tvec4<U> const & v
		) :
			x(value_type(v.x))
		{}

		//////////////////////////////////////
		// Unary arithmetic operators

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator=
		(
			tvec1<T> const & v
		)
		{
			this->x = v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator+=
		(
			value_type const & s
		)
		{
			this->x += s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator+=
		(
			tvec1<T> const & v
		)
		{
			this->x += v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator-=
		(
			value_type const & s
		)
		{
			this->x -= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator-=
		(
			tvec1<T> const & v
		)
		{
			this->x -= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator*=
		(
			value_type const & s
		)
		{
			this->x *= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator*=
		(	
			tvec1<T> const & v
		)
		{
			this->x *= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator/=
		(
			value_type const & s
		)
		{
			this->x /= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator/=
		(
			tvec1<T> const & v
		)
		{
			this->x /= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator++()
		{
			++this->x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator--()
		{
			--this->x;
			return *this;
		}

		//////////////////////////////////////
		// Boolean operators

		template <typename T> 
		inline bool operator==
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return (v1.x == v2.x);
		}

		template <typename T> 
		inline bool operator!=
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return (v1.x != v2.x);
		}

		//////////////////////////////////////
		// Unary bit operators

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator%=
		(
			value_type const & s
		)
		{
			this->x %= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator%=
		(
			tvec1<T> const & v
		)
		{
			this->x %= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator&=
		(
			value_type const & s
		)
		{
			this->x &= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator&=
		(
			tvec1<T> const & v
		)
		{
			this->x &= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator|=
		(
			value_type const & s
		)
		{
			this->x |= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator|=
		(
			tvec1<T> const & v
		)
		{
			this->x |= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator^=
		(
			value_type const & s
		)
		{
			this->x ^= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator^=
		(
			tvec1<T> const & v
		)
		{
			this->x ^= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator<<=
		(
			value_type const & s
		)
		{
			this->x <<= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator<<=
		(
			tvec1<T> const & v
		)
		{
			this->x <<= v.x;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator>>=
		(
			value_type const & s
		)
		{
			this->x >>= s;
			return *this;
		}

		template <typename T>
		inline tvec1<T> & tvec1<T>::operator>>=
		(
			tvec1<T> const & v
		)
		{
			this->x >>= v.x;
			return *this;
		}

		//////////////////////////////////////
		// Swizzle operators

		template <typename T>
		inline T 
		tvec1<T>::swizzle(comp x) const
		{
			return (*this)[x];
		}

		template <typename T>
		inline tvec2<T> 
		tvec1<T>::swizzle
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
		inline tvec3<T> 
		tvec1<T>::swizzle
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
		inline tvec4<T> 
		tvec1<T>::swizzle
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
		inline tref1<T> 
		tvec1<T>::swizzle
		(
			comp x
		)
		{
			return tref1<T>(
				(*this)[x]);
		}

		//////////////////////////////////////
		// Binary arithmetic operators

		template <typename T> 
		inline tvec1<T> operator+ 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x + s);
		}

		template <typename T> 
		inline tvec1<T> operator+ 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s + v.x);
		}

		template <typename T> 
		inline tvec1<T> operator+ 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x + v2.x);
		}

		//operator-
		template <typename T> 
		inline tvec1<T> operator- 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x - s);
		}

		template <typename T> 
		inline tvec1<T> operator- 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s - v.x);
		}

		template <typename T> 
		inline tvec1<T> operator- 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x - v2.x);
		}

		//operator*
		template <typename T> 
		inline tvec1<T> operator* 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x * s);
		}

		template <typename T> 
		inline tvec1<T> operator* 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s * v.x);
		}

		template <typename T> 
		inline tvec1<T> operator*
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x * v2.x);
		}

		//operator/
		template <typename T> 
		inline tvec1<T> operator/ 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x / s);
		}

		template <typename T> 
		inline tvec1<T> operator/ 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s / v.x);
		}

		template <typename T> 
		inline tvec1<T> operator/ 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x / v2.x);
		}

		// Unary constant operators
		template <typename T> 
		inline tvec1<T> operator- 
		(
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				-v.x);
		}

		template <typename T> 
		inline tvec1<T> operator++ 
		(
			tvec1<T> const & v, 
			int
		)
		{
			return tvec1<T>(
				v.x + T(1));
		}

		template <typename T> 
		inline tvec1<T> operator-- 
		(
			tvec1<T> const & v, 
			int
		)
		{
			return tvec1<T>(
				v.x - T(1));
		}

		//////////////////////////////////////
		// Binary bit operators

		template <typename T>
		inline tvec1<T> operator% 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x % s);
		}

		template <typename T>
		inline tvec1<T> operator% 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s % v.x);
		}

		template <typename T>
		inline tvec1<T> operator% 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x % v2.x);
		}

		template <typename T>
		inline tvec1<T> operator& 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x & s);
		}

		template <typename T>
		inline tvec1<T> operator& 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s & v.x);
		}

		template <typename T>
		inline tvec1<T> operator& 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x & v2.x);
		}

		template <typename T>
		inline tvec1<T> operator| 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x | s);
		}

		template <typename T>
		inline tvec1<T> operator| 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s | v.x);
		}

		template <typename T>
		inline tvec1<T> operator| 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x | v2.x);
		}
		
		template <typename T>
		inline tvec1<T> operator^ 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x ^ s);
		}

		template <typename T>
		inline tvec1<T> operator^ 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s ^ v.x);
		}

		template <typename T>
		inline tvec1<T> operator^ 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x ^ v2.x);
		}

		template <typename T>
		inline tvec1<T> operator<< 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x << s);
		}

		template <typename T>
		inline tvec1<T> operator<< 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s << v.x);
		}

		template <typename T>
		inline tvec1<T> operator<< 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x << v2.x);
		}

		template <typename T>
		inline tvec1<T> operator>> 
		(
			tvec1<T> const & v, 
			typename tvec1<T>::value_type const & s
		)
		{
			return tvec1<T>(
				v.x >> s);
		}

		template <typename T>
		inline tvec1<T> operator>> 
		(
			typename tvec1<T>::value_type const & s, 
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				s >> v.x);
		}

		template <typename T>
		inline tvec1<T> operator>> 
		(
			tvec1<T> const & v1, 
			tvec1<T> const & v2
		)
		{
			return tvec1<T>(
				v1.x >> v2.x);
		}

		template <typename T> 
		inline tvec1<T> operator~ 
		(
			tvec1<T> const & v
		)
		{
			return tvec1<T>(
				~v.x);
		}

		//////////////////////////////////////
		// tref definition

		template <typename T> 
		inline tref1<T>::tref1
		(
			T & x
		) :
			x(x)
		{}

		template <typename T> 
		inline tref1<T>::tref1
		(
			tref1<T> const & r
		) :
			x(r.x)
		{}

		template <typename T> 
		inline tref1<T>::tref1
		(
			tvec1<T> const & v
		) :
			x(v.x)
		{}

		template <typename T> 
		inline tref1<T> & tref1<T>::operator= 
		(
			tref1<T> const & r
		)
		{
			x = r.x;
			return *this;
		}

		template <typename T> 
		inline tref1<T> & tref1<T>::operator= 
		(
			tvec1<T> const & v
		)
		{
			x = v.x;
			return *this;
		}

	}//namespace detail
}//namespace glm
