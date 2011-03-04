///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-03
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/func_geometric.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace core{
	namespace function{
	namespace geometric{

    // length
    template <typename genType>
	inline genType length
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'length' only accept floating-point inputs");

        genType sqr = x * x;
        return sqrt(sqr);
    }

	template <typename T>
	inline typename detail::tvec2<T>::value_type length
	(
		detail::tvec2<T> const & v
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'length' only accept floating-point inputs");

        typename detail::tvec2<T>::value_type sqr = v.x * v.x + v.y * v.y;
        return sqrt(sqr);
    }

    template <typename T>
    inline typename detail::tvec3<T>::value_type length
	(
		detail::tvec3<T> const & v
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'length' only accept floating-point inputs");

        typename detail::tvec3<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z;
        return sqrt(sqr);
    }

    template <typename T>
    inline typename detail::tvec4<T>::value_type length
	(
		detail::tvec4<T> const & v
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'length' only accept floating-point inputs");

        typename detail::tvec4<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
        return sqrt(sqr);
    }

    // distance
	template <typename genType>
    inline genType distance
	(
		genType const & p0, 
		genType const & p1
	)
    {
        GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'distance' only accept floating-point inputs");

		return length(p1 - p0);
    }
 
	template <typename T>
	inline typename detail::tvec2<T>::value_type distance
	(
		detail::tvec2<T> const & p0,
		detail::tvec2<T> const & p1
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'distance' only accept floating-point inputs");

        return length(p1 - p0);
    }

    template <typename T>
    inline typename detail::tvec3<T>::value_type distance
	(
		detail::tvec3<T> const & p0,
		detail::tvec3<T> const & p1
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'distance' only accept floating-point inputs");

		return length(p1 - p0);
    }

    template <typename T>
    inline typename detail::tvec4<T>::value_type distance
	(
		detail::tvec4<T> const & p0,
		detail::tvec4<T> const & p1
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'distance' only accept floating-point inputs");

		return length(p1 - p0);
    }

	// dot
	template <typename genType>
	inline genType dot
	(
		genType const & x, 
		genType const & y
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'dot' only accept floating-point inputs");

		return x * y;
	}

    template <typename T>
	inline typename detail::tvec2<T>::value_type dot
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'dot' only accept floating-point inputs");

		return x.x * y.x + x.y * y.y;
    }

    template <typename T>
    inline T dot
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'dot' only accept floating-point inputs");

		return x.x * y.x + x.y * y.y + x.z * y.z;
    }
/* // SSE3
    inline float dot(const tvec4<float>& x, const tvec4<float>& y)
    {
	    float Result;
	    __asm
        {
		    mov		esi, x
		    mov		edi, y
		    movaps	xmm0, [esi]
		    mulps	xmm0, [edi]
		    haddps(	_xmm0, _xmm0 )
		    haddps(	_xmm0, _xmm0 )
		    movss	Result, xmm0
	    }
	    return Result;
    }
*/
    template <typename T>
    inline T dot
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'dot' only accept floating-point inputs");

        return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
    }

    // cross
    template <typename T>
    inline detail::tvec3<T> cross
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'cross' only accept floating-point inputs");

        return detail::tvec3<T>(
            x.y * y.z - y.y * x.z,
            x.z * y.x - y.z * x.x,
            x.x * y.y - y.x * x.y);
    }

    // normalize
    template <typename genType>
    inline genType normalize
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'normalize' only accept floating-point inputs");

        return x < genType(0) ? genType(-1) : genType(1);
    }

    // According to issue 10 GLSL 1.10 specification, if length(x) == 0 then result is undefine and generate an error
    template <typename T>
    inline detail::tvec2<T> normalize
	(
		detail::tvec2<T> const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'normalize' only accept floating-point inputs");
		
		typename detail::tvec2<T>::value_type sqr = x.x * x.x + x.y * x.y;
	    return x * inversesqrt(sqr);
    }

    template <typename T>
    inline detail::tvec3<T> normalize
	(
		detail::tvec3<T> const & x
	)
    {
        GLM_STATIC_ASSERT(detail::type<T>::is_float, "'normalize' only accept floating-point inputs");

		typename detail::tvec3<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z;
	    return x * inversesqrt(sqr);
    }

    template <typename T>
    inline detail::tvec4<T> normalize
	(
		detail::tvec4<T> const & x
	)
    {
        GLM_STATIC_ASSERT(detail::type<T>::is_float, "'normalize' only accept floating-point inputs");
		
		typename detail::tvec4<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w;
	    return x * inversesqrt(sqr);
    }

    // faceforward
	template <typename genType>
	inline genType faceforward
	(
		genType const & N, 
		genType const & I, 
		genType const & Nref
	)
	{
		return dot(Nref, I) < 0 ? N : -N;
	}

	// reflect
	template <typename genType>
	genType reflect
	(
		genType const & I, 
		genType const & N
	)
	{
		return I - N * dot(N, I) * float(2);
	}

    // refract
    template <typename genType>
    inline genType refract
	(
		genType const & I, 
		genType const & N, 
		typename genType::value_type const & eta
	)
    {
		//It could be a vector
		//GLM_STATIC_ASSERT(detail::type<genType>::is_float);

        typename genType::value_type dotValue = dot(N, I);
        typename genType::value_type k = typename genType::value_type(1) - eta * eta * (typename genType::value_type(1) - dotValue * dotValue);
        if(k < typename genType::value_type(0))
            return genType(0);
        else
            return eta * I - (eta * dotValue + sqrt(k)) * N;
    }

	}//namespace geometric
	}//namespace function
	}//namespace core
}//namespace glm
