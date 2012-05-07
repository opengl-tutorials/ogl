///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-08-05
// Updated : 2010-02-05
// Licence : This source is under MIT License
// File    : glm/core/type_mat3x4.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat3x4<T>::size_type tmat3x4<T>::col_size()
	{
		return 4;
	}

	template <typename T>
	inline typename tmat3x4<T>::size_type tmat3x4<T>::row_size()
	{
		return 3;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat3x4<T>::col_type & 
	tmat3x4<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->row_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat3x4<T>::col_type const & 
	tmat3x4<T>::operator[]
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
    inline tmat3x4<T>::tmat3x4()
    {
		value_type const Zero(0);
		value_type const One(1);
        this->value[0] = col_type(1, 0, 0, 0);
        this->value[1] = col_type(0, 1, 0, 0);
        this->value[2] = col_type(0, 0, 1, 0);
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = m.value[0];
        this->value[1] = m.value[1];
        this->value[2] = m.value[2];
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		ctor
	)
    {}

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		value_type const & s
	)
    {
		value_type const Zero(0);
        this->value[0] = col_type(s, Zero, Zero, Zero);
        this->value[1] = col_type(Zero, s, Zero, Zero);
        this->value[2] = col_type(Zero, Zero, s, Zero);
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
    (
		value_type const & x0, value_type const & y0, value_type const & z0, value_type const & w0,
        value_type const & x1, value_type const & y1, value_type const & z1, value_type const & w1,
        value_type const & x2, value_type const & y2, value_type const & z2, value_type const & w2
    )
    {
        this->value[0] = col_type(x0, y0, z0, w0);
        this->value[1] = col_type(x1, y1, z1, w1);
        this->value[2] = col_type(x2, y2, z2, w2);
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
    (
        col_type const & v0, 
        col_type const & v1, 
        col_type const & v2
    )
    {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
    }

    // Conversion
    template <typename T> 
    template <typename U> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat3x4<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
	}

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], detail::tvec2<T>(0));
        this->value[1] = col_type(m[1], detail::tvec2<T>(0));
        this->value[2] = col_type(T(0), T(0), T(1), T(0));
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat3x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
        this->value[2] = col_type(m[2], T(0));
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat4x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
        this->value[2] = col_type(T(0), T(0), T(1), T(0));
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], detail::tvec2<T>(0));
        this->value[1] = col_type(m[1], detail::tvec2<T>(0));
        this->value[2] = col_type(m[2], T(0), T(1));
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(T(0), T(0), T(1), T(0));
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], detail::tvec2<T>(T(0)));
        this->value[1] = col_type(m[1], detail::tvec2<T>(T(0)));
        this->value[2] = col_type(m[2], detail::tvec2<T>(T(1), T(0)));
    }

    template <typename T> 
    inline tmat3x4<T>::tmat3x4
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0], T(0));
        this->value[1] = col_type(m[1], T(0));
        this->value[2] = col_type(m[2], T(0));
    }

    //////////////////////////////////////////////////////////////
    // Unary updatable operators

    template <typename T> 
    inline tmat3x4<T>& tmat3x4<T>::operator= 
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T>& tmat3x4<T>::operator= 
	(
		tmat3x4<U> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T>& tmat3x4<T>::operator+= 
	(
		U const & s
	)
    {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T>& tmat3x4<T>::operator+= 
	(
		tmat3x4<U> const & m
	)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T>& tmat3x4<T>::operator-= 
	(
		U const & s
	)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T>& tmat3x4<T>::operator-= 
	(
		tmat3x4<U> const & m
	)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[2] -= m[2];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T>& tmat3x4<T>::operator*= 
	(
		U const & s
	)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T>& tmat3x4<T>::operator*= 
	(
		tmat3x4<U> const & m
	)
    {
        return (*this = tmat3x4<T>(*this * m));
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x4<T> & tmat3x4<T>::operator/= 
	(
		U const & s
	)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        return *this;
    }

    template <typename T> 
    inline tmat3x4<T>& tmat3x4<T>::operator++ ()
    {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        return *this;
    }

    template <typename T> 
    inline tmat3x4<T>& tmat3x4<T>::operator-- ()
    {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        return *this;
    }

    //////////////////////////////////////////////////////////////
    // Binary operators

    template <typename T> 
    inline tmat3x4<T> operator+ 
	(
		tmat3x4<T> const & m, 
		typename tmat3x4<T>::value_type const & s
	)
    {
        return tmat3x4<T>(
            m[0] + s,
            m[1] + s,
            m[2] + s);
    }

    template <typename T> 
    inline tmat3x4<T> operator+ 
	(
		tmat3x4<T> const & m1, 
		tmat3x4<T> const & m2
	)
    {
        return tmat3x4<T>(
            m1[0] + m2[0],
            m1[1] + m2[1],
            m1[2] + m2[2]);
    }

    template <typename T> 
	inline tmat3x4<T> operator- 
	(
		tmat3x4<T> const & m, 
		typename tmat3x4<T>::value_type const & s
	)
    {
        return tmat3x4<T>(
            m[0] - s,
            m[1] - s,
            m[2] - s);
    }

    template <typename T> 
    inline tmat3x4<T> operator- 
	(
		tmat3x4<T> const & m1, 
		tmat3x4<T> const & m2
	)
    {
        return tmat3x4<T>(
            m1[0] - m2[0],
            m1[1] - m2[1],
            m1[2] - m2[2]);
    }

    template <typename T> 
    inline tmat3x4<T> operator* 
	(
		tmat3x4<T> const & m, 
		typename tmat3x4<T>::value_type const & s
	)
    {
        return tmat3x4<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s);
    }

    template <typename T> 
    inline tmat3x4<T> operator* 
	(
		typename tmat3x4<T>::value_type const & s, 
		tmat3x4<T> const & m
	)
    {
        return tmat3x4<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s);
    }
   
    template <typename T>
    inline typename tmat3x4<T>::col_type operator* 
	(
		tmat3x4<T> const & m, 
		typename tmat3x4<T>::row_type const & v
	)
    {
        return typename tmat3x4<T>::col_type(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z,
            m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z);
    }

	//			X X X
	//			X X X
	//			X X X
	//			X X X
	// X X X X
    template <typename T> 
    inline typename tmat3x4<T>::row_type operator* 
	(
		typename tmat3x4<T>::col_type const & v, 
		tmat3x4<T> const & m
	)
    {
		return typename tmat3x4<T>::row_type(
            v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
            v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3],
            v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3]);
    }

    template <typename T> 
    inline tmat4x4<T> operator* 
	(
		tmat3x4<T> const & m1, 
		tmat4x3<T> const & m2
	)
    {
        const T SrcA00 = m1[0][0];
        const T SrcA01 = m1[0][1];
        const T SrcA02 = m1[0][2];
        const T SrcA03 = m1[0][3];
        const T SrcA10 = m1[1][0];
        const T SrcA11 = m1[1][1];
        const T SrcA12 = m1[1][2];
        const T SrcA13 = m1[1][3];
        const T SrcA20 = m1[2][0];
        const T SrcA21 = m1[2][1];
        const T SrcA22 = m1[2][2];
        const T SrcA23 = m1[2][3];

        const T SrcB00 = m2[0][0];
        const T SrcB01 = m2[0][1];
        const T SrcB02 = m2[0][2];
        const T SrcB10 = m2[1][0];
        const T SrcB11 = m2[1][1];
        const T SrcB12 = m2[1][2];
        const T SrcB20 = m2[2][0];
        const T SrcB21 = m2[2][1];
        const T SrcB22 = m2[2][2];
        const T SrcB30 = m2[3][0];
        const T SrcB31 = m2[3][1];
        const T SrcB32 = m2[3][2];

        tmat4x4<T> Result(tmat4x4<T>::null);
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
        Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
        Result[0][3] = SrcA03 * SrcB00 + SrcA13 * SrcB01 + SrcA23 * SrcB02;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
        Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
        Result[1][3] = SrcA03 * SrcB10 + SrcA13 * SrcB11 + SrcA23 * SrcB12;
        Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
        Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
        Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
        Result[2][3] = SrcA03 * SrcB20 + SrcA13 * SrcB21 + SrcA23 * SrcB22;
        Result[3][0] = SrcA00 * SrcB30 + SrcA10 * SrcB31 + SrcA20 * SrcB32;
        Result[3][1] = SrcA01 * SrcB30 + SrcA11 * SrcB31 + SrcA21 * SrcB32;
        Result[3][2] = SrcA02 * SrcB30 + SrcA12 * SrcB31 + SrcA22 * SrcB32;
        Result[3][3] = SrcA03 * SrcB30 + SrcA13 * SrcB31 + SrcA23 * SrcB32;
        return Result;
    }

    template <typename T> 
    inline tmat3x4<T> operator/ 
	(
		tmat3x4<T> const & m, 
		typename tmat3x4<T>::value_type const & s
	)
    {
        return tmat3x4<T>(
            m[0] / s,
            m[1] / s,
            m[2] / s);        
    }

    template <typename T> 
    inline tmat3x4<T> operator/
	(
		typename tmat3x4<T>::value_type const & s, 
		tmat3x4<T> const & m
	)
    {
        return tmat3x4<T>(
            s / m[0],
            s / m[1],
            s / m[2]);        
    }

	// Unary constant operators
    template <typename T> 
    inline tmat3x4<T> const operator- 
	(
		tmat3x4<T> const & m
	)
    {
        return tmat3x4<T>(
            -m[0], 
            -m[1],
            -m[2]);
    }

    template <typename T> 
    inline tmat3x4<T> const operator++ 
	(
		tmat3x4<T> const & m, 
		int
	) 
    {
        return tmat3x4<T>(
            m[0] + T(1),
            m[1] + T(1),
            m[2] + T(1));
    }

    template <typename T> 
    inline tmat3x4<T> const operator-- 
	(
		tmat3x4<T> const & m, 
		int
	) 
    {
        return tmat3x4<T>(
            m[0] - T(1),
            m[1] - T(1),
            m[2] - T(1));
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	inline bool operator==
	(
		tmat3x4<T> const & m1, 
		tmat3x4<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	template <typename T> 
	inline bool operator!=
	(
		tmat3x4<T> const & m1, 
		tmat3x4<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}

} //namespace detail
} //namespace glm
