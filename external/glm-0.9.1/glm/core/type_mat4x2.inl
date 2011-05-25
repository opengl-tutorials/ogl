///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-10-01
// Updated : 2010-02-03
// Licence : This source is under MIT License
// File    : glm/core/type_mat4x2.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat4x2<T>::size_type tmat4x2<T>::col_size()
	{
		return 2;
	}

	template <typename T>
	inline typename tmat4x2<T>::size_type tmat4x2<T>::row_size()
	{
		return 4;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat4x2<T>::col_type & 
	tmat4x2<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->row_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat4x2<T>::col_type const & 
	tmat4x2<T>::operator[]
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
    inline tmat4x2<T>::tmat4x2()
    {
		value_type const Zero(0);
		value_type const One(1);
        this->value[0] = col_type(One, Zero);
        this->value[1] = col_type(Zero, One);
        this->value[2] = col_type(Zero, Zero);
        this->value[3] = col_type(Zero, Zero);
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = m.value[0];
        this->value[1] = m.value[1];
        this->value[2] = m.value[2];
        this->value[3] = m.value[3];
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		ctor
	)
    {}

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		value_type const & s
	)
    {
		value_type const Zero(0);
        this->value[0] = col_type(s, Zero);
        this->value[1] = col_type(Zero, s);
        this->value[2] = col_type(Zero, Zero);
        this->value[3] = col_type(Zero, Zero);
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
    (
        value_type const & x0, value_type const & y0,
        value_type const & x1, value_type const & y1,
        value_type const & x2, value_type const & y2,
        value_type const & x3, value_type const & y3
    )
    {
        this->value[0] = col_type(x0, y0);
        this->value[1] = col_type(x1, y1);
        this->value[2] = col_type(x2, y2);
        this->value[3] = col_type(x3, y3);
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
    (
        col_type const & v0, 
        col_type const & v1, 
        col_type const & v2,
        col_type const & v3
    )
    {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
        this->value[3] = v3;
    }

    // Conversion
    template <typename T> 
    template <typename U> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat4x2<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
        this->value[3] = col_type(m[3]);
	}

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(value_type(0));
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat3x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat4x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
        this->value[3] = col_type(m[3]);
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(value_type(0));
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(value_type(0));
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
        this->value[3] = col_type(m[3]);
    }

    template <typename T> 
    inline tmat4x2<T>::tmat4x2
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
        this->value[3] = col_type(value_type(0));
    }

    //////////////////////////////////////////////////////////////
    // Unary updatable operators

    template <typename T> 
    inline tmat4x2<T>& tmat4x2<T>::operator= 
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x2<T>& tmat4x2<T>::operator= 
	(
		tmat4x2<U> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x2<T> & tmat4x2<T>::operator+= 
	(
		U const & s
	)
    {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        this->value[3] += s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x2<T> & tmat4x2<T>::operator+= 
	(
		tmat4x2<U> const & m
	)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        this->value[3] += m[3];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x2<T> & tmat4x2<T>::operator-= 
	(
		U const & s
	)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        this->value[3] -= s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x2<T> & tmat4x2<T>::operator-= 
	(
		tmat4x2<U> const & m
	)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[2] -= m[2];
        this->value[3] -= m[3];
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x2<T> & tmat4x2<T>::operator*= 
	(
		U const & s
	)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        this->value[3] *= s;
        return *this;
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x2<T> & tmat4x2<T>::operator*= 
	(
		tmat4x2<U> const & m
	)
    {
        return (*this = tmat4x2<T>(*this * m));
    }

    template <typename T>
	template <typename U> 
    inline tmat4x2<T> & tmat4x2<T>::operator/= 
	(
		U const & s
	)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        this->value[3] /= s;
        return *this;
    }

    template <typename T> 
    inline tmat4x2<T> & tmat4x2<T>::operator++ ()
    {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        ++this->value[3];
        return *this;
    }

    template <typename T> 
    inline tmat4x2<T> & tmat4x2<T>::operator-- ()
    {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        --this->value[3];
        return *this;
    }

    //////////////////////////////////////////////////////////////
    // Binary operators

    template <typename T> 
    inline tmat4x2<T> operator+ 
	(
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s
	)
    {
        return tmat4x2<T>(
            m[0] + s,
            m[1] + s,
            m[2] + s,
            m[3] + s);
    }

    template <typename T> 
    inline tmat4x2<T> operator+ 
	(	
		tmat4x2<T> const & m1, 
		tmat4x2<T> const & m2
	)
    {
        return tmat4x2<T>(
            m1[0] + m2[0],
            m1[1] + m2[1],
            m1[2] + m2[2],
            m1[3] + m2[3]);
    }

    template <typename T> 
    inline tmat4x2<T> operator- 
	(
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s
	)
    {
        return tmat4x2<T>(
            m[0] - s,
            m[1] - s,
            m[2] - s,
            m[3] - s);
    }

    template <typename T> 
    inline tmat4x2<T> operator- 
	(	
		tmat4x2<T> const & m1, 
		tmat4x2<T> const & m2
	)
    {
        return tmat4x2<T>(
            m1[0] - m2[0],
            m1[1] - m2[1],
            m1[2] - m2[2],
            m1[3] - m2[3]);
    }

    template <typename T> 
    inline tmat4x2<T> operator* 
	(
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s
	)
    {
        return tmat4x2<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s,
            m[3] * s);
    }

    template <typename T> 
    inline tmat4x2<T> operator* 
	(
		typename tmat4x2<T>::value_type const & s, 
		tmat4x2<T> const & m
	)
    {
        return tmat4x2<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s,
            m[3] * s);
    }

    template <typename T>
    inline typename tmat4x2<T>::col_type operator* 
	(
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::row_type const & v)
    {
        return typename tmat4x2<T>::col_type(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w);
    }

    template <typename T> 
    inline typename tmat4x2<T>::row_type operator* 
	(
		typename tmat4x2<T>::col_type const & v, 
		tmat4x2<T> const & m) 
    {
        return typename tmat4x2<T>::row_type(
            v.x * m[0][0] + v.y * m[0][1],
            v.x * m[1][0] + v.y * m[1][1],
            v.x * m[2][0] + v.y * m[2][1],
            v.x * m[3][0] + v.y * m[3][1]);
    }

    template <typename T> 
    inline tmat2x2<T> operator* 
	(
		tmat4x2<T> const & m1, 
		tmat2x4<T> const & m2
	)
    {
        T const SrcA00 = m1[0][0];
        T const SrcA01 = m1[0][1];
        T const SrcA10 = m1[1][0];
        T const SrcA11 = m1[1][1];
        T const SrcA20 = m1[2][0];
        T const SrcA21 = m1[2][1];
        T const SrcA30 = m1[3][0];
        T const SrcA31 = m1[3][1];

        T const SrcB00 = m2[0][0];
        T const SrcB01 = m2[0][1];
        T const SrcB02 = m2[0][2];
        T const SrcB03 = m2[0][3];
        T const SrcB10 = m2[1][0];
        T const SrcB11 = m2[1][1];
        T const SrcB12 = m2[1][2];
        T const SrcB13 = m2[1][3];

        tmat2x2<T> Result(tmat2x2<T>::null);
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02 + SrcA30 * SrcB03;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02 + SrcA31 * SrcB03;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12 + SrcA30 * SrcB13;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12 + SrcA31 * SrcB13;
        return Result;
    }

    template <typename T> 
    inline tmat4x2<T> operator/ 
	(
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s
	)
    {
        return tmat4x2<T>(
            m[0] / s,
            m[1] / s,
            m[2] / s,
            m[3] / s);        
    }

    template <typename T> 
    inline tmat4x2<T> operator/ 
	(
		typename tmat4x2<T>::value_type const & s, 
		tmat4x2<T> const & m
	)
    {
        return tmat4x2<T>(
            s / m[0],
            s / m[1],
            s / m[2],
            s / m[3]);        
    }

	// Unary constant operators
    template <typename T> 
    inline tmat4x2<T> const operator- 
	(
		tmat4x2<T> const & m
	)
    {
        return tmat4x2<T>(
            -m[0], 
            -m[1], 
            -m[2], 
            -m[3]);
    }

    template <typename T> 
    inline tmat4x2<T> const operator++ 
	(
		tmat4x2<T> const & m, 
		int
	) 
    {
        return tmat4x2<T>(
			m[0] + typename tmat4x2<T>::value_type(1),
            m[1] + typename tmat4x2<T>::value_type(1),
            m[2] + typename tmat4x2<T>::value_type(1),
            m[3] + typename tmat4x2<T>::value_type(1));
    }

    template <typename T> 
    inline tmat4x2<T> const operator-- 
	(
		tmat4x2<T> const & m, 
		int
	) 
    {
        return tmat4x2<T>(
            m[0] - typename tmat4x2<T>::value_type(1),
            m[1] - typename tmat4x2<T>::value_type(1),
            m[2] - typename tmat4x2<T>::value_type(1),
            m[3] - typename tmat4x2<T>::value_type(1));
    }

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	inline bool operator==
	(
		tmat4x2<T> const & m1, 
		tmat4x2<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	template <typename T> 
	inline bool operator!=
	(
		tmat4x2<T> const & m1, 
		tmat4x2<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}

} //namespace detail
} //namespace glm
