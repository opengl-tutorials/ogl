///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-08-05
// Updated : 2010-02-03
// Licence : This source is under MIT License
// File    : glm/core/type_mat2x3.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat2x3<T>::size_type tmat2x3<T>::col_size()
	{
		return 3;
	}

	template <typename T>
	inline typename tmat2x3<T>::size_type tmat2x3<T>::row_size()
	{
		return 2;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat2x3<T>::col_type &
	tmat2x3<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->row_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat2x3<T>::col_type const &
	tmat2x3<T>::operator[]
	(
		size_type i
	) const
	{
		assert(i < this->row_size());
		return this->value[i];
	}

    //////////////////////////////////////////////////////////////
    // Constructors

    template <typename T> 
    inline tmat2x3<T>::tmat2x3()
    {
        this->value[0] = col_type(T(1), T(0), T(0));
        this->value[1] = col_type(T(0), T(1), T(0));
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = m.value[0];
        this->value[1] = m.value[1];
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		ctor
	)
    {}

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		value_type const & s
	)
    {
        this->value[0] = col_type(s, T(0), T(0));
        this->value[1] = col_type(T(0), s, T(0));
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
    (
        value_type const & x0, value_type const & y0, value_type const & z0,
        value_type const & x1, value_type const & y1, value_type const & z1
    )
    {
        this->value[0] = col_type(x0, y0, z0);
        this->value[1] = col_type(x1, y1, z1);
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
    (
        col_type const & v0, 
        col_type const & v1
    )
    {
        this->value[0] = v0;
        this->value[1] = v1;
    }

    // Conversion
    template <typename T> 
    template <typename U> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat2x3<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
	}

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat3x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat4x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
    }

    template <typename T> 
    inline tmat2x3<T>::tmat2x3
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
    }

    //////////////////////////////////////////////////////////////
    // Unary updatable operators

    template <typename T> 
    inline tmat2x3<T>& tmat2x3<T>::operator= 
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x3<T>& tmat2x3<T>::operator= 
	(
		tmat2x3<U> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x3<T> & tmat2x3<T>::operator+= 
	(
		U const & s
	)
    {
        this->value[0] += s;
        this->value[1] += s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x3<T>& tmat2x3<T>::operator+=
	(
		tmat2x3<U> const & m
	)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x3<T>& tmat2x3<T>::operator-= 
	(
		U const & s
	)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x3<T>& tmat2x3<T>::operator-= 
	(
		tmat2x3<U> const & m
	)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x3<T>& tmat2x3<T>::operator*= 
	(
		U const & s
	)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x3<T> & tmat2x3<T>::operator*= 
	(
		tmat2x3<U> const & m
	)
    {
        return (*this = tmat2x3<U>(*this * m));
    }

    template <typename T>
	template <typename U> 
    inline tmat2x3<T> & tmat2x3<T>::operator/= 
	(
		U const & s
	)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        return *this;
    }

    template <typename T> 
    inline tmat2x3<T> & tmat2x3<T>::operator++ ()
    {
        ++this->value[0];
        ++this->value[1];
        return *this;
    }

    template <typename T> 
    inline tmat2x3<T> & tmat2x3<T>::operator-- ()
    {
        --this->value[0];
        --this->value[1];
        return *this;
    }
    
    //////////////////////////////////////////////////////////////
    // Binary operators

    template <typename T> 
    inline tmat2x3<T> operator+ 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
    {
        return tmat2x3<T>(
            m[0] + s,
            m[1] + s);
    }

    template <typename T> 
    inline tmat2x3<T> operator+ 
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
    {
        return tmat2x3<T>(
            m1[0] + m2[0],
            m1[1] + m2[1]);
    }

    template <typename T> 
    inline tmat2x3<T> operator- 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
    {
        return tmat2x3<T>(
            m[0] - s,
            m[1] - s);
    }

    template <typename T> 
    inline tmat2x3<T> operator- 
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
    {
        return tmat2x3<T>(
            m1[0] - m2[0],
            m1[1] - m2[1]);
    }

    template <typename T> 
    inline tmat2x3<T> operator* 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
    {
        return tmat2x3<T>(
            m[0] * s,
            m[1] * s);
    }

    template <typename T> 
    inline tmat2x3<T> operator* 
	(
		typename tmat2x3<T>::value_type const & s, 
		tmat2x3<T> const & m
	)
    {
        return tmat2x3<T>(
            m[0] * s,
            m[1] * s);
    }

    template <typename T>
    inline typename tmat2x3<T>::col_type operator* 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::row_type const & v)
    {
        return typename tmat2x3<T>::col_type(
            m[0][0] * v.x + m[1][0] * v.y,
            m[0][1] * v.x + m[1][1] * v.y,
            m[0][2] * v.x + m[1][2] * v.y);
    }

    template <typename T> 
    inline typename tmat2x3<T>::row_type operator* 
	(
		typename tmat2x3<T>::col_type const & v, 
		tmat2x3<T> const & m) 
    {
        return typename tmat2x3<T>::row_type(
            v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2],
            v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2]);
    }

    template <typename T> 
    inline tmat3x3<T> operator* 
	(
		tmat2x3<T> const & m1, 
		tmat3x2<T> const & m2
	)
    {
		typename tmat2x3<T>::value_type SrcA00 = m1[0][0];
		typename tmat2x3<T>::value_type SrcA01 = m1[0][1];
		typename tmat2x3<T>::value_type SrcA02 = m1[0][2];
		typename tmat2x3<T>::value_type SrcA10 = m1[1][0];
		typename tmat2x3<T>::value_type SrcA11 = m1[1][1];
		typename tmat2x3<T>::value_type SrcA12 = m1[1][2];

		typename tmat2x3<T>::value_type SrcB00 = m2[0][0];
		typename tmat2x3<T>::value_type SrcB01 = m2[0][1];
		typename tmat2x3<T>::value_type SrcB10 = m2[1][0];
		typename tmat2x3<T>::value_type SrcB11 = m2[1][1];
		typename tmat2x3<T>::value_type SrcB20 = m2[2][0];
		typename tmat2x3<T>::value_type SrcB21 = m2[2][1];

		tmat3x3<T> Result(tmat3x3<T>::null);
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21;
		return Result;
    }

    template <typename T> 
    inline tmat2x3<T> operator/ 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
    {
        return tmat2x3<T>(
            m[0] / s,
            m[1] / s);        
    }

    template <typename T> 
    inline tmat2x3<T> operator/ 
	(
		typename tmat2x3<T>::value_type const & s, 
		tmat2x3<T> const & m
	)
    {
        return tmat2x3<T>(
            s / m[0],
            s / m[1]);        
    }

	// Unary constant operators
    template <typename T> 
    inline tmat2x3<T> const operator- 
	(
		tmat2x3<T> const & m
	)
    {
        return tmat2x3<T>(
            -m[0], 
            -m[1]);
    }

    template <typename T> 
    inline tmat2x3<T> const operator++ 
	(
		tmat2x3<T> const & m, 
		int
	) 
    {
        return tmat2x3<T>(
            m[0] + typename tmat2x3<T>::value_type(1),
            m[1] + typename tmat2x3<T>::value_type(1));
    }

    template <typename T> 
    inline tmat2x3<T> const operator-- 
	(
		tmat2x3<T> const & m, 
		int
	) 
    {
        return tmat2x3<T>(
            m[0] - typename tmat2x3<T>::value_type(1),
            m[1] - typename tmat2x3<T>::value_type(1));
    }

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	inline bool operator==
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template <typename T> 
	inline bool operator!=
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}

} //namespace detail
} //namespace glm
