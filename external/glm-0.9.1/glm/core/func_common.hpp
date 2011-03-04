///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-03-08
// Updated : 2010-01-26
// Licence : This source is under MIT License
// File    : glm/core/func_common.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_common
#define glm_core_func_common

#include "_fixes.hpp"

namespace glm
{
	namespace test{
		void main_core_func_common();
	}//namespace test

	namespace core{
	namespace function{
	//! Define common functions from Section 8.3 of GLSL 1.30.8 specification. Included in glm namespace.
	namespace common{

	/// \addtogroup core_funcs
	///@{

	//! Returns x if x >= 0; otherwise, it returns -x. 
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genFIType> 
	genFIType abs(genFIType const & x);

	//! Returns 1.0 if x > 0, 0.0 if x == 0, or -1.0 if x < 0. 
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genFIType> 
	genFIType sign(genFIType const & x);

    //! Returns a value equal to the nearest integer that is less then or equal to x. 
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType floor(genType const & x);

	//! Returns a value equal to the nearest integer to x 
	//! whose absolute value is not larger than the absolute value of x. 
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType trunc(genType const & x);

	//! Returns a value equal to the nearest integer to x. 
	//! The fraction 0.5 will round in a direction chosen by the 
	//! implementation, presumably the direction that is fastest. 
	//! This includes the possibility that round(x) returns the 
	//! same value as roundEven(x) for all values of x. 
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType round(genType const & x);

	//! Returns a value equal to the nearest integer to x.
	//! A fractional part of 0.5 will round toward the nearest even
	//! integer. (Both 3.5 and 4.5 for x will return 4.0.) 
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType roundEven(genType const & x);

	//! Returns a value equal to the nearest integer 
	//! that is greater than or equal to x. 
	//! (From GLSL 1.30.08 specification, section 8.3)
    template <typename genType> 
	genType ceil(genType const & x);

	//! Return x - floor(x).
	//! (From GLSL 1.30.08 specification, section 8.3)
    template <typename genType> 
	genType fract(genType const & x);

	//! Modulus. Returns x - y * floor(x / y) 
	//! for each component in x using the floating point value y.
	//! (From GLSL 1.30.08 specification, section 8.3)
    template <typename genType> 
	genType mod(
		genType const & x, 
		genType const & y);

	//! Modulus. Returns x - y * floor(x / y) 
	//! for each component in x using the floating point value y.
	//! (From GLSL 1.30.08 specification, section 8.3)
    template <typename genType> 
	genType mod(
		genType const & x, 
		typename genType::value_type const & y);

	//! Returns the fractional part of x and sets i to the integer
	//! part (as a whole number floating point value). Both the
	//! return value and the output parameter will have the same
	//! sign as x.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType modf(
		genType const & x, 
		genType & i);

    //! Returns y if y < x; otherwise, it returns x.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType min(
		genType const & x, 
		genType const & y);

	template <typename genType> 
	genType min(
		genType const & x, 
		typename genType::value_type const & y);

    //! Returns y if x < y; otherwise, it returns x.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType max(
		genType const & x, 
		genType const & y);

	template <typename genType> 
	genType max(
		genType const & x, 
		typename genType::value_type const & y);

    //! Returns min(max(x, minVal), maxVal) for each component in x 
	//! using the floating-point values minVal and maxVal.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType clamp(
		genType const & x, 
		genType const & minVal, 
		genType const & maxVal); 

	template <typename genType> 
	genType clamp(
		genType const & x, 
		typename genType::value_type const & minVal, 
		typename genType::value_type const & maxVal); 

	//! \return If genTypeU is a floating scalar or vector: 
	//! Returns x * (1.0 - a) + y * a, i.e., the linear blend of 
	//! x and y using the floating-point value a. 
	//! The value for a is not restricted to the range [0, 1].
	//!
	//! \return If genTypeU is a boolean scalar or vector: 
	//! Selects which vector each returned component comes
	//! from. For a component of a that is false, the
	//! corresponding component of x is returned. For a
	//! component of a that is true, the corresponding
	//! component of y is returned. Components of x and y that
	//! are not selected are allowed to be invalid floating point
	//! values and will have no effect on the results. Thus, this
	//! provides different functionality than
	//! genType mix(genType x, genType y, genType(a))
	//! where a is a Boolean vector.
	//! 
	//! From GLSL 1.30.08 specification, section 8.3
	//! 
	//! \param[in]  x Floating point scalar or vector.
	//! \param[in]  y Floating point scalar or vector.
	//! \param[in]  a Floating point or boolean scalar or vector.
	//!
	// \todo Test when 'a' is a boolean.
	template <typename genTypeT, typename genTypeU> 
	genTypeT mix(genTypeT const & x, genTypeT const & y, genTypeU const & a);

	//! Returns 0.0 if x < edge, otherwise it returns 1.0.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType step(
		genType const & edge, 
		genType const & x);

	template <typename genType> 
	genType step(
		typename genType::value_type const & edge, 
		genType const & x);

	//! Returns 0.0 if x <= edge0 and 1.0 if x >= edge1 and
	//! performs smooth Hermite interpolation between 0 and 1
	//! when edge0 < x < edge1. This is useful in cases where
	//! you would want a threshold function with a smooth
	//! transition. This is equivalent to:
	//! genType t;
	//! t = clamp ((x – edge0) / (edge1 – edge0), 0, 1);
	//! return t * t * (3 – 2 * t);
	//! Results are undefined if edge0 >= edge1.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	genType smoothstep(
		genType const & edge0, 
		genType const & edge1, 
		genType const & x);

	template <typename genType> 
	genType smoothstep(
		typename genType::value_type const & edge0, 
		typename genType::value_type const & edge1, 
		genType const & x);

	//! Returns true if x holds a NaN (not a number)
	//! representation in the underlying implementation's set of
	//! floating point representations. Returns false otherwise,
	//! including for implementations with no NaN
	//! representations.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	typename genType::bool_type isnan(genType const & x);

	//! Returns true if x holds a positive infinity or negative
	//! infinity representation in the underlying implementation's
	//! set of floating point representations. Returns false
	//! otherwise, including for implementations with no infinity
	//! representations.
	//! (From GLSL 1.30.08 specification, section 8.3)
	template <typename genType> 
	typename genType::bool_type isinf(genType const & x);

	//! Returns a signed or unsigned integer value representing
	//! the encoding of a floating-point value. The floatingpoint
	//! value's bit-level representation is preserved.
	//! (From GLSL 4.00.08 specification, section 8.3)
	template <typename genType, typename genIType>
	genIType floatBitsToInt(genType const & value);

	//! Returns a signed or unsigned integer value representing
	//! the encoding of a floating-point value. The floatingpoint
	//! value's bit-level representation is preserved.
	//! (From GLSL 4.00.08 specification, section 8.3)
	template <typename genType, typename genUType>
	genUType floatBitsToInt(genType const & value);

	//! Returns a floating-point value corresponding to a signed
	//! or unsigned integer encoding of a floating-point value.
	//! If an inf or NaN is passed in, it will not signal, and the
	//! resulting floating point value is unspecified. Otherwise,
	//! the bit-level representation is preserved.
	//! (From GLSL 4.00.08 specification, section 8.3)
	template <typename genType, typename genIUType>
	genType intBitsToFloat(genIUType const & value);

	//! Computes and returns a * b + c.
	//! (From GLSL 4.00.08 specification, section 8.3)
	template <typename genType>
	genType fma(genType const & a, genType const & b, genType const & c);

	//! Splits x into a floating-point significand in the range
	//! [0.5, 1.0) and an integral exponent of two, such that:
	//! x = significand * exp(2, exponent)
	//! The significand is returned by the function and the
	//! exponent is returned in the parameter exp. For a
	//! floating-point value of zero, the significant and exponent
	//! are both zero. For a floating-point value that is an
	//! infinity or is not a number, the results are undefined.
	//! (From GLSL 4.00.08 specification, section 8.3)
	template <typename genType, typename genIType>
	genType frexp(genType const & x, genIType & exp);

	//! Builds a floating-point number from x and the
	//! corresponding integral exponent of two in exp, returning:
	//! significand * exp(2, exponent)
	//! If this product is too large to be represented in the
	//! floating-point type, the result is undefined.
	//! (From GLSL 4.00.08 specification, section 8.3)
	template <typename genType, typename genIType>
	genType ldexp(genType const & x, genIType const & exp);

	///@}

	}//namespace common
	}//namespace function
	}//namespace core

	using namespace core::function::common;
}//namespace glm

#include "func_common.inl"

#endif//glm_core_func_common
