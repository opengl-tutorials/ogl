///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-03
// Updated : 2010-01-26
// Licence : This source is under MIT License
// File    : glm/core/func_common.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace detail
	{
		template <typename genFIType, bool /*signed*/>
		struct Abs_
		{
		};

		template <typename genFIType>
		struct Abs_<genFIType, true>
		{
			static genFIType get(genFIType const & x)
			{
				GLM_STATIC_ASSERT(
					detail::type<genFIType>::is_float || 
					detail::type<genFIType>::is_int, "'abs' only accept floating-point and integer inputs");
				return x >= genFIType(0) ? x : -x;
			}
		};

		template <typename genFIType>
		struct Abs_<genFIType, false>
		{
			static genFIType get(genFIType const & x)
			{
				GLM_STATIC_ASSERT(
					detail::type<genFIType>::is_uint, "'abs' only accept floating-point and integer inputs");

				return x;
			}
		};
	}//namespace detail

	namespace core{
	namespace function{
	namespace common{

	// abs
	template <typename genFIType>
    inline genFIType abs(
		genFIType const & x)
    {
		return detail::Abs_<genFIType, std::numeric_limits<genFIType>::is_signed>::get(x);
    }

	//template <typename T> 
	//inline detail::tvec1<T> abs(
	//	detail::tvec1<T> const & v)
	//{
	//	return detail::tvec1<T>(
	//		abs(v.x));	
	//}

    template <typename T>
    inline detail::tvec2<T> abs(
		detail::tvec2<T> const & v)
    {
        return detail::tvec2<T>(
            abs(v.x),
            abs(v.y));
    }

    template <typename T>
    inline detail::tvec3<T> abs(
		detail::tvec3<T> const & v)
    {
        return detail::tvec3<T>(
            abs(v.x),
            abs(v.y),
            abs(v.z));
    }

    template <typename T>
    inline detail::tvec4<T> abs(
		detail::tvec4<T> const & v)
    {
        return detail::tvec4<T>(
            abs(v.x),
            abs(v.y),
            abs(v.z),
            abs(v.w));
    }

    // sign

	//Try something like based on x >> 31 to get the sign bit
    template <typename genFIType> 
	inline genFIType sign(
		genFIType const & x)
	{
		GLM_STATIC_ASSERT(
			detail::type<genFIType>::is_float || 
			detail::type<genFIType>::is_int, "'sign' only accept signed inputs");
        
		genFIType result;
		if(x > genFIType(0))
            result = genFIType(1);
        else if(x < genFIType(0))
            result = genFIType(-1);
        else
            result = genFIType(0);
        return result;
	}
	
    template <typename valFIType>
    inline detail::tvec2<valFIType> sign(
		detail::tvec2<valFIType> const & x)
    {
        return detail::tvec2<valFIType>(
            sign(x.x),
            sign(x.y));
    }

    template <typename valFIType>
    inline detail::tvec3<valFIType> sign(
		detail::tvec3<valFIType> const & x)
    {
        return detail::tvec3<valFIType>(
            sign(x.x),
            sign(x.y),
            sign(x.z));
    }

    template <typename valFIType>
    inline detail::tvec4<valFIType> sign(
		detail::tvec4<valFIType> const & x)
    {
        return detail::tvec4<valFIType>(
            sign(x.x),
            sign(x.y),
            sign(x.z),
            sign(x.w));
    }

    // floor
    template <>
	inline detail::thalf floor<detail::thalf>(detail::thalf const& x)
    {
        return detail::thalf(::std::floor(float(x)));
    }

    template <typename genType>
    inline genType floor(genType const& x)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'floor' only accept floating-point inputs");

        return ::std::floor(x);
    }

    template <typename valType>
    inline detail::tvec2<valType> floor(detail::tvec2<valType> const& x)
    {
        return detail::tvec2<valType>(
            floor(x.x),
            floor(x.y));
    }

    template <typename valType>
    inline detail::tvec3<valType> floor(detail::tvec3<valType> const& x)
    {
        return detail::tvec3<valType>(
            floor(x.x),
            floor(x.y),
            floor(x.z));
    }

    template <typename valType>
    inline detail::tvec4<valType> floor(detail::tvec4<valType> const& x)
    {
        return detail::tvec4<valType>(
            floor(x.x),
            floor(x.y),
            floor(x.z),
            floor(x.w));
    }

    // trunc
    template <typename genType>
    inline genType trunc(genType const & x)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'trunc' only accept floating-point inputs");
        return x < 0 ? -floor(-x) : floor(x);
    }

    template <typename valType>
    inline detail::tvec2<valType> trunc(detail::tvec2<valType> const & x)
    {
        return detail::tvec2<valType>(
            trunc(x.x),
            trunc(x.y));
    }

    template <typename valType>
    inline detail::tvec3<valType> trunc(detail::tvec3<valType> const & x)
    {
        return detail::tvec3<valType>(
            trunc(x.x),
            trunc(x.y),
            trunc(x.z));
    }

    template <typename valType>
    inline detail::tvec4<valType> trunc(detail::tvec4<valType> const & x)
    {
        return detail::tvec4<valType>(
            trunc(x.x),
            trunc(x.y),
            trunc(x.z),
            trunc(x.w));
    }

    // round
    template <typename genType>
    inline genType round(genType const& x)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'round' only accept floating-point inputs");

        return genType(int(x + genType(0.5)));
    }

    template <typename valType>
    inline detail::tvec2<valType> round(detail::tvec2<valType> const& x)
    {
        return detail::tvec2<valType>(
            round(x.x),
            round(x.y));
    }

    template <typename valType>
    inline detail::tvec3<valType> round(detail::tvec3<valType> const& x)
    {
        return detail::tvec3<valType>(
            round(x.x),
            round(x.y),
            round(x.z));
    }

    template <typename valType>
    inline detail::tvec4<valType> round(detail::tvec4<valType> const& x)
    {
        return detail::tvec4<valType>(
            round(x.x),
            round(x.y),
            round(x.z),
            round(x.w));
    }

    // roundEven
    template <typename genType>
    inline genType roundEven(genType const& x)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'roundEven' only accept floating-point inputs");

		return genType(int(x + genType(int(x) % 2)));
    }

    template <typename valType>
    inline detail::tvec2<valType> roundEven(detail::tvec2<valType> const& x)
    {
        return detail::tvec2<valType>(
            roundEven(x.x),
            roundEven(x.y));
    }

    template <typename valType>
    inline detail::tvec3<valType> roundEven(detail::tvec3<valType> const& x)
    {
        return detail::tvec3<valType>(
            roundEven(x.x),
            roundEven(x.y),
            roundEven(x.z));
    }

    template <typename valType>
    inline detail::tvec4<valType> roundEven(detail::tvec4<valType> const& x)
    {
        return detail::tvec4<valType>(
            roundEven(x.x),
            roundEven(x.y),
            roundEven(x.z),
            roundEven(x.w));
    }

    // ceil
    template <typename genType>
    inline genType ceil(genType const & x)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'ceil' only accept floating-point inputs");

        return ::std::ceil(x);
    }

    template <typename valType>
    inline detail::tvec2<valType> ceil(detail::tvec2<valType> const & x)
    {
        return detail::tvec2<valType>(
            ceil(x.x),
            ceil(x.y));
    }

    template <typename valType>
    inline detail::tvec3<valType> ceil(detail::tvec3<valType> const & x)
    {
        return detail::tvec3<valType>(
            ceil(x.x),
            ceil(x.y),
            ceil(x.z));
    }

    template <typename valType>
    inline detail::tvec4<valType> ceil(detail::tvec4<valType> const & x)
    {
        return detail::tvec4<valType>(
            ceil(x.x),
            ceil(x.y),
            ceil(x.z),
            ceil(x.w));
    }

    // fract
    template <typename genType>
    inline genType fract
	(
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'fract' only accept floating-point inputs");

        return x - ::std::floor(x);
    }

    template <typename valType>
    inline detail::tvec2<valType> fract
	(
		detail::tvec2<valType> const & x
	)
    {
        return detail::tvec2<valType>(
            fract(x.x),
            fract(x.y));
    }

    template <typename valType>
    inline detail::tvec3<valType> fract
	(
		detail::tvec3<valType> const & x
	)
    {
        return detail::tvec3<valType>(
            fract(x.x),
            fract(x.y),
            fract(x.z));
    }

    template <typename valType>
    inline detail::tvec4<valType> fract
	(
		detail::tvec4<valType> const & x
	)
    {
        return detail::tvec4<valType>(
            fract(x.x),
            fract(x.y),
            fract(x.z),
            fract(x.w));
    }

    // mod
    template <typename genType>
    inline genType mod
	(
		genType const & x, 
		genType const & y
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'mod' only accept floating-point inputs");

        return x - y * floor(x / y);
    }

    template <typename T>
    inline detail::tvec2<T> mod
	(
		detail::tvec2<T> const & x, 
		typename detail::tvec2<T>::value_type const & y
	)
    {
        return detail::tvec2<T>(
            mod(x.x, y),
            mod(x.y, y));
    }

    template <typename T>
    inline detail::tvec3<T> mod
	(
		detail::tvec3<T> const & x, 
		typename detail::tvec3<T>::value_type const & y
	)
    {
        return detail::tvec3<T>(
            mod(x.x, y),
            mod(x.y, y),
            mod(x.z, y));
    }

    template <typename T>
    inline detail::tvec4<T> mod
	(
		detail::tvec4<T> const & x, 
		typename detail::tvec4<T>::value_type const & y
	)
    {
        return detail::tvec4<T>(
            mod(x.x, y),
            mod(x.y, y),
            mod(x.z, y),
            mod(x.w, y));
    }

    template <typename T>
    inline detail::tvec2<T> mod
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y
	)
    {
        return detail::tvec2<T>(
            mod(x.x, y.x),
            mod(x.y, y.y));
    }

    template <typename T>
    inline detail::tvec3<T> mod
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y
	)
    {
        return detail::tvec3<T>(
            mod(x.x, y.x),
            mod(x.y, y.y),
            mod(x.z, y.z));
    }

    template <typename T>
    inline detail::tvec4<T> mod
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y
	)
    {
        return detail::tvec4<T>(
            mod(x.x, y.x),
            mod(x.y, y.y),
            mod(x.z, y.z),
            mod(x.w, y.w));
    }

    // modf
    template <typename genType>
    inline genType modf
	(
		genType const & x, 
		genType & i
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'modf' only accept floating-point inputs");

		i = glm::floor(x);

        return x - i;
    }

    template <typename valType>
    inline detail::tvec2<valType> modf
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y
	)
    {
        return detail::tvec2<valType>(
            modf(x.x, y.x),
            modf(x.y, y.y));
    }

    template <typename valType>
    inline detail::tvec3<valType> modf
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y
	)
    {
        return detail::tvec3<valType>(
            modf(x.x, y.x),
            modf(x.y, y.y),
            modf(x.z, y.z));
    }

    template <typename valType>
    inline detail::tvec4<valType> modf
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y
	)
    {
        return detail::tvec4<valType>(
            modf(x.x, y.x),
            modf(x.y, y.y),
            modf(x.z, y.z),
            modf(x.w, y.w));
    }

	//// Only valid if (INT_MIN <= x-y <= INT_MAX)
	//// min(x,y)
	//r = y + ((x - y) & ((x - y) >> (sizeof(int) *
	//CHAR_BIT – 1)));
	//// max(x,y)
	//r = x - ((x - y) & ((x - y) >> (sizeof(int) *
	//CHAR_BIT - 1)));

    // min
    template <typename genType>
    inline genType min
	(
		genType const & x, 
		genType const & y
	)
    {
		GLM_STATIC_ASSERT(
			detail::type<genType>::is_float || 
			detail::type<genType>::is_int ||
			detail::type<genType>::is_uint, "'min' only accept numbers");

        return x < y ? x : y;
    }

    template <typename T>
    inline detail::tvec2<T> min
	(
		detail::tvec2<T> const & x, 
		typename detail::tvec2<T>::value_type const & y
	)
    {
        return detail::tvec2<T>(
            min(x.x, y),
            min(x.y, y));
    }

    template <typename T>
    inline detail::tvec3<T> min
	(
		detail::tvec3<T> const & x, 
		typename detail::tvec3<T>::value_type const & y
	)
    {
        return detail::tvec3<T>(
            min(x.x, y),
            min(x.y, y),
            min(x.z, y));
    }

    template <typename T>
    inline detail::tvec4<T> min
	(
		detail::tvec4<T> const & x, 
		typename detail::tvec4<T>::value_type const & y
	)
    {
        return detail::tvec4<T>(
            min(x.x, y),
            min(x.y, y),
            min(x.z, y),
            min(x.w, y));
    }

    template <typename T>
    inline detail::tvec2<T> min
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y
	)
    {
        return detail::tvec2<T>(
            min(x.x, y.x),
            min(x.y, y.y));
    }

    template <typename T>
    inline detail::tvec3<T> min
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y
	)
    {
        return detail::tvec3<T>(
            min(x.x, y.x),
            min(x.y, y.y),
            min(x.z, y.z));
    }

    template <typename T>
    inline detail::tvec4<T> min
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y
	)
    {
        return detail::tvec4<T>(
            min(x.x, y.x),
            min(x.y, y.y),
            min(x.z, y.z),
            min(x.w, y.w));
    }

    // max
    template <typename genType>
    inline genType max
	(
		genType const & x, 
		genType const & y
	)
    {
		GLM_STATIC_ASSERT(
			detail::type<genType>::is_float || 
			detail::type<genType>::is_int ||
			detail::type<genType>::is_uint, "'max' only accept numbers");

		return x > y ? x : y;
    }

    template <typename T>
    inline detail::tvec2<T> max
	(
		detail::tvec2<T> const & x, 
		typename detail::tvec2<T>::value_type y
	)
    {
        return detail::tvec2<T>(
            max(x.x, y),
            max(x.y, y));
    }

    template <typename T>
    inline detail::tvec3<T> max
	(
		detail::tvec3<T> const & x, 
		typename detail::tvec3<T>::value_type y
	)
    {
        return detail::tvec3<T>(
            max(x.x, y),
            max(x.y, y),
            max(x.z, y));
    }

    template <typename T>
    inline detail::tvec4<T> max
	(
		detail::tvec4<T> const & x, 
		typename detail::tvec4<T>::value_type y
	)
    {
        return detail::tvec4<T>(
            max(x.x, y),
            max(x.y, y),
            max(x.z, y),
            max(x.w, y));
    }

    template <typename T>
    inline detail::tvec2<T> max
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y
	)
    {
        return detail::tvec2<T>(
            max(x.x, y.x),
            max(x.y, y.y));
    }

    template <typename T>
    inline detail::tvec3<T> max
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y
	)
    {
        return detail::tvec3<T>(
            max(x.x, y.x),
            max(x.y, y.y),
            max(x.z, y.z));
    }

    template <typename T>
    inline detail::tvec4<T> max
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y)
    {
        return detail::tvec4<T>(
            max(x.x, y.x),
            max(x.y, y.y),
            max(x.z, y.z),
            max(x.w, y.w));
    }

    // clamp
    template <typename valType>
    inline valType clamp
	(
		valType const & x, 
		valType const & minVal, 
		valType const & maxVal
	)
    {
		GLM_STATIC_ASSERT(
			detail::type<valType>::is_float || 
			detail::type<valType>::is_int ||
			detail::type<valType>::is_uint, "'clamp' only accept numbers");
		
		// Old implementation, less predictable branching
		//if(x >= maxVal) return maxVal; 
        //if(x <= minVal) return minVal;
	    //return x;
		return glm::max(glm::min(x, maxVal), minVal);
    }

    template <typename T>
    inline detail::tvec2<T> clamp
	(
		detail::tvec2<T> const & x, 
		typename detail::tvec2<T>::value_type const & minVal, 
		typename detail::tvec2<T>::value_type const & maxVal
	)
    {
        return detail::tvec2<T>(
            clamp(x.x, minVal, maxVal),
            clamp(x.y, minVal, maxVal));
    }

    template <typename T>
    inline detail::tvec3<T> clamp
	(
		detail::tvec3<T> const & x, 
		typename detail::tvec3<T>::value_type const & minVal, 
		typename detail::tvec3<T>::value_type const & maxVal
	)
    {
        return detail::tvec3<T>(
            clamp(x.x, minVal, maxVal),
            clamp(x.y, minVal, maxVal),
            clamp(x.z, minVal, maxVal));
    }

    template <typename T>
    inline detail::tvec4<T> clamp
	(
		detail::tvec4<T> const & x, 
		typename detail::tvec4<T>::value_type const & minVal, 
		typename detail::tvec4<T>::value_type const & maxVal
	)
    {
        return detail::tvec4<T>(
            clamp(x.x, minVal, maxVal),
            clamp(x.y, minVal, maxVal),
            clamp(x.z, minVal, maxVal),
            clamp(x.w, minVal, maxVal));
    }

    template <typename T>
    inline detail::tvec2<T> clamp
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & minVal, 
		detail::tvec2<T> const & maxVal
	)
    {
        return detail::tvec2<T>(
            clamp(x.x, minVal.x, maxVal.x),
            clamp(x.y, minVal.y, maxVal.y));
    }

    template <typename T>
    inline detail::tvec3<T> clamp
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & minVal, 
		detail::tvec3<T> const & maxVal
	)
    {
        return detail::tvec3<T>(
            clamp(x.x, minVal.x, maxVal.x),
            clamp(x.y, minVal.y, maxVal.y),
            clamp(x.z, minVal.z, maxVal.z));
    }

    template <typename T>
    inline detail::tvec4<T> clamp
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & minVal, 
		detail::tvec4<T> const & maxVal
	)
    {
        return detail::tvec4<T>(
            clamp(x.x, minVal.x, maxVal.x),
            clamp(x.y, minVal.y, maxVal.y),
            clamp(x.z, minVal.z, maxVal.z),
            clamp(x.w, minVal.w, maxVal.w));
    }

	// mix
	template <typename genTypeT, typename genTypeU>
	inline genTypeT mix
	(
		genTypeT const & x, 
		genTypeT const & y, 
		genTypeU const & a
	)
	{
		// It could be a vector too
		//GLM_STATIC_ASSERT(
		//	detail::type<genTypeT>::is_float && 
		//	detail::type<genTypeU>::is_float);

		//return x + a * (y - x);
		return genTypeT(genTypeU(x) + a * genTypeU(y - x));
	}

	template <typename valTypeA, typename valTypeB>
	inline detail::tvec2<valTypeA> mix
	(
		detail::tvec2<valTypeA> const & x, 
		detail::tvec2<valTypeA> const & y, 
		valTypeB const & a
	)
	{
		return detail::tvec2<valTypeA>(
			detail::tvec2<valTypeB>(x) + a * detail::tvec2<valTypeB>(y - x));
	}

	template <typename valTypeA, typename valTypeB>
	inline detail::tvec3<valTypeA> mix
	(
		detail::tvec3<valTypeA> const & x, 
		detail::tvec3<valTypeA> const & y, 
		valTypeB const & a
	)
	{
		return detail::tvec3<valTypeA>(
			detail::tvec3<valTypeB>(x) + a * detail::tvec3<valTypeB>(y - x));
	}

	template <typename valTypeA, typename valTypeB>
	inline detail::tvec4<valTypeA> mix
	(
		detail::tvec4<valTypeA> const & x, 
		detail::tvec4<valTypeA> const & y, 
		valTypeB const & a
	)
	{
		return detail::tvec4<valTypeA>(
			detail::tvec4<valTypeB>(x) + a * detail::tvec4<valTypeB>(y - x));
	}

	template <typename valTypeA, typename valTypeB>
	inline detail::tvec2<valTypeA> mix
	(
		detail::tvec2<valTypeA> const & x, 
		detail::tvec2<valTypeA> const & y, 
		detail::tvec2<valTypeB> const & a
	)
	{
		return detail::tvec2<valTypeA>(
			detail::tvec2<valTypeB>(x) + a * detail::tvec2<valTypeB>(y - x));
	}

	template <typename valTypeA, typename valTypeB>
	inline detail::tvec3<valTypeA> mix
	(
		detail::tvec3<valTypeA> const & x, 
		detail::tvec3<valTypeA> const & y, 
		detail::tvec3<valTypeB> const & a
	)
	{
		return detail::tvec3<valTypeA>(
			detail::tvec3<valTypeB>(x) + a * detail::tvec3<valTypeB>(y - x));
	}

	template <typename valTypeA, typename valTypeB>
	inline detail::tvec4<valTypeA> mix
	(
		detail::tvec4<valTypeA> const & x, 
		detail::tvec4<valTypeA> const & y, 
		detail::tvec4<valTypeB> const & a
	)
	{
		return detail::tvec4<valTypeA>(
			detail::tvec4<valTypeB>(x) + a * detail::tvec4<valTypeB>(y - x));
	}

	//template <typename genTypeT>
	//inline genTypeT mix
	//(
	//	genTypeT const & x, 
	//	genTypeT const & y, 
	//	float const & a
	//)
	//{
	//	// It could be a vector too
	//	//GLM_STATIC_ASSERT(
	//	//	detail::type<genTypeT>::is_float && 
	//	//	detail::type<genTypeU>::is_float);

	//	return x + a * (y - x);
	//}

	template <typename genType>
	inline genType mix
	(
		genType const & x, 
		genType const & y, 
		bool a
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'mix' only accept floating-point inputs");

		return a ? x : y;
	}

	template <typename T>
	inline detail::tvec2<T> mix
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y, 
		typename detail::tvec2<T>::bool_type a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		detail::tvec2<T> result;
		for
		(
			typename detail::tvec2<T>::size_type i = 0; 
			i < detail::tvec2<T>::value_size(); 
			++i
		)
		{
			result[i] = a[i] ? x[i] : y[i];
		}
		return result;
	}

	template <typename T>
	inline detail::tvec3<T> mix
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		typename detail::tvec3<T>::bool_type a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		detail::tvec3<T> result;
		for
		(
			typename detail::tvec3<T>::size_type i = 0; 
			i < detail::tvec3<T>::value_size(); 
			++i
		)
		{
			result[i] = a[i] ? x[i] : y[i];
		}
		return result;
	}

	template <typename T>
	inline detail::tvec4<T> mix
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y, 
		typename detail::tvec4<T>::bool_type a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		detail::tvec4<T> result;
		for
		(
			typename detail::tvec4<T>::size_type i = 0; 
			i < detail::tvec4<T>::value_size(); 
			++i
		)
		{
			result[i] = a[i] ? x[i] : y[i];
		}
		return result;
	}

	// step
    template <typename genType>
    inline genType step
	(
		genType const & edge, 
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'mix' only accept floating-point inputs");

        return x <= edge ? genType(0) : genType(1);
    }

    template <typename T>
    inline detail::tvec2<T> step
	(
		typename detail::tvec2<T>::value_type const & edge, 
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            x.x <= edge ? T(0) : T(1),
            x.y <= edge ? T(0) : T(1));
    }

    template <typename T>
    inline detail::tvec3<T> step
	(
		typename detail::tvec3<T>::value_type const & edge, 
		detail::tvec3<T> const & x
	)
    {
		return detail::tvec3<T>(
			x.x <= edge ? T(0) : T(1),
			x.y <= edge ? T(0) : T(1),
			x.z <= edge ? T(0) : T(1));
    }

    template <typename T>
    inline detail::tvec4<T> step
	(
		typename detail::tvec4<T>::value_type const & edge, 
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            x.x <= edge ? T(0) : T(1),
            x.y <= edge ? T(0) : T(1),
            x.z <= edge ? T(0) : T(1),
            x.w <= edge ? T(0) : T(1));
    }

    template <typename T>
    inline detail::tvec2<T> step
	(
		detail::tvec2<T> const & edge, 
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            x.x <= edge.x ? T(0) : T(1),
            x.y <= edge.y ? T(0) : T(1));
    }

    template <typename T>
    inline detail::tvec3<T> step
	(
		detail::tvec3<T> const & edge, 
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            x.x <= edge.x ? T(0) : T(1),
            x.y <= edge.y ? T(0) : T(1),
            x.z <= edge.z ? T(0) : T(1));
    }

    template <typename T>
    inline detail::tvec4<T> step
	(
		detail::tvec4<T> const & edge, 
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            x.x <= edge.x ? T(0) : T(1),
            x.y <= edge.y ? T(0) : T(1),
            x.z <= edge.z ? T(0) : T(1),
            x.w <= edge.w ? T(0) : T(1));
    }

    // smoothstep
    template <typename genType>
    inline genType smoothstep
	(
		genType const & edge0, 
		genType const & edge1, 
		genType const & x
	)
    {
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'mix' only accept floating-point inputs");

        genType tmp = clamp((x - edge0) / (edge1 - edge0), genType(0), genType(1));
        return tmp * tmp * (genType(3) - genType(2) * tmp);
    }

    template <typename T>
    inline detail::tvec2<T> smoothstep
	(
		typename detail::tvec2<T>::value_type const & edge0, 
		typename detail::tvec2<T>::value_type const & edge1, 
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            smoothstep(edge0, edge1, x.x),
            smoothstep(edge0, edge1, x.y));
    }

    template <typename T>
    inline detail::tvec3<T> smoothstep
	(
		typename detail::tvec3<T>::value_type const & edge0, 
		typename detail::tvec3<T>::value_type const & edge1, 
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            smoothstep(edge0, edge1, x.x),
            smoothstep(edge0, edge1, x.y),
            smoothstep(edge0, edge1, x.z));
    }

    template <typename T>
    inline detail::tvec4<T> smoothstep
	(
		typename detail::tvec4<T>::value_type const & edge0, 
		typename detail::tvec4<T>::value_type const & edge1, 
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            smoothstep(edge0, edge1, x.x),
            smoothstep(edge0, edge1, x.y),
            smoothstep(edge0, edge1, x.z),
            smoothstep(edge0, edge1, x.w));
    }

    template <typename T>
    inline detail::tvec2<T> smoothstep
	(
		detail::tvec2<T> const & edge0, 
		detail::tvec2<T> const & edge1, 
		detail::tvec2<T> const & x
	)
    {
        return detail::tvec2<T>(
            smoothstep(edge0.x, edge1.x, x.x),
            smoothstep(edge0.y, edge1.y, x.y));
    }

    template <typename T>
    inline detail::tvec3<T> smoothstep
	(
		detail::tvec3<T> const & edge0, 
		detail::tvec3<T> const & edge1, 
		detail::tvec3<T> const & x
	)
    {
        return detail::tvec3<T>(
            smoothstep(edge0.x, edge1.x, x.x),
            smoothstep(edge0.y, edge1.y, x.y),
            smoothstep(edge0.z, edge1.z, x.z));
    }

    template <typename T>
    inline detail::tvec4<T> smoothstep
	(
		detail::tvec4<T> const & edge0, 
		detail::tvec4<T> const & edge1, 
		detail::tvec4<T> const & x
	)
    {
        return detail::tvec4<T>(
            smoothstep(edge0.x, edge1.x, x.x),
            smoothstep(edge0.y, edge1.y, x.y),
            smoothstep(edge0.z, edge1.z, x.z),
            smoothstep(edge0.w, edge1.w, x.w));
    }

	template <typename genType> 
	inline typename genType::bool_type isnan
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'mix' only accept floating-point inputs");

#if(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_VC)
		return typename genType::bool_type(_isnan(x));
#else
		return typename genType::bool_type(std::isnan(x));
#endif
	}

    template <typename T>
    inline typename detail::tvec2<T>::bool_type isnan
	(
		detail::tvec2<T> const & x
	)
    {
        return typename detail::tvec2<T>::bool_type(
            isnan(x.x),
            isnan(x.y));
    }

    template <typename T>
    inline typename detail::tvec3<T>::bool_type isnan
	(
		detail::tvec3<T> const & x
	)
    {
        return typename detail::tvec3<T>::bool_type(
            isnan(x.x),
            isnan(x.y),
            isnan(x.z));
    }

    template <typename T>
    inline typename detail::tvec4<T>::bool_type isnan
	(
		detail::tvec4<T> const & x
	)
    {
        return typename detail::tvec4<T>::bool_type(
            isnan(x.x),
            isnan(x.y),
            isnan(x.z),
            isnan(x.w));
    }

	template <typename genType> 
	inline typename genType::bool_type isinf
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'isinf' only accept floating-point inputs");

#if(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_VC)
		return typename genType::bool_type(_fpclass(x) == _FPCLASS_NINF || _fpclass(x) == _FPCLASS_PINF);
#else
		return typename genType::bool_type(std::isinf(x));
#endif
	}

    template <typename T>
    inline typename detail::tvec2<T>::bool_type isinf
	(
		detail::tvec2<T> const & x
	)
    {
        return typename detail::tvec2<T>::bool_type(
            isnan(x.x),
            isnan(x.y));
    }

    template <typename T>
    inline typename detail::tvec3<T>::bool_type isinf
	(
		detail::tvec3<T> const & x
	)
    {
        return typename detail::tvec3<T>::bool_type(
            isnan(x.x),
            isnan(x.y),
            isnan(x.z));
    }

    template <typename T>
    inline typename detail::tvec4<T>::bool_type isinf
	(
		detail::tvec4<T> const & x
	)
    {
        return typename detail::tvec4<T>::bool_type(
            isnan(x.x),
            isnan(x.y),
            isnan(x.z),
            isnan(x.w));
    }

	inline int floatBitsToInt(float const & value)
	{
		union
		{
			float f;
			int i;
		} fi;

		fi.f = value;
		return fi.i;
	}

    template <typename T>
    inline detail::tvec2<int> floatBitsToInt
	(
		detail::tvec2<T> const & value
	)
    {
        return detail::tvec2<T>(
            floatBitsToInt(value.x),
            floatBitsToInt(value.y));
    }

    template <typename T>
    inline detail::tvec3<int> floatBitsToInt
	(
		detail::tvec3<T> const & value
	)
    {
        return detail::tvec3<T>(
            floatBitsToInt(value.x),
            floatBitsToInt(value.y));
    }

    template <typename T>
    inline detail::tvec4<int> floatBitsToInt
	(
		detail::tvec4<T> const & value
	)
    {
        return detail::tvec4<T>(
            floatBitsToInt(value.x),
            floatBitsToInt(value.y));
    }

	inline uint floatBitsToUint(float const & value)
	{
		union
		{
			float f;
			uint u;
		} fu;

		fu.f = value;
		return fu.u;
	}

    template <typename T>
    inline detail::tvec2<uint> floatBitsToUint
	(
		detail::tvec2<T> const & value
	)
    {
        return detail::tvec2<T>(
            floatBitsToUint(value.x),
            floatBitsToUint(value.y));
    }

    template <typename T>
    inline detail::tvec3<uint> floatBitsToUint
	(
		detail::tvec3<T> const & value
	)
    {
        return detail::tvec3<T>(
            floatBitsToUint(value.x),
            floatBitsToUint(value.y));
    }

    template <typename T>
    inline detail::tvec4<uint> floatBitsToUint
	(
		detail::tvec4<T> const & value
	)
    {
        return detail::tvec4<T>(
            floatBitsToUint(value.x),
            floatBitsToUint(value.y));
    }

	inline float intBitsToFloat(int const & value)
	{
		union
		{
			float f;
			int i;
		} fi;

		fi.i = value;
		return fi.f;
	}

	inline float intBitsToFloat(uint const & value)
	{
		union
		{
			float f;
			uint u;
		} fu;

		fu.u = value;
		return fu.f;
	}

    template <typename T>
    inline detail::tvec2<float> intBitsToFloat
	(
		detail::tvec2<T> const & value
	)
    {
        return detail::tvec2<T>(
            intBitsToFloat(value.x),
            intBitsToFloat(value.y));
    }

    template <typename T>
    inline detail::tvec3<float> intBitsToFloat
	(
		detail::tvec3<T> const & value
	)
    {
        return detail::tvec3<T>(
            intBitsToFloat(value.x),
            intBitsToFloat(value.y));
    }

    template <typename T>
    inline detail::tvec4<float> intBitsToFloat
	(
		detail::tvec4<T> const & value
	)
    {
        return detail::tvec4<T>(
            intBitsToFloat(value.x),
            intBitsToFloat(value.y));
    }

	template <typename genType>
	inline genType fma
	(
		genType const & a, 
		genType const & b, 
		genType const & c
	)
	{
		return a * b + c;
	}

	template <typename genType>
	genType frexp
	(
		genType const & x, 
		int & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	detail::tvec2<T> frexp
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<int> & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	detail::tvec3<T> frexp
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<int> & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	detail::tvec4<T> frexp
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<int> & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename genType>
	genType ldexp
	(
		genType const & x, 
		int const & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	detail::tvec2<T> ldexp
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<int> const & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	detail::tvec3<T> ldexp
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<int> const & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	detail::tvec4<T> ldexp
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<int> const & exp
	)
	{
		return std::frexp(x, exp);
	}

	}//namespace common
	}//namespace function
	}//namespace core
}//namespace glm
