///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-01-16
// Updated : 2010-02-11
// Licence : This source is under MIT License
// File    : glm/core/type_mat2x2.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat2x2<T>::size_type tmat2x2<T>::col_size()
	{
		return 2;
	}

	template <typename T>
	inline typename tmat2x2<T>::size_type tmat2x2<T>::row_size()
	{
		return 2;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat2x2<T>::col_type &
	tmat2x2<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->row_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat2x2<T>::col_type const &
	tmat2x2<T>::operator[]
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
    inline tmat2x2<T>::tmat2x2()
    {
		this->value[0] = col_type(1, 0);
        this->value[1] = col_type(0, 1);
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = m.value[0];
        this->value[1] = m.value[1];
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		ctor
	)
    {}

    template <typename T> 
	inline tmat2x2<T>::tmat2x2
	(
		value_type const & s
	)
    {
		value_type const Zero(0);
        this->value[0] = col_type(s, Zero);
        this->value[1] = col_type(Zero, s);
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		value_type const & x0, value_type const & y0, 
		value_type const & x1, value_type const & y1
	)
    {
        this->value[0] = col_type(x0, y0);
        this->value[1] = col_type(x1, y1);
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		col_type const & v0, 
		col_type const & v1
	)
    {
        this->value[0] = v0;
        this->value[1] = v1;
    }

    //////////////////////////////////////////////////////////////
    // mat2 conversions

    template <typename T> 
    template <typename U> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat2x2<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
	}

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat3x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat4x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

	template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x2<T>::tmat2x2
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
    }

    template <typename T> 
    inline tmat2x2<T> tmat2x2<T>::_inverse() const
    {
        typename tmat2x2<T>::value_type Determinant = this->value[0][0] * this->value[1][1] - this->value[1][0] * this->value[0][1];

        tmat2x2<T> Inverse(
            + this->value[1][1] / Determinant,
            - this->value[1][0] / Determinant,
            - this->value[0][1] / Determinant, 
            + this->value[0][0] / Determinant);
        return Inverse;
    }

    //////////////////////////////////////////////////////////////
    // mat3 operators

    // This function shouldn't required but it seems that VC7.1 have an optimisation bug if this operator wasn't declared
    template <typename T> 
    inline tmat2x2<T>& tmat2x2<T>::operator=
	(
		tmat2x2<T> const & m
	)
    {
	    this->value[0] = m[0];
	    this->value[1] = m[1];
	    return *this;
    }

	template <typename T> 
	template <typename U> 
    inline tmat2x2<T>& tmat2x2<T>::operator=
	(
		tmat2x2<U> const & m
	)
    {
	    this->value[0] = m[0];
	    this->value[1] = m[1];
	    return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x2<T>& tmat2x2<T>::operator+=
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
    inline tmat2x2<T>& tmat2x2<T>::operator+=
	(
		tmat2x2<U> const & m
	)
    {
	    this->value[0] += m[0];
	    this->value[1] += m[1];
	    return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x2<T>& tmat2x2<T>::operator-=
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
    inline tmat2x2<T>& tmat2x2<T>::operator-=
	(
		tmat2x2<U> const & m
	)
    {
	    this->value[0] -= m[0];
	    this->value[1] -= m[1];
	    return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x2<T>& tmat2x2<T>::operator*= 
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
    inline tmat2x2<T>& tmat2x2<T>::operator*= 
	(
		tmat2x2<U> const & m
	)
    {
        return (*this = *this * m);
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x2<T>& tmat2x2<T>::operator/= 
	(
		U const & s
	)
    {
	    this->value[0] /= s;
	    this->value[1] /= s;
	    return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat2x2<T>& tmat2x2<T>::operator/= 
	(
		tmat2x2<U> const & m
	)
    {
        return (*this = *this / m);
    }

    template <typename T> 
    inline tmat2x2<T>& tmat2x2<T>::operator++ ()
    {
	    ++this->value[0];
	    ++this->value[1];
	    return *this;
    }

    template <typename T> 
    inline tmat2x2<T>& tmat2x2<T>::operator-- ()
    {
	    --this->value[0];
	    --this->value[1];
	    return *this;
    }

    //////////////////////////////////////////////////////////////
	// Binary operators

    template <typename T> 
    inline tmat2x2<T> operator+ 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
    {
        return tmat2x2<T>(
            m[0] + s,
            m[1] + s);
    }

    template <typename T> 
    inline tmat2x2<T> operator+ 
	(
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
    {
        return tmat2x2<T>(
            m[0] + s,
            m[1] + s);
    }

    template <typename T> 
    inline tmat2x2<T> operator+ 
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
    {
        return tmat2x2<T>(
            m1[0] + m2[0],
            m1[1] + m2[1]);
    }

    template <typename T> 
    inline tmat2x2<T> operator- 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
    {
        return tmat2x2<T>(
            m[0] - s,
            m[1] - s);
    }

    template <typename T> 
    inline tmat2x2<T> operator- 
	(
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
    {
        return tmat2x2<T>(
            s - m[0],
            s - m[1]);
    }

    template <typename T> 
    inline tmat2x2<T> operator- 
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
    {
        return tmat2x2<T>(
            m1[0] - m2[0],
            m1[1] - m2[1]);
    }

    template <typename T> 
    inline tmat2x2<T> operator* 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
    {
        return tmat2x2<T>(
            m[0] * s,
            m[1] * s);
    }

	//     X
	//     X
	// X X
	// X X
    template <typename T> 
    inline tmat2x2<T> operator* 
	(	
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
    {
        return tmat2x2<T>(
            m[0] * s,
            m[1] * s);
    }

    template <typename T> 
    inline typename tmat2x2<T>::col_type operator* 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::row_type const & v
	)
    {
        return detail::tvec2<T>(
            m[0][0] * v.x + m[1][0] * v.y,
            m[0][1] * v.x + m[1][1] * v.y);
    }

	//		X X
	//		X X
	// X X 
    template <typename T> 
    inline typename tmat2x2<T>::row_type operator* 
	(
		typename tmat2x2<T>::col_type const & v, 
		tmat2x2<T> const & m
	)
    {
        return detail::tvec2<T>(
            v.x * m[0][0] + v.y * m[0][1],
            v.x * m[1][0] + v.y * m[1][1]);
    }

	template <typename T>
	inline tmat2x2<T> operator* 
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return tmat2x2<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
	}

    template <typename T> 
    inline tmat2x2<T> operator/ 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
    {
        return tmat2x2<T>(
            m[0] / s,
            m[1] / s);
    }

    template <typename T> 
    inline tmat2x2<T> operator/ 
	(
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
    {
        return tmat2x2<T>(
            s / m[0],
            s / m[1]);
    }

    template <typename T> 
    inline typename tmat2x2<T>::col_type operator/ 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::row_type & v
	)
    {
        return m._inverse() * v;
    }

    template <typename T> 
    inline typename tmat2x2<T>::row_type operator/ 
	(
		typename tmat2x2<T>::col_type const & v,
		tmat2x2<T> const & m
	)
    {
        return v * m._inverse();
    }

    template <typename T> 
    inline tmat2x2<T> operator/ 
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
    {
        return m1 * m2._inverse();
    }

	// Unary constant operators
    template <typename T> 
    inline tmat2x2<T> const operator- 
	(
		tmat2x2<T> const & m
	)
    {
        return tmat2x2<T>(
            -m[0], 
            -m[1]);
    }

    template <typename T> 
    inline tmat2x2<T> const operator++ 
	(
		tmat2x2<T> const & m, 
		int
	) 
    {
        return tmat2x2<T>(
            m[0] + T(1),
            m[1] + T(1));
    }

    template <typename T> 
    inline tmat2x2<T> const operator-- 
	(
		tmat2x2<T> const & m, 
		int
	) 
    {
        return tmat2x2<T>(
            m[0] - T(1),
            m[1] - T(1));
    }

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	inline bool operator==
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template <typename T> 
	inline bool operator!=
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}

} //namespace detail
} //namespace glm
