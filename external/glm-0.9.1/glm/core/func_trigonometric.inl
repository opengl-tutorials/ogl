///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-03
// Updated : 2008-09-14
// Licence : This source is under MIT License
// File    : glm/core/func_trigonometric.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace core{
	namespace function{
	namespace trigonometric{

    // radians
    template <typename genType>
    inline genType radians
	(
		genType const & degrees
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'radians' only accept floating-point input");

        const genType pi = genType(3.1415926535897932384626433832795);
        return degrees * (pi / genType(180));
    }

    template <typename T>
	inline detail::tvec2<T> radians
	(
		detail::tvec2<T> const & degrees
	)
    {
        return detail::tvec2<T>(
            radians(degrees.x),
            radians(degrees.y));
    }

    template <typename T>
    inline detail::tvec3<T> radians
	(
		detail::tvec3<T> const & degrees
	)
    {
        return detail::tvec3<T>(
            radians(degrees.x),
            radians(degrees.y),
            radians(degrees.z));
    }

    template <typename T>
    inline detail::tvec4<T> radians
	(
		detail::tvec4<T> const & degrees
	)
    {
        return detail::tvec4<T>(
            radians(degrees.x),
            radians(degrees.y),
            radians(degrees.z),
            radians(degrees.w));
    }

    // degrees
    template <typename genType>
    inline genType degrees
	(
		genType const & radians
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'degrees' only accept floating-point input");

        const genType pi = genType(3.1415926535897932384626433832795);
        return radians * (genType(180) / pi);
    }

    template <typename T>
    inline detail::tvec2<T> degrees
	(
		detail::tvec2<T> const & radians
	)
    {
        return detail::tvec2<T>(
            degrees(radians.x),
            degrees(radians.y));
    }

    template <typename T>
    inline detail::tvec3<T> degrees
	(	
		detail::tvec3<T> const & radians
	)
    {
        return detail::tvec3<T>(
            degrees(radians.x),
            degrees(radians.y),
            degrees(radians.z));
    }

    template <typename T>
    inline detail::tvec4<T> degrees
	(
		detail::tvec4<T> const & radians
	)
    {
        return detail::tvec4<T>(
            degrees(radians.x),
            degrees(radians.y),
            degrees(radians.z),
            degrees(radians.w));
    }

    // sin
    template <typename genType>
    inline genType sin
	(
		genType const & angle
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sin' only accept floating-point input");

		return ::std::sin(angle);
    }

    template <typename T>
    inline detail::tvec2<T> sin
	(
		detail::tvec2<T> const & angle
	)
    {
        return detail::tvec2<T>(
            sin(angle.x),
            sin(angle.y));
    }

    template <typename T>
    inline detail::tvec3<T> sin
	(
		detail::tvec3<T> const & angle
	)
    {
        return detail::tvec3<T>(
            sin(angle.x),
            sin(angle.y),
            sin(angle.z));
    }

    template <typename T>
    inline detail::tvec4<T> sin
	(
		detail::tvec4<T> const & angle
	)
    {
        return detail::tvec4<T>(
            sin(angle.x),
            sin(angle.y),
            sin(angle.z),
            sin(angle.w));
    }

    // cos
    template <typename genType>
    inline genType cos(genType const & angle)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'cos' only accept floating-point input");

        return ::std::cos(angle);
    }

    template <typename T>
    inline detail::tvec2<T> cos
	(
		detail::tvec2<T> const & angle
	)
    {
        return detail::tvec2<T>(
            cos(angle.x),
            cos(angle.y));
    }

    template <typename T>
    inline detail::tvec3<T> cos
	(
		detail::tvec3<T> const & angle
	)
    {
        return detail::tvec3<T>(
            cos(angle.x),
            cos(angle.y),
            cos(angle.z));
    }

    template <typename T>
    inline detail::tvec4<T> cos
	(	
		detail::tvec4<T> const & angle
	)
    {
        return detail::tvec4<T>(
            cos(angle.x),
            cos(angle.y),
            cos(angle.z),
            cos(angle.w));
    }

    // tan
    template <typename genType>
    inline genType tan
	(
		genType const & angle
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'tan' only accept floating-point input");

        return ::std::tan(angle);
    }

    template <typename T>
    inline detail::tvec2<T> tan
	(
		detail::tvec2<T> const & angle
	)
    {
        return detail::tvec2<T>(
            tan(angle.x),
            tan(angle.y));
    }

    template <typename T>
    inline detail::tvec3<T> tan
	(
		detail::tvec3<T> const & angle
	)
    {
        return detail::tvec3<T>(
            tan(angle.x),
            tan(angle.y),
            tan(angle.z));
    }

    template <typename T>
    inline detail::tvec4<T> tan
	(
		detail::tvec4<T> const & angle
	)
    {
        return detail::tvec4<T>(
            tan(angle.x),
            tan(angle.y),
            tan(angle.z),
            tan(angle.w));
    }

    // asin
    template <typename genType>
    inline genType asin
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asin' only accept floating-point input");

        return ::std::asin(x);
    }

    template <typename T>
	inline detail::tvec2<T> asin
	(
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            asin(x.x),
            asin(x.y));
    }

    template <typename T>
	inline detail::tvec3<T> asin
	(
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            asin(x.x),
            asin(x.y),
            asin(x.z));
    }

    template <typename T>
	inline detail::tvec4<T> asin
	(
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            asin(x.x),
            asin(x.y),
            asin(x.z),
            asin(x.w));
    }

    // acos
    template <typename genType>
    inline genType acos
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acos' only accept floating-point input");

        return ::std::acos(x);
    }

    template <typename T>
	inline detail::tvec2<T> acos
	(
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            acos(x.x),
            acos(x.y));
    }

    template <typename T>
	inline detail::tvec3<T> acos
	(
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            acos(x.x),
            acos(x.y),
            acos(x.z));
    }

    template <typename T>
	inline detail::tvec4<T> acos
	(
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            acos(x.x),
            acos(x.y),
            acos(x.z),
            acos(x.w));
    }

    // atan
    template <typename genType>
    inline genType atan
	(
		genType const & y, 
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'atan' only accept floating-point input");

        return ::std::atan2(y, x);
    }

    template <typename T>
    inline detail::tvec2<T> atan
	(
		detail::tvec2<T> const & y, 
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            atan(y.x, x.x),
            atan(y.y, x.y));
    }

    template <typename T>
    inline detail::tvec3<T> atan
	(
		detail::tvec3<T> const & y, 
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            atan(y.x, x.x),
            atan(y.y, x.y),
            atan(y.z, x.z));
    }

    template <typename T>
    inline detail::tvec4<T> atan
	(
		detail::tvec4<T> const & y, 
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            atan(y.x, x.x),
            atan(y.y, x.y),
            atan(y.z, x.z),
            atan(y.w, x.w));
    }

    template <typename genType>
    inline genType atan
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'atan' only accept floating-point input");

        return ::std::atan(x);
    }

    template <typename T>
    inline detail::tvec2<T> atan
	(
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            atan(x.x),
            atan(x.y));
    }

    template <typename T>
    inline detail::tvec3<T> atan
	(
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            atan(x.x),
            atan(x.y),
            atan(x.z));
    }

    template <typename T>
    inline detail::tvec4<T> atan
	(
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            atan(x.x),
            atan(x.y),
            atan(x.z),
            atan(x.w));
    }

    // sinh
    template <typename genType> 
    inline genType sinh
	(
		genType const & angle
	)
    {
        GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sinh' only accept floating-point input");

		return std::sinh(angle);
    }

    template <typename T> 
    inline detail::tvec2<T> sinh
	(
		detail::tvec2<T> const & angle
	)
    {
        return detail::tvec2<T>(
            sinh(angle.x),
            sinh(angle.y));
    }

    template <typename T> 
    inline detail::tvec3<T> sinh
	(
		detail::tvec3<T> const & angle
	)
    {
        return detail::tvec3<T>(
            sinh(angle.x),
            sinh(angle.y),
            sinh(angle.z));
    }

    template <typename T> 
    inline detail::tvec4<T> sinh
	(
		detail::tvec4<T> const & angle
	)
    {
        return detail::tvec4<T>(
            sinh(angle.x),
            sinh(angle.y),
            sinh(angle.z),
            sinh(angle.w));
    }

    // cosh
    template <typename genType> 
    inline genType cosh
	(
		genType const & angle
	)
    {
        GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'cosh' only accept floating-point input");

		return std::cosh(angle);
    }

    template <typename T> 
    inline detail::tvec2<T> cosh
	(
		detail::tvec2<T> const & angle
	)
    {
        return detail::tvec2<T>(
            cosh(angle.x),
            cosh(angle.y));
    }

    template <typename T> 
    inline detail::tvec3<T> cosh
	(
		detail::tvec3<T> const & angle
	)
    {
        return detail::tvec3<T>(
            cosh(angle.x),
            cosh(angle.y),
            cosh(angle.z));
    }

    template <typename T> 
    inline detail::tvec4<T> cosh
	(
		detail::tvec4<T> const & angle
	)
    {
        return detail::tvec4<T>(
            cosh(angle.x),
            cosh(angle.y),
            cosh(angle.z),
            cosh(angle.w));
    }

    // tanh
    template <typename genType>
    inline genType tanh
	(
		genType const & angle
	)
    {
        GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'tanh' only accept floating-point input");

		return std::tanh(angle);
    }

    template <typename T> 
    inline detail::tvec2<T> tanh
	(
		detail::tvec2<T> const & angle
	)
    {
        return detail::tvec2<T>(
            tanh(angle.x),
            tanh(angle.y));
    }

    template <typename T> 
    inline detail::tvec3<T> tanh
	(
		detail::tvec3<T> const & angle
	)
    {
        return detail::tvec3<T>(
            tanh(angle.x),
            tanh(angle.y),
            tanh(angle.z));
    }

    template <typename T> 
    inline detail::tvec4<T> tanh
	(
		detail::tvec4<T> const & angle
	)
    {
        return detail::tvec4<T>(
            tanh(angle.x),
            tanh(angle.y),
            tanh(angle.z),
            tanh(angle.w));
    }

    // asinh
    template <typename genType> 
    inline genType asinh
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asinh' only accept floating-point input");
		
		return (x < genType(0) ? genType(-1) : (x > genType(0) ? genType(1) : genType(0))) * log(abs(x) + sqrt(genType(1) + x * x));
    }

    template <typename T> 
    inline detail::tvec2<T> asinh
	(
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            asinh(x.x),
            asinh(x.y));
    }

    template <typename T> 
    inline detail::tvec3<T> asinh
	(
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            asinh(x.x),
            asinh(x.y),
            asinh(x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> asinh
	(
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            asinh(x.x),
            asinh(x.y),
            asinh(x.z),
            asinh(x.w));
    }

    // acosh
    template <typename genType> 
    inline genType acosh
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acosh' only accept floating-point input");

		if(x < genType(1))
			return genType(0);
		return log(x + sqrt(x * x - genType(1)));
    }

	template <typename T> 
	inline detail::tvec2<T> acosh
	(
		detail::tvec2<T> const & x
	)
	{
		return detail::tvec2<T>(
			acosh(x.x),
			acosh(x.y));
	}

    template <typename T> 
    inline detail::tvec3<T> acosh
	(
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            acosh(x.x),
            acosh(x.y),
            acosh(x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> acosh
	(
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            acosh(x.x),
            acosh(x.y),
            acosh(x.z),
            acosh(x.w));
    }

    // atanh
    template <typename genType>
    inline genType atanh
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'atanh' only accept floating-point input");
		
		if(abs(x) >= genType(1))
			return 0;
		return genType(0.5) * log((genType(1) + x) / (genType(1) - x));
    }

    template <typename T> 
    inline detail::tvec2<T> atanh
	(
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            atanh(x.x),
            atanh(x.y));
    }

    template <typename T> 
    inline detail::tvec3<T> atanh
	(
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            atanh(x.x),
            atanh(x.y),
            atanh(x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> atanh
	(
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            atanh(x.x),
            atanh(x.y),
            atanh(x.z),
            atanh(x.w));
    }

	}//namespace trigonometric
	}//namespace function
	}//namespace core
}//namespace glm
