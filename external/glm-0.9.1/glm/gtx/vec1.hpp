///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-02-08
// Updated : 2010-02-08
// Licence : This source is under MIT License
// File    : glm/gtx/vec1.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_vec1
#define glm_gtx_vec1

// Dependency:
#include "../glm.hpp"
#include "../core/type_vec1.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_vec1 extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_vector1();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_vector1 extension: 1 component vector.
	namespace vector1
	{
		namespace precision
		{
			//! 1 component vector of high precision floating-point numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::highp_vec1_t			highp_vec1;
			//! 1 component vector of medium precision floating-point numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::mediump_vec1_t			mediump_vec1;
			//! 1 component vector of low precision floating-point numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::lowp_vec1_t				lowp_vec1;

			//! 1 component vector of high precision signed integer numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::highp_ivec1_t			highp_ivec1;
			//! 1 component vector of medium precision signed integer numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::mediump_ivec1_t			mediump_ivec1;
			//! 1 component vector of low precision signed integer numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::lowp_ivec1_t			lowp_ivec1;

			//! 1 component vector of high precision unsigned integer numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::highp_uvec1_t			highp_uvec1;
			//! 1 component vector of medium precision unsigned integer numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::mediump_uvec1_t			mediump_uvec1;
			//! 1 component vector of low precision unsigned integer numbers. 
			//! There is no guarantee on the actual precision.
			//! From GLM_GTX_vec1 extension.
			typedef detail::lowp_uvec1_t			lowp_uvec1;
		}//namespace precision

		//////////////////////////
		// vec1 definition

		//! 1 component vector of boolean.
		//! From GLM_GTX_vec1 extension.
		typedef detail::tvec1<bool>	bvec1;

#if(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_HIGHP_FLOAT)
		typedef precision::highp_vec1			vec1;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_MEDIUMP_FLOAT)
		typedef precision::mediump_vec1			vec1;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_LOWP_FLOAT)
		typedef precision::lowp_vec1			vec1;
#else
		//! 1 component vector of floating-point numbers.
		//! From GLM_GTX_vec1 extension.
		typedef precision::mediump_vec1			vec1;
#endif//GLM_PRECISION

#if(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_HIGHP_INT)
		typedef precision::highp_ivec1			ivec1;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_MEDIUMP_INT)
		typedef precision::mediump_ivec1		ivec1;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_LOWP_INT)
		typedef precision::lowp_ivec1			ivec1;
#else
		//! 1 component vector of signed integer numbers. 
		//! From GLM_GTX_vec1 extension.
		typedef precision::mediump_ivec1		ivec1;
#endif//GLM_PRECISION

#if(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_HIGHP_UINT)
		typedef precision::highp_uvec1			uvec1;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_MEDIUMP_UINT)
		typedef precision::mediump_uvec1		uvec1;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_LOWP_UINT)
		typedef precision::lowp_uvec1			uvec1;
#else
		//! 1 component vector of unsigned integer numbers. 
		//! From GLM_GTX_vec1 extension.
		typedef precision::mediump_uvec1		uvec1;
#endif//GLM_PRECISION

	}//namespace vec1
	}//namespace gtx
}//namespace glm

#include "vec1.inl"

namespace glm{using namespace gtx::vector1;}

#endif//glm_gtx_vec1

