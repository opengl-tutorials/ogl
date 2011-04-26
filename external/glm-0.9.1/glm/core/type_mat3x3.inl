///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-01-27
// Updated : 2010-02-03
// Licence : This source is under MIT License
// File    : glm/core/type_mat3x3.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat3x3<T>::size_type tmat3x3<T>::col_size()
	{
		return 3;
	}

	template <typename T>
	inline typename tmat3x3<T>::size_type tmat3x3<T>::row_size()
	{
		return 3;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat3x3<T>::col_type &
	tmat3x3<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->row_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat3x3<T>::col_type const &
	tmat3x3<T>::operator[]
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
    inline tmat3x3<T>::tmat3x3()
    {
		value_type const Zero(0);
		value_type const One(1);
        this->value[0] = col_type(One, Zero, Zero);
        this->value[1] = col_type(Zero, One, Zero);
        this->value[2] = col_type(Zero, Zero, One);
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat3x3<T> const & m
	)
    {
        this->value[0] = m.value[0];
        this->value[1] = m.value[1];
        this->value[2] = m.value[2];
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		ctor
	)
    {}

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		value_type const & s
	)
    {
		value_type const Zero(0);
        this->value[0] = col_type(s, Zero, Zero);
        this->value[1] = col_type(Zero, s, Zero);
        this->value[2] = col_type(Zero, Zero, s);
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
    (
        value_type const & x0, value_type const & y0, value_type const & z0, 
        value_type const & x1, value_type const & y1, value_type const & z1,
        value_type const & x2, value_type const & y2, value_type const & z2
    )
    {
        this->value[0] = col_type(x0, y0, z0);
        this->value[1] = col_type(x1, y1, z1);
        this->value[2] = col_type(x2, y2, z2);
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
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

    //////////////////////////////////////////////////////////////
    // Conversions

    template <typename T> 
    template <typename U> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat3x3<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
	}

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], value_type(0));
        this->value[1] = col_type(m[1], value_type(0));
        this->value[2] = col_type(detail::tvec2<T>(0), value_type(1));
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat4x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
    }

	template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = col_type(detail::tvec2<T>(0), value_type(1));
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], value_type(0));
        this->value[1] = col_type(m[1], value_type(0));
        this->value[2] = col_type(m[2], value_type(1));
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(detail::tvec2<T>(0), value_type(1));
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], value_type(0));
        this->value[1] = col_type(m[1], value_type(0));
        this->value[2] = col_type(m[2], value_type(1));
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
    }

    template <typename T> 
    inline tmat3x3<T>::tmat3x3
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    //////////////////////////////////////////////////////////////
    // Operators

    template <typename T> 
    inline tmat3x3<T> & tmat3x3<T>::operator=
	(
		tmat3x3<T> const & m
	)
    {
	    this->value[0] = m[0];
	    this->value[1] = m[1];
        this->value[2] = m[2];
	    return *this;
    }

    template <typename T> 
    template <typename U> 
	inline tmat3x3<T> & tmat3x3<T>::operator=
	(
		tmat3x3<U> const & m
	)
    {
	    this->value[0] = m[0];
	    this->value[1] = m[1];
        this->value[2] = m[2];
	    return *this;
    }

    template <typename T> 
	template <typename U> 
	inline tmat3x3<T> & tmat3x3<T>::operator+= 
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
    inline tmat3x3<T> & tmat3x3<T>::operator+=
	(
		tmat3x3<U> const & m
	)
    {
	    this->value[0] += m[0];
	    this->value[1] += m[1];
        this->value[2] += m[2];
	    return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x3<T> & tmat3x3<T>::operator-= 
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
    inline tmat3x3<T> & tmat3x3<T>::operator-= 
	(
		tmat3x3<U> const & m
	)
    {
	    this->value[0] -= m[0];
	    this->value[1] -= m[1];
        this->value[2] -= m[2];
	    return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x3<T> & tmat3x3<T>::operator*= 
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
    inline tmat3x3<T> & tmat3x3<T>::operator*= 
	(
		tmat3x3<U> const & m
	)
    {
        return (*this = *this * m);
    }

    template <typename T> 
	template <typename U> 
    inline tmat3x3<T> & tmat3x3<T>::operator/= 
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
	template <typename U> 
    inline tmat3x3<T> & tmat3x3<T>::operator/= 
	(
		tmat3x3<U> const & m
	)
    {
        return (*this = *this / m);
    }

    template <typename T> 
    inline tmat3x3<T> & tmat3x3<T>::operator++ ()
    {
	    ++this->value[0];
	    ++this->value[1];
        ++this->value[2];
	    return *this;
    }

    template <typename T> 
    inline tmat3x3<T> & tmat3x3<T>::operator-- ()
    {
	    --this->value[0];
	    --this->value[1];
        --this->value[2];
	    return *this;
    }

    template <typename T> 
    inline tmat3x3<T> tmat3x3<T>::_inverse() const
    {
        T S00 = value[0][0];
        T S01 = value[0][1];
        T S02 = value[0][2];

        T S10 = value[1][0];
        T S11 = value[1][1];
        T S12 = value[1][2];

        T S20 = value[2][0];
        T S21 = value[2][1];
        T S22 = value[2][2];
/*
        tmat3x3<T> Inverse(
            + (S11 * S22 - S21 * S12),
            - (S10 * S22 - S20 * S12),
            + (S10 * S21 - S20 * S11),
            - (S01 * S22 - S21 * S02),
            + (S00 * S22 - S20 * S02),
            - (S00 * S21 - S20 * S01),
            + (S01 * S12 - S11 * S02),
            - (S00 * S12 - S10 * S02),
            + (S00 * S11 - S10 * S01));
*/
        tmat3x3<T> Inverse(
            S11 * S22 - S21 * S12,
            S12 * S20 - S22 * S10,
            S10 * S21 - S20 * S11,
            S02 * S21 - S01 * S22,
            S00 * S22 - S02 * S20,
            S01 * S20 - S00 * S21,
            S12 * S01 - S11 * S02,
            S10 * S02 - S12 * S00,
            S11 * S00 - S10 * S01);

        T Determinant = S00 * (S11 * S22 - S21 * S12)
                      - S10 * (S01 * S22 - S21 * S02)
                      + S20 * (S01 * S12 - S11 * S02);

        Inverse /= Determinant;
        return Inverse;
    }

    //////////////////////////////////////////////////////////////
	// Binary operators

    template <typename T> 
    inline tmat3x3<T> operator+ 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
    {
        return tmat3x3<T>(
            m[0] + s,
            m[1] + s,
            m[2] + s);
    }

    template <typename T> 
    inline tmat3x3<T> operator+ 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
    {
        return tmat3x3<T>(
            m[0] + s,
            m[1] + s,
            m[2] + s);
    }

    template <typename T> 
    inline tmat3x3<T> operator+ 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
    {
        return tmat3x3<T>(
            m1[0] + m2[0],
            m1[1] + m2[1],
            m1[2] + m2[2]);
    }

    template <typename T> 
    inline tmat3x3<T> operator- 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
    {
        return tmat3x3<T>(
            m[0] - s,
            m[1] - s,
            m[2] - s);
    }

    template <typename T> 
    inline tmat3x3<T> operator- 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
    {
        return tmat3x3<T>(
            s - m[0],
            s - m[1],
            s - m[2]);
    }

    template <typename T> 
    inline tmat3x3<T> operator- 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
    {
        return tmat3x3<T>(
            m1[0] - m2[0],
            m1[1] - m2[1],
            m1[2] - m2[2]);
    }

    template <typename T> 
    inline tmat3x3<T> operator* 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
    {
        return tmat3x3<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s);
    }

    template <typename T> 
    inline tmat3x3<T> operator* 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
    {
        return tmat3x3<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s);
    }

    template <typename T> 
    inline typename tmat3x3<T>::col_type operator* 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::row_type const & v
	)
    {
        return typename tmat3x3<T>::col_type(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
    }

    template <typename T> 
    inline typename tmat3x3<T>::row_type operator* 
	(
		typename tmat3x3<T>::col_type const & v, 
		tmat3x3<T> const & m
	)
    {
        return typename tmat3x3<T>::row_type(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
    }

    template <typename T> 
    inline tmat3x3<T> operator* 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
    {
		typename tmat3x3<T>::value_type const SrcA00 = m1[0][0];
		typename tmat3x3<T>::value_type const SrcA01 = m1[0][1];
		typename tmat3x3<T>::value_type const SrcA02 = m1[0][2];
		typename tmat3x3<T>::value_type const SrcA10 = m1[1][0];
		typename tmat3x3<T>::value_type const SrcA11 = m1[1][1];
		typename tmat3x3<T>::value_type const SrcA12 = m1[1][2];
		typename tmat3x3<T>::value_type const SrcA20 = m1[2][0];
		typename tmat3x3<T>::value_type const SrcA21 = m1[2][1];
		typename tmat3x3<T>::value_type const SrcA22 = m1[2][2];

		typename tmat3x3<T>::value_type const SrcB00 = m2[0][0];
		typename tmat3x3<T>::value_type const SrcB01 = m2[0][1];
		typename tmat3x3<T>::value_type const SrcB02 = m2[0][2];
		typename tmat3x3<T>::value_type const SrcB10 = m2[1][0];
		typename tmat3x3<T>::value_type const SrcB11 = m2[1][1];
		typename tmat3x3<T>::value_type const SrcB12 = m2[1][2];
		typename tmat3x3<T>::value_type const SrcB20 = m2[2][0];
		typename tmat3x3<T>::value_type const SrcB21 = m2[2][1];
		typename tmat3x3<T>::value_type const SrcB22 = m2[2][2];

		tmat3x3<T> Result(tmat3x3<T>::null);
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
		return Result;
    }


    template <typename T> 
    inline tmat3x3<T> operator/ 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
    {
        return tmat3x3<T>(
            m[0] / s,
            m[1] / s,
            m[2] / s);
    }

    template <typename T> 
    inline tmat3x3<T> operator/ 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
    {
        return tmat3x3<T>(
            s / m[0],
            s / m[1],
            s / m[2]);
    }

	template <typename T> 
	inline typename tmat3x3<T>::col_type operator/ 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::row_type const & v
	)
	{
		return m._inverse() * v;
	}

	template <typename T> 
	inline typename tmat3x3<T>::row_type operator/ 
	(
		typename tmat3x3<T>::col_type const & v, 
		tmat3x3<T> const & m
	)
	{
		return v * m._inverse();
	}

	template <typename T> 
	inline tmat3x3<T> operator/ 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return m1 * m2._inverse();
	}

	// Unary constant operators
    template <typename T> 
    inline tmat3x3<T> const operator- 
	(
		tmat3x3<T> const & m
	)
    {
        return tmat3x3<T>(
            -m[0], 
            -m[1],
            -m[2]);
    }

    template <typename T> 
    inline tmat3x3<T> const operator++ 
	(
		tmat3x3<T> const & m, 
		int
	) 
    {
        return tmat3x3<T>(
            m[0] + T(1),
            m[1] + T(1),
            m[2] + T(1));
    }

    template <typename T> 
    inline tmat3x3<T> const operator-- 
	(
		tmat3x3<T> const & m, 
		int
	) 
    {
        return tmat3x3<T>(
            m[0] - T(1),
            m[1] - T(1),
            m[2] - T(1));
    }

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	inline bool operator==
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	template <typename T> 
	inline bool operator!=
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}

} //namespace detail
} //namespace glm
