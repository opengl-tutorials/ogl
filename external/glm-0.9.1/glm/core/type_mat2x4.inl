///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-08-05
// Updated : 2010-02-03
// Licence : This source is under MIT License
// File    : glm/core/type_mat2x4.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat2x4<T>::size_type tmat2x4<T>::col_size()
	{
		return 4;
	}

	template <typename T>
	inline typename tmat2x4<T>::size_type tmat2x4<T>::row_size()
	{
		return 2;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat2x4<T>::col_type &
	tmat2x4<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->row_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat2x4<T>::col_type const &
	tmat2x4<T>::operator[]
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
    inline tmat2x4<T>::tmat2x4()
    {
		value_type const Zero(0);
		value_type const One(1);
        this->value[0] = col_type(One, Zero, Zero, Zero);
        this->value[1] = col_type(Zero, One, Zero, Zero);
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = m.value[0];
        this->value[1] = m.value[1];
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		ctor
	)
    {}

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		value_type const & s
	)
    {
		value_type const Zero(0);
        this->value[0] = col_type(s, Zero, Zero, Zero);
        this->value[1] = col_type(Zero, Zero, Zero, Zero);
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
    (
        value_type const & x0, value_type const & y0, value_type const & z0, value_type const & w0,
        value_type const & x1, value_type const & y1, value_type const & z1, value_type const & w1
    )
    {
        this->value[0] = col_type(x0, y0, z0, w0);
        this->value[1] = col_type(x1, y1, z1, w1);
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
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
    inline tmat2x4<T>::tmat2x4
	(
		tmat2x4<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
	}

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], detail::tvec2<T>(0));
        this->value[1] = col_type(m[1], detail::tvec2<T>(0));
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat3x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat4x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], detail::tvec2<T>(0));
        this->value[1] = col_type(m[1], detail::tvec2<T>(0));
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], detail::tvec2<T>(T(0)));
        this->value[1] = col_type(m[1], detail::tvec2<T>(T(0)));
    }

    template <typename T> 
    inline tmat2x4<T>::tmat2x4
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
    }

    //////////////////////////////////////////////////////////////
    // Unary updatable operators

    template <typename T> 
    inline tmat2x4<T>& tmat2x4<T>::operator= 
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x4<T>& tmat2x4<T>::operator= 
	(
		tmat2x4<U> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x4<T>& tmat2x4<T>::operator+= 
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
    inline tmat2x4<T>& tmat2x4<T>::operator+= 
	(
		tmat2x4<U> const & m
	)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x4<T>& tmat2x4<T>::operator-= 
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
    inline tmat2x4<T>& tmat2x4<T>::operator-= 
	(
		tmat2x4<U> const & m
	)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x4<T>& tmat2x4<T>::operator*= 
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
    inline tmat2x4<T>& tmat2x4<T>::operator*=
	(
		tmat2x4<U> const & m
	)
    {
        return (*this = tmat2x4<T>(*this * m));
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x4<T> & tmat2x4<T>::operator/= 
	(
		U const & s
	)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        return *this;
    }

    template <typename T> 
    inline tmat2x4<T>& tmat2x4<T>::operator++ ()
    {
        ++this->value[0];
        ++this->value[1];
        return *this;
    }

    template <typename T> 
    inline tmat2x4<T>& tmat2x4<T>::operator-- ()
    {
        --this->value[0];
        --this->value[1];
        return *this;
    }

    //////////////////////////////////////////////////////////////
    // Binary operators

    template <typename T> 
    inline tmat2x4<T> operator+
	(
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s
	)
    {
        return tmat2x4<T>(
            m[0] + s,
            m[1] + s);
    }

    template <typename T> 
    inline tmat2x4<T> operator+ 
	(
		tmat2x4<T> const & m1, 
		tmat2x4<T> const & m2
	)
    {
        return tmat2x4<T>(
            m1[0] + m2[0],
            m1[1] + m2[1]);
    }

    template <typename T> 
    inline tmat2x4<T> operator- 
	(
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s
	)
    {
        return tmat2x4<T>(
            m[0] - s,
            m[1] - s);
    }

    template <typename T> 
    inline tmat2x4<T> operator- 
	(
		tmat2x4<T> const & m1, 
		tmat2x4<T> const & m2
	)
    {
        return tmat2x4<T>(
            m1[0] - m2[0],
            m1[1] - m2[1]);
    }

    template <typename T> 
    inline tmat2x4<T> operator* 
	(
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s
	)
    {
        return tmat2x4<T>(
            m[0] * s,
            m[1] * s);
    }

    template <typename T> 
    inline tmat2x4<T> operator*
	(
		typename tmat2x4<T>::value_type const & s, 
		tmat2x4<T> const & m
	)
    {
        return tmat2x4<T>(
            m[0] * s,
            m[1] * s);
    }
   
	//     X
	//     X
	// X X
	// X X
	// X X
	// X X
    template <typename T>
    inline typename tmat2x4<T>::col_type operator* 
	(
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::row_type const & v
	)
    {
        return typename tmat2x4<T>::col_type(
            m[0][0] * v.x + m[1][0] * v.y,
            m[0][1] * v.x + m[1][1] * v.y,
            m[0][2] * v.x + m[1][2] * v.y,
            m[0][3] * v.x + m[1][3] * v.y);
    }

	//			X X
	//			X X
	//			X X
	//			X X
	// X X X X
	template <typename T> 
    inline typename tmat2x4<T>::row_type operator* 
	(
		typename tmat2x4<T>::col_type const & v, 
		tmat2x4<T> const & m
	) 
    {
        return typename tmat2x4<T>::row_type(
            v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
            v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3]);
    }

    template <typename T> 
    inline tmat4x4<T> operator* 
	(
		tmat2x4<T> const & m1, 
		tmat4x2<T> const & m2
	)
    {
		typename tmat2x4<T>::value_type SrcA00 = m1[0][0];
		typename tmat2x4<T>::value_type SrcA01 = m1[0][1];
		typename tmat2x4<T>::value_type SrcA02 = m1[0][2];
		typename tmat2x4<T>::value_type SrcA03 = m1[0][3];
		typename tmat2x4<T>::value_type SrcA10 = m1[1][0];
		typename tmat2x4<T>::value_type SrcA11 = m1[1][1];
		typename tmat2x4<T>::value_type SrcA12 = m1[1][2];
		typename tmat2x4<T>::value_type SrcA13 = m1[1][3];

		typename tmat2x4<T>::value_type SrcB00 = m2[0][0];
		typename tmat2x4<T>::value_type SrcB01 = m2[0][1];
		typename tmat2x4<T>::value_type SrcB10 = m2[1][0];
		typename tmat2x4<T>::value_type SrcB11 = m2[1][1];
		typename tmat2x4<T>::value_type SrcB20 = m2[2][0];
		typename tmat2x4<T>::value_type SrcB21 = m2[2][1];
		typename tmat2x4<T>::value_type SrcB30 = m2[3][0];
		typename tmat2x4<T>::value_type SrcB31 = m2[3][1];

		tmat4x4<T> Result(tmat4x4<T>::null);
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01;
		Result[0][3] = SrcA03 * SrcB00 + SrcA13 * SrcB01;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11;
		Result[1][3] = SrcA03 * SrcB10 + SrcA13 * SrcB11;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21;
		Result[2][3] = SrcA03 * SrcB20 + SrcA13 * SrcB21;
		Result[3][0] = SrcA00 * SrcB30 + SrcA10 * SrcB31;
		Result[3][1] = SrcA01 * SrcB30 + SrcA11 * SrcB31;
		Result[3][2] = SrcA02 * SrcB30 + SrcA12 * SrcB31;
		Result[3][3] = SrcA03 * SrcB30 + SrcA13 * SrcB31;
		return Result;
    }

    template <typename T> 
    inline tmat2x4<T> operator/ 
	(
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s
	)
    {
        return tmat2x4<T>(
            m[0] / s,
            m[1] / s);        
    }

    template <typename T> 
    inline tmat2x4<T> operator/ 
	(
		typename tmat2x4<T>::value_type const & s, 
		tmat2x4<T> const & m
	)
    {
        return tmat2x4<T>(
            s / m[0],
            s / m[1]);        
    }

	// Unary constant operators
    template <typename T> 
    inline tmat2x4<T> const operator- 
	(
		tmat2x4<T> const & m
	)
    {
        return tmat2x4<T>(
            -m[0], 
            -m[1]);
    }

    template <typename T> 
    inline tmat2x4<T> const operator++ 
	(
		tmat2x4<T> const & m, 
		int
	) 
    {
        return tmat2x4<T>(
            m[0] + typename tmat2x4<T>::value_type(1),
            m[1] + typename tmat2x4<T>::value_type(1));
    }

    template <typename T> 
    inline tmat2x4<T> const operator-- 
	(
		tmat2x4<T> const & m, 
		int
	) 
    {
        return tmat2x4<T>(
            m[0] - typename tmat2x4<T>::value_type(1),
            m[1] - typename tmat2x4<T>::value_type(1));
    }

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	inline bool operator==
	(
		tmat2x4<T> const & m1, 
		tmat2x4<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template <typename T> 
	inline bool operator!=
	(
		tmat2x4<T> const & m1, 
		tmat2x4<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}

} //namespace detail
} //namespace glm
