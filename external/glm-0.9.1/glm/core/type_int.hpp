///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-22
// Updated : 2008-09-17
// Licence : This source is under MIT License
// File    : glm/core/type_int.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_int
#define glm_core_type_int

#include "setup.hpp"
#include "_detail.hpp"

namespace glm
{
	namespace detail
	{
		typedef signed short			lowp_int_t;
		typedef signed int				mediump_int_t;
		typedef sint64					highp_int_t;

		typedef unsigned short			lowp_uint_t;
		typedef unsigned int			mediump_uint_t;
		typedef uint64					highp_uint_t;

		GLM_DETAIL_IS_INT(signed char);
		GLM_DETAIL_IS_INT(signed short);
		GLM_DETAIL_IS_INT(signed int);
		GLM_DETAIL_IS_INT(signed long);
		GLM_DETAIL_IS_INT(highp_int_t);

		GLM_DETAIL_IS_UINT(unsigned char);
		GLM_DETAIL_IS_UINT(unsigned short);
		GLM_DETAIL_IS_UINT(unsigned int);
		GLM_DETAIL_IS_UINT(unsigned long);
		GLM_DETAIL_IS_UINT(highp_uint_t);
	}
	//namespace detail

	namespace core{
	namespace type{

	///namespace for precision stuff.
	namespace precision
	{
		//! Low precision signed integer. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification.
		//! \ingroup core_precision
		typedef detail::lowp_int_t				lowp_int;
		//! Medium precision signed integer. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification.
		//! \ingroup core_precision
		typedef detail::mediump_int_t			mediump_int;
		//! High precision signed integer.
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification.
		//! \ingroup core_precision
		typedef detail::highp_int_t				highp_int;

		//! Low precision unsigned integer. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification.
		//! \ingroup core_precision
		typedef detail::lowp_uint_t				lowp_uint;
		//! Medium precision unsigned integer. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification.
		//! \ingroup core_precision
		typedef detail::mediump_uint_t			mediump_uint;
		//! High precision unsigned integer. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification.
		//! \ingroup core_precision
		typedef detail::highp_uint_t			highp_uint;
	}
	//namespace precision

#ifndef GLM_PRECISION 
	typedef precision::mediump_int				int_t;
#elif(GLM_PRECISION & GLM_PRECISION_HIGHP_INT)
	typedef precision::highp_int				int_t;
#elif(GLM_PRECISION & GLM_PRECISION_MEDIUMP_INT)
	typedef precision::mediump_int				int_t;
#elif(GLM_PRECISION & GLM_PRECISION_LOWP_INT)
	typedef precision::lowp_int					int_t;
#else
	typedef mediump_int							int_t;
#	pragma message("GLM message: Precisson undefined for signed integer number.");
#endif//GLM_PRECISION

#ifndef GLM_PRECISION 
	typedef precision::mediump_uint				uint_t;
#elif(GLM_PRECISION & GLM_PRECISION_HIGHP_UINT)
	typedef precision::highp_uint				uint_t;
#elif(GLM_PRECISION & GLM_PRECISION_MEDIUMP_UINT)
	typedef precision::mediump_uint				uint_t;
#elif(GLM_PRECISION & GLM_PRECISION_LOWP_UINT)
	typedef precision::lowp_uint				uint_t;
#else
	typedef precision::mediump_uint				uint_t;
#	pragma message("GLM message: Precisson undefined for unsigned integer number.");
#endif//GLM_PRECISION

	//! Unsigned integer. 
	//! From GLSL 1.30.8 specification section 4.1.3 Integers.
	typedef uint_t								uint;

	}//namespace type
	}//namespace core
}//namespace glm

#endif//glm_core_type_int
