///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-04-17
// Updated : 2010-02-02
// Licence : This source is under MIT License
// File    : glm/core/type_mat4x3.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat4x3<T>::size_type tmat4x3<T>::col_size()
	{
		return 3;
	}

	template <typename T>
	inline typename tmat4x3<T>::size_type tmat4x3<T>::row_size()
	{
		return 4;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat4x3<T>::col_type & 
	tmat4x3<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->row_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat4x3<T>::col_type const & 
	tmat4x3<T>::operator[]
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
    inline tmat4x3<T>::tmat4x3()
    {
		value_type const Zero(0);
		value_type const One(1);
        this->value[0] = col_type(One, Zero, Zero);
        this->value[1] = col_type(Zero, One, Zero);
        this->value[2] = col_type(Zero, Zero, One);
        this->value[3] = col_type(Zero, Zero, Zero);
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = m.value[0];
        this->value[1] = m.value[1];
        this->value[2] = m.value[2];
        this->value[3] = m.value[3];
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
	(
		ctor
	)
    {}

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
	(
		value_type const & s
	)
    {
		value_type const Zero(0);
        this->value[0] = col_type(s, Zero, Zero);
        this->value[1] = col_type(Zero, s, Zero);
        this->value[2] = col_type(Zero, Zero, s);
        this->value[3] = col_type(Zero, Zero, Zero);
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
    (
        value_type const & x0, value_type const & y0, value_type const & z0,
        value_type const & x1, value_type const & y1, value_type const & z1,
        value_type const & x2, value_type const & y2, value_type const & z2,
        value_type const & x3, value_type const & y3, value_type const & z3
    )
    {
        this->value[0] = col_type(x0, y0, z0);
        this->value[1] = col_type(x1, y1, z1);
        this->value[2] = col_type(x2, y2, z2);
        this->value[3] = col_type(x3, y3, z3);
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
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

    //////////////////////////////////////////////////////////////
    // Conversions

    template <typename T> 
    template <typename U> 
    inline tmat4x3<T>::tmat4x3
	(
		tmat4x3<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
        this->value[3] = col_type(m[3]);
	}

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], value_type(0));
        this->value[1] = col_type(m[1], value_type(0));
        this->value[2] = col_type(m[2], value_type(1));
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
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
    inline tmat4x3<T>::tmat4x3
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
    inline tmat4x3<T>::tmat4x3
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(value_type(0), value_type(0), value_type(1));
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], value_type(0));
        this->value[1] = col_type(m[1], value_type(0));
        this->value[2] = col_type(m[2], value_type(1));
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(value_type(0), value_type(0), value_type(1));
        this->value[3] = col_type(value_type(0));
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = col_type(m[0], value_type(0));
        this->value[1] = col_type(m[1], value_type(0));
        this->value[2] = col_type(m[2], value_type(1));
        this->value[3] = col_type(m[3], value_type(0));
    }

    template <typename T> 
    inline tmat4x3<T>::tmat4x3
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
    inline tmat4x3<T>& tmat4x3<T>::operator= 
	(
		tmat4x3<T> const & m
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
    inline tmat4x3<T>& tmat4x3<T>::operator= 
	(
		tmat4x3<U> const & m
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
    inline tmat4x3<T> & tmat4x3<T>::operator+= 
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
    inline tmat4x3<T> & tmat4x3<T>::operator+= 
	(
		tmat4x3<U> const & m
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
    inline tmat4x3<T> & tmat4x3<T>::operator-= 
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
    inline tmat4x3<T> & tmat4x3<T>::operator-= 
	(
		tmat4x3<U> const & m
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
    inline tmat4x3<T> & tmat4x3<T>::operator*= 
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
    inline tmat4x3<T> & tmat4x3<T>::operator*= 
	(
		tmat4x3<U> const & m
	)
    {
        return (*this = tmat4x3<T>(*this * m));
    }

    template <typename T> 
	template <typename U> 
    inline tmat4x3<T> & tmat4x3<T>::operator/= 
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
    inline tmat4x3<T> & tmat4x3<T>::operator++ ()
    {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        ++this->value[3];
        return *this;
    }

    template <typename T> 
    inline tmat4x3<T> & tmat4x3<T>::operator-- ()
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
    inline tmat4x3<T> operator+ (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s)
    {
        return tmat4x3<T>(
            m[0] + s,
            m[1] + s,
            m[2] + s,
            m[3] + s);
    }

    template <typename T> 
    inline tmat4x3<T> operator+ (
		tmat4x3<T> const & m1, 
		tmat4x3<T> const & m2)
    {
        return tmat4x3<T>(
            m1[0] + m2[0],
            m1[1] + m2[1],
            m1[2] + m2[2],
            m1[3] + m2[3]);
    }

    template <typename T> 
    inline tmat4x3<T> operator- (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s)
    {
        return tmat4x3<T>(
            m[0] - s,
            m[1] - s,
            m[2] - s,
            m[3] - s);
    }

    template <typename T> 
    inline tmat4x3<T> operator- (
		tmat4x3<T> const & m1, 
		tmat4x3<T> const & m2)
    {
        return tmat4x3<T>(
            m1[0] - m2[0],
            m1[1] - m2[1],
            m1[2] - m2[2],
            m1[3] - m2[3]);
    }

    template <typename T> 
    inline tmat4x3<T> operator* (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s)
    {
        return tmat4x3<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s,
            m[3] * s);
    }

    template <typename T> 
    inline tmat4x3<T> operator* (
		typename tmat4x3<T>::value_type const & s, 
		tmat4x3<T> const & m)
    {
        return tmat4x3<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s,
            m[3] * s);
    }
   
    template <typename T>
    inline typename tmat4x3<T>::col_type operator* 
	(
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::row_type const & v)
    {
        return typename tmat4x3<T>::col_type(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w);
    }

    template <typename T> 
    inline typename tmat4x3<T>::row_type operator* 
	(
		typename tmat4x3<T>::col_type const & v, 
		tmat4x3<T> const & m) 
    {
        return typename tmat4x3<T>::row_type(
            v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2],
            v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2],
            v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2],
            v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2]);
    }

    template <typename T> 
    inline tmat3x3<T> operator* 
	(
		tmat4x3<T> const & m1, 
		tmat3x4<T> const & m2
	)
    {
        T const SrcA00 = m1[0][0];
        T const SrcA01 = m1[0][1];
        T const SrcA02 = m1[0][2];
        T const SrcA10 = m1[1][0];
		T const SrcA11 = m1[1][1];
        T const SrcA12 = m1[1][2];
        T const SrcA20 = m1[2][0];
        T const SrcA21 = m1[2][1];
        T const SrcA22 = m1[2][2];
        T const SrcA30 = m1[3][0];
        T const SrcA31 = m1[3][1];
        T const SrcA32 = m1[3][2];

        T const SrcB00 = m2[0][0];
        T const SrcB01 = m2[0][1];
        T const SrcB02 = m2[0][2];
        T const SrcB03 = m2[0][3];
        T const SrcB10 = m2[1][0];
        T const SrcB11 = m2[1][1];
        T const SrcB12 = m2[1][2];
        T const SrcB13 = m2[1][3];
        T const SrcB20 = m2[2][0];
        T const SrcB21 = m2[2][1];
        T const SrcB22 = m2[2][2];
        T const SrcB23 = m2[2][3];

        tmat3x3<T> Result(tmat3x3<T>::null);
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02 + SrcA30 * SrcB03;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02 + SrcA31 * SrcB03;
        Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02 + SrcA32 * SrcB03;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12 + SrcA30 * SrcB13;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12 + SrcA31 * SrcB13;
        Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12 + SrcA32 * SrcB13;
        Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22 + SrcA30 * SrcB23;
        Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22 + SrcA31 * SrcB23;
        Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22 + SrcA32 * SrcB23;
        return Result;
    }

    template <typename T> 
    inline tmat4x3<T> operator/ 
	(
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s
	)
    {
        return tmat4x3<T>(
            m[0] / s,
            m[1] / s,
            m[2] / s,
            m[3] / s);        
    }

    template <typename T> 
    inline tmat4x3<T> operator/ 
	(
		typename tmat4x3<T>::value_type const & s, 
		tmat4x3<T> const & m
	)
    {
        return tmat4x3<T>(
            s / m[0],
            s / m[1],
            s / m[2],
            s / m[3]);        
    }

	// Unary constant operators
    template <typename T> 
    inline tmat4x3<T> const operator- 
	(
		tmat4x3<T> const & m
	)
    {
        return tmat4x3<T>(
            -m[0], 
            -m[1],
            -m[2],
            -m[3]);
    }

    template <typename T> 
    inline tmat4x3<T> const operator++ 
	(
		tmat4x3<T> const & m, 
		int
	) 
    {
        return tmat4x3<T>(
            m[0] + T(1),
            m[1] + T(1),
            m[2] + T(1),
            m[3] + T(1));
    }

    template <typename T> 
    inline tmat4x3<T> const operator-- 
	(
		tmat4x3<T> const & m, 
		int
	) 
    {
        return tmat4x3<T>(
            m[0] - T(1),
            m[1] - T(1),
            m[2] - T(1),
            m[3] - T(1));
    }

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	inline bool operator==
	(
		tmat4x3<T> const & m1, 
		tmat4x3<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	template <typename T> 
	inline bool operator!=
	(
		tmat4x3<T> const & m1, 
		tmat4x3<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}

} //namespace detail
} //namespace glm

