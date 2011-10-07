///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-08
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/func_exponential.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_exponential
#define glm_core_func_exponential

namespace glm
{
	namespace test{
		void main_core_func_exponential();
	}//namespace test

	namespace core{
	namespace function{
	//! Define all exponential functions from Section 8.2 of GLSL 1.30.8 specification. Included in glm namespace.
	namespace exponential{

	/// \addtogroup core_funcs
	///@{

	//! Returns x raised to the y power. 
	//! (From GLSL 1.30.08 specification, section 8.2)
	template <typename genType> 
	genType pow(genType const & x, genType const & y);

	//! Returns the natural exponentiation of x, i.e., e^x.
	//! (From GLSL 1.30.08 specification, section 8.2)
	template <typename genType> 
	genType exp(genType const & x);

	//! Returns the natural logarithm of x, i.e., 
	//! returns the value y which satisfies the equation x = e^y. 
	//! Results are undefined if x <= 0.
	//! (From GLSL 1.30.08 specification, section 8.2)
	template <typename genType> 
	genType log(genType const & x);

	//! Returns 2 raised to the x power.
	//! (From GLSL 1.30.08 specification, section 8.2)
	template <typename genType> 
	genType exp2(genType const & x);

	//! Returns the base 2 log of x, i.e., returns the value y, 
	//! which satisfies the equation x = 2 ^ y.
	//! (From GLSL 1.30.08 specification, section 8.2)
	template <typename genType> 
	genType log2(genType const & x);

	//! Returns the positive square root of x.
	//! (From GLSL 1.30.08 specification, section 8.2)
	template <typename genType> 
	genType sqrt(genType const & x);
    
	//! Returns the reciprocal of the positive square root of x.
	//! (From GLSL 1.30.08 specification, section 8.2)
	template <typename genType> 
	genType inversesqrt(genType const & x);

	///@}

	}//namespace exponential
	}//namespace function
	}//namespace core

	using namespace core::function::exponential;
}//namespace glm

#include "func_exponential.inl"

#endif//glm_core_func_exponential
