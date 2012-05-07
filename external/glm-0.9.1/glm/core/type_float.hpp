///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-22
// Updated : 2010-02-08
// Licence : This source is under MIT License
// File    : glm/core/type_float.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_float
#define glm_core_type_float

#include "type_half.hpp"
#include "setup.hpp"

namespace glm
{
	namespace detail
	{
		GLM_DETAIL_IS_FLOAT(detail::thalf);
		GLM_DETAIL_IS_FLOAT(float);
		GLM_DETAIL_IS_FLOAT(double);
		GLM_DETAIL_IS_FLOAT(long double);
	}
	//namespace detail

	namespace core{
	namespace type{

	namespace precision
	{
#ifdef GLM_USE_HALF_SCALAR
		typedef detail::thalf		lowp_float_t;
#else//GLM_USE_HALF_SCALAR
		typedef float				lowp_float_t;
#endif//GLM_USE_HALF_SCALAR
		typedef float				mediump_float_t;
		typedef double				highp_float_t;

		//! Low precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification
		//! \ingroup core_precision
		typedef lowp_float_t		lowp_float;
		//! Medium precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification
		//! \ingroup core_precision
		typedef mediump_float_t		mediump_float;
		//! High precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification
		//! \ingroup core_precision
		typedef highp_float_t		highp_float;
	}
	//namespace precision

#ifndef GLM_PRECISION 
	typedef precision::mediump_float		float_t;
#elif(GLM_PRECISION & GLM_PRECISION_HIGHP_FLOAT)
	typedef precision::highp_float			float_t;
#elif(GLM_PRECISION & GLM_PRECISION_MEDIUMP_FLOAT)
	typedef precision::mediump_float		float_t;
#elif(GLM_PRECISION & GLM_PRECISION_LOWP_FLOAT)
	typedef precision::lowp_float			float_t;
#else
	#	pragma message("GLM message: Precisson undefined for float numbers.");
	typedef precision::mediump_float		float_t;
#endif//GLM_PRECISION

	}//namespace type
	}//namespace core
}//namespace glm

#endif//glm_core_type_float
