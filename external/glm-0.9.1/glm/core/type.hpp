///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-01-08
// Updated : 2008-01-08
// Licence : This source is under MIT License
// File    : glm/core/type.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type
#define glm_core_type

#include "type_half.hpp"
#include "type_float.hpp"
#include "type_int.hpp"

#include "type_gentype.hpp"

#include "type_vec1.hpp"
#include "type_vec2.hpp"
#include "type_vec3.hpp"
#include "type_vec4.hpp"

#include "type_mat2x2.hpp"
#include "type_mat2x3.hpp"
#include "type_mat2x4.hpp"
#include "type_mat3x2.hpp"
#include "type_mat3x3.hpp"
#include "type_mat3x4.hpp"
#include "type_mat4x2.hpp"
#include "type_mat4x3.hpp"
#include "type_mat4x4.hpp"

namespace glm{
namespace core{
namespace type
{
	//////////////////////////
	// Float definition

#if(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_HIGHP_FLOAT)
	typedef precision::highp_vec2		vec2;
	typedef precision::highp_vec3		vec3;
	typedef precision::highp_vec4		vec4;
	typedef precision::highp_mat2x2		mat2x2;
	typedef precision::highp_mat2x3		mat2x3;
	typedef precision::highp_mat2x4		mat2x4;
	typedef precision::highp_mat3x2		mat3x2;
	typedef precision::highp_mat3x3		mat3x3;
	typedef precision::highp_mat3x4		mat3x4;
	typedef precision::highp_mat4x2		mat4x2;
	typedef precision::highp_mat4x3		mat4x3;
	typedef precision::highp_mat4x4		mat4x4;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_MEDIUMP_FLOAT)
	typedef precision::mediump_vec2		vec2;
	typedef precision::mediump_vec3		vec3;
	typedef precision::mediump_vec4		vec4;
	typedef precision::mediump_mat2x2	mat2x2;
	typedef precision::mediump_mat2x3	mat2x3;
	typedef precision::mediump_mat2x4	mat2x4;
	typedef precision::mediump_mat3x2	mat3x2;
	typedef precision::mediump_mat3x3	mat3x3;
	typedef precision::mediump_mat3x4	mat3x4;
	typedef precision::mediump_mat4x2	mat4x2;
	typedef precision::mediump_mat4x3	mat4x3;
	typedef precision::mediump_mat4x4	mat4x4;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_LOWP_FLOAT)
	typedef precision::lowp_vec2			vec2;
	typedef precision::lowp_vec3			vec3;
	typedef precision::lowp_vec4			vec4;
	typedef precision::lowp_mat2x2			mat2x2;
	typedef precision::lowp_mat2x3			mat2x3;
	typedef precision::lowp_mat2x4			mat2x4;
	typedef precision::lowp_mat3x2			mat3x2;
	typedef precision::lowp_mat3x3			mat3x3;
	typedef precision::lowp_mat3x4			mat3x4;
	typedef precision::lowp_mat4x2			mat4x2;
	typedef precision::lowp_mat4x3			mat4x3;
	typedef precision::lowp_mat4x4			mat4x4;
#else
	//! 2 components vector of floating-point numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_vec2		vec2;

	//! 3 components vector of floating-point numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_vec3		vec3;

	//! 4 components vector of floating-point numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_vec4		vec4;

	//! 2 columns of 2 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat2x2		mat2x2;

	//! 2 columns of 3 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat2x3		mat2x3;

	//! 2 columns of 4 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat2x4		mat2x4;

	//! 3 columns of 2 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat3x2		mat3x2;

	//! 3 columns of 3 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat3x3		mat3x3;

	//! 3 columns of 4 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat3x4		mat3x4;

	//! 4 columns of 2 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat4x2		mat4x2;

	//! 4 columns of 3 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat4x3		mat4x3;

	//! 4 columns of 4 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef precision::mediump_mat4x4		mat4x4;

#endif//GLM_PRECISION

	//! 2 columns of 2 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef mat2x2							mat2;

	//! 3 columns of 3 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef mat3x3							mat3;

	//! 4 columns of 4 components matrix of floating-point numbers. 
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices)
	//! \ingroup core_types
	typedef mat4x4							mat4;

	//////////////////////////
	// Signed integer definition

#if(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_HIGHP_INT)
	typedef precision::highp_ivec2			ivec2;
	typedef precision::highp_ivec3			ivec3;
	typedef precision::highp_ivec4			ivec4;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_MEDIUMP_INT)
	typedef precision::mediump_ivec2		ivec2;
	typedef precision::mediump_ivec3		ivec3;
	typedef precision::mediump_ivec4		ivec4;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_LOWP_INT)
	typedef precision::lowp_ivec2			ivec2;
	typedef precision::lowp_ivec3			ivec3;
	typedef precision::lowp_ivec4			ivec4;
#else
	//! 2 components vector of signed integer numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_ivec2		ivec2;

	//! 3 components vector of signed integer numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_ivec3		ivec3;

	//! 4 components vector of signed integer numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_ivec4		ivec4;
#endif//GLM_PRECISION

	//////////////////////////
	// Unsigned integer definition

#if(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_HIGHP_UINT)
	typedef precision::highp_uvec2			uvec2;
	typedef precision::highp_uvec3			uvec3;
	typedef precision::highp_uvec4			uvec4;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_MEDIUMP_UINT)
	typedef precision::mediump_uvec2		uvec2;
	typedef precision::mediump_uvec3		uvec3;
	typedef precision::mediump_uvec4		uvec4;
#elif(defined(GLM_PRECISION) && GLM_PRECISION & GLM_PRECISION_LOWP_UINT)
	typedef precision::lowp_uvec2			uvec2;
	typedef precision::lowp_uvec3			uvec3;
	typedef precision::lowp_uvec4			uvec4;
#else
	//! 2 components vector of unsigned integer numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_uvec2		uvec2;

	//! 3 components vector of unsigned integer numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_uvec3		uvec3;

	//! 4 components vector of unsigned integer numbers. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef precision::mediump_uvec4		uvec4;
#endif//GLM_PRECISION

	//////////////////////////
	// Boolean definition

	//! 2 components vector of boolean. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef detail::tvec2<bool>		bvec2;

	//! 3 components vector of boolean. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef detail::tvec3<bool>		bvec3;

	//! 4 components vector of boolean. 
	//! From GLSL 1.30.8 specification, section 4.1.5 Vectors.
	//! \ingroup core_types
	typedef detail::tvec4<bool>		bvec4;

	//////////////////////////
	// Double definition

	//! Vector of 2 double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tvec2<double>	dvec2;

	//! Vector of 3 double-precision floating-point numbers.
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tvec3<double>	dvec3;

	//! Vector of 4 double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tvec4<double>	dvec4;

	//! 2 * 2 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat2x2<double>	dmat2;

	//! 3 * 3 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat3x3<double>	dmat3;

	//! 4 * 4 matrix of double-precision floating-point numbers.
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat4x4<double>	dmat4;

	//! 2 * 2 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat2x2<double>	dmat2x2;

	//! 2 * 3 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat2x3<double>	dmat2x3;

	//! 2 * 4 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat2x4<double>	dmat2x4;

	//! 3 * 2 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat3x2<double>	dmat3x2;

	//! 3 * 3 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat3x3<double>	dmat3x3;

	//! 3 * 4 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat3x4<double>	dmat3x4;

	//! 4 * 2 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat4x2<double>	dmat4x2;

	//! 4 * 3 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat4x3<double>	dmat4x3;

	//! 4 * 4 matrix of double-precision floating-point numbers. 
	//! From GLSL 4.00.8 specification, section 4.1 Basic Types.
	//! \ingroup core_types
	typedef detail::tmat4x4<double>	dmat4x4;

}//namespace type
}//namespace core
}//namespace glm

#endif//glm_core_type
