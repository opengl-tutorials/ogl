///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-06-04
// Updated : 2009-06-04
// Licence : This source is under MIT License
// File    : glm/gtc/type_precision.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_half
// - GLM_GTC_quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_type_precision
#define glm_gtc_type_precision

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtc/quaternion.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_type_precision extension included")
#endif

namespace glm
{
	namespace test{
		bool main_gtc_type_precision();
	}//namespace test

	namespace gtc{
	//! GLM_GTC_type_precision extension: Defined types with specific size.
	namespace type_precision
	{
		///////////////////////////
		// Dependences

		using namespace gtc::half_float;
		using namespace gtc::quaternion;

		///////////////////////////
		// Signed int vector types 

		/// \addtogroup gtc_type_precision
		///@{

		typedef detail::int8						int8;         //!< \brief 8bit signed integer. (from GLM_GTC_type_precision extension)
		typedef detail::int16						int16;        //!< \brief 16bit signed integer. (from GLM_GTC_type_precision extension)
		typedef detail::int32						int32;        //!< \brief 32bit signed integer. (from GLM_GTC_type_precision extension)
		typedef detail::int64						int64;        //!< \brief 64bit signed integer. (from GLM_GTC_type_precision extension)

		typedef int8								i8;         //!< \brief 8bit signed integer. (from GLM_GTC_type_precision extension)
		typedef int16								i16;        //!< \brief 16bit signed integer. (from GLM_GTC_type_precision extension)
		typedef int32								i32;        //!< \brief 32bit signed integer. (from GLM_GTC_type_precision extension)
		typedef int64								i64;        //!< \brief 64bit signed integer. (from GLM_GTC_type_precision extension)

		//typedef i8									i8vec1;		//!< \brief 8bit signed integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<i8>					i8vec2;     //!< \brief 8bit signed integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<i8>					i8vec3;     //!< \brief 8bit signed integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<i8>					i8vec4;     //!< \brief 8bit signed integer vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef i16									i16vec1;	//!< \brief 16bit signed integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<i16>					i16vec2;    //!< \brief 16bit signed integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<i16>					i16vec3;    //!< \brief 16bit signed integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<i16>					i16vec4;    //!< \brief 16bit signed integer vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef i32									i32vec1;	//!< \brief 32bit signed integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<i32>					i32vec2;    //!< \brief 32bit signed integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<i32>					i32vec3;    //!< \brief 32bit signed integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<i32>					i32vec4;    //!< \brief 32bit signed integer vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef i64									i64vec1;	//!< \brief 32bit signed integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<i64>					i64vec2;    //!< \brief 64bit signed integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<i64>					i64vec3;    //!< \brief 64bit signed integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<i64>					i64vec4;    //!< \brief 64bit signed integer vector of 4 components. (from GLM_GTC_type_precision extension)

		/////////////////////////////
		// Unsigned int vector types 

		typedef detail::uint8						uint8;         //!< \brief 8bit unsigned integer. (from GLM_GTC_type_precision extension)
		typedef detail::uint16						uint16;        //!< \brief 16bit unsigned integer. (from GLM_GTC_type_precision extension)
		typedef detail::uint32						uint32;        //!< \brief 32bit unsigned integer. (from GLM_GTC_type_precision extension)
		typedef detail::uint64						uint64;        //!< \brief 64bit unsigned integer. (from GLM_GTC_type_precision extension)

		typedef uint8								u8;         //!< \brief 8bit unsigned integer. (from GLM_GTC_type_precision extension)
		typedef uint16								u16;        //!< \brief 16bit unsigned integer. (from GLM_GTC_type_precision extension)
		typedef uint32								u32;        //!< \brief 32bit unsigned integer. (from GLM_GTC_type_precision extension)
		typedef uint64								u64;        //!< \brief 64bit unsigned integer. (from GLM_GTC_type_precision extension)

		//typedef u8									u8vec1;		//!< \brief 8bit unsigned integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<u8>					u8vec2;     //!< \brief 8bit unsigned integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<u8>					u8vec3;     //!< \brief 8bit unsigned integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<u8>					u8vec4;     //!< \brief 8bit unsigned integer vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef u16									u16vec1;    //!< \brief 16bit unsigned integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<u16>					u16vec2;    //!< \brief 16bit unsigned integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<u16>					u16vec3;    //!< \brief 16bit unsigned integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<u16>					u16vec4;    //!< \brief 16bit unsigned integer vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef u32									u32vec1;    //!< \brief 32bit unsigned integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<u32>					u32vec2;    //!< \brief 32bit unsigned integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<u32>					u32vec3;    //!< \brief 32bit unsigned integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<u32>					u32vec4;    //!< \brief 32bit unsigned integer vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef u64									u64vec1;    //!< \brief 64bit unsigned integer scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<u64>					u64vec2;    //!< \brief 64bit unsigned integer vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<u64>					u64vec3;    //!< \brief 64bit unsigned integer vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<u64>					u64vec4;    //!< \brief 64bit unsigned integer vector of 4 components. (from GLM_GTC_type_precision extension)

		//////////////////////
		// Float vector types 

		typedef detail::float16						float16;	//!< \brief Half-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::float32						float32;	//!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::float64						float64;	//!< \brief Double-precision floating-point scalar. (from GLM_GTC_type_precision extension)

		typedef float16								f16;        //!< \brief Half-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef float32								f32;        //!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef float64								f64;        //!< \brief Double-precision floating-point scalar. (from GLM_GTC_type_precision extension)

		typedef detail::tvec2<float>				fvec2;		//!<  Vector of 2 single-precision floating-point numbers. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<float>				fvec3;		//!<  Vector of 3 single-precision floating-point numbers. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<float>				fvec4;		//!<  Vector of 4 single-precision floating-point numbers. (from GLM_GTC_type_precision extension)

		//typedef f16									f16vec1;    //!< \brief Half-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<f16>					f16vec2;    //!< \brief Half-precision floating-point vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<f16>					f16vec3;    //!< \brief Half-precision floating-point vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<f16>					f16vec4;    //!< \brief Half-precision floating-point vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef f32									f32vec1;    //!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<f32>					f32vec2;    //!< \brief Single-precision floating-point vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<f32>					f32vec3;    //!< \brief Single-precision floating-point vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<f32>					f32vec4;    //!< \brief Single-precision floating-point vector of 4 components. (from GLM_GTC_type_precision extension)

		//typedef f64									f64vec1;    //!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tvec2<f64>					f64vec2;    //!< \brief Double-precision floating-point vector of 2 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec3<f64>					f64vec3;    //!< \brief Double-precision floating-point vector of 3 components. (from GLM_GTC_type_precision extension)
		typedef detail::tvec4<f64>					f64vec4;    //!< \brief Double-precision floating-point vector of 4 components. (from GLM_GTC_type_precision extension)

		//////////////////////
		// Float matrix types 

		//typedef f32									fmat1;	//!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f32>				fmat2;	//!< \brief Single-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f32>				fmat3;	//!< \brief Single-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f32>				fmat4;	//!< \brief Single-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//typedef f32									fmat1x1;	//!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f32>				fmat2x2;  //!< \brief Single-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x3<f32>				fmat2x3;	//!< \brief Single-precision floating-point 2x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x4<f32>				fmat2x4;	//!< \brief Single-precision floating-point 2x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x2<f32>				fmat3x2;	//!< \brief Single-precision floating-point 3x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f32>				fmat3x3;	//!< \brief Single-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x4<f32>				fmat3x4;	//!< \brief Single-precision floating-point 3x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x2<f32>				fmat4x2;	//!< \brief Single-precision floating-point 4x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x3<f32>				fmat4x3;	//!< \brief Single-precision floating-point 4x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f32>				fmat4x4;	//!< \brief Single-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//typedef f16									f16mat1;    //!< \brief Half-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f16>				f16mat2;	//!< \brief Half-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f16>				f16mat3;	//!< \brief Half-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f16>				f16mat4;	//!< \brief Half-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//typedef f16									f16mat1x1;	//!< \brief Half-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f16>				f16mat2x2;	//!< \brief Half-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x3<f16>				f16mat2x3;	//!< \brief Half-precision floating-point 2x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x4<f16>				f16mat2x4;	//!< \brief Half-precision floating-point 2x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x2<f16>				f16mat3x2;	//!< \brief Half-precision floating-point 3x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f16>				f16mat3x3;	//!< \brief Half-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x4<f16>				f16mat3x4;	//!< \brief Half-precision floating-point 3x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x2<f16>				f16mat4x2;	//!< \brief Half-precision floating-point 4x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x3<f16>				f16mat4x3;	//!< \brief Half-precision floating-point 4x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f16>				f16mat4x4;	//!< \brief Half-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//typedef f32									f32mat1;	//!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f32>				f32mat2;	//!< \brief Single-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f32>				f32mat3;	//!< \brief Single-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f32>				f32mat4;	//!< \brief Single-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//typedef f32									f32mat1x1;	//!< \brief Single-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f32>				f32mat2x2;  //!< \brief Single-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x3<f32>				f32mat2x3;	//!< \brief Single-precision floating-point 2x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x4<f32>				f32mat2x4;	//!< \brief Single-precision floating-point 2x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x2<f32>				f32mat3x2;	//!< \brief Single-precision floating-point 3x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f32>				f32mat3x3;	//!< \brief Single-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x4<f32>				f32mat3x4;	//!< \brief Single-precision floating-point 3x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x2<f32>				f32mat4x2;	//!< \brief Single-precision floating-point 4x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x3<f32>				f32mat4x3;	//!< \brief Single-precision floating-point 4x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f32>				f32mat4x4;	//!< \brief Single-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//typedef f64									f64mat1;	//!< \brief Double-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f64>				f64mat2;	//!< \brief Double-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f64>				f64mat3;	//!< \brief Double-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f64>				f64mat4;	//!< \brief Double-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//typedef f64									f64mat1x1;	//!< \brief Double-precision floating-point scalar. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x2<f64>				f64mat2x2;	//!< \brief Double-precision floating-point 2x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x3<f64>				f64mat2x3;	//!< \brief Double-precision floating-point 2x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat2x4<f64>				f64mat2x4;	//!< \brief Double-precision floating-point 2x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x2<f64>				f64mat3x2;	//!< \brief Double-precision floating-point 3x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x3<f64>				f64mat3x3;	//!< \brief Double-precision floating-point 3x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat3x4<f64>				f64mat3x4;	//!< \brief Double-precision floating-point 3x4 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x2<f64>				f64mat4x2;	//!< \brief Double-precision floating-point 4x2 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x3<f64>				f64mat4x3;	//!< \brief Double-precision floating-point 4x3 matrix. (from GLM_GTC_type_precision extension)
		typedef detail::tmat4x4<f64>				f64mat4x4;	//!< \brief Double-precision floating-point 4x4 matrix. (from GLM_GTC_type_precision extension)

		//////////////////////////
		// Float quaternion types 

		typedef detail::tquat<f16>					f16quat;    //!< \brief Half-precision floating-point quaternion. (from GLM_GTC_type_precision extension)
		typedef detail::tquat<f32>					f32quat;    //!< \brief Single-precision floating-point quaternion. (from GLM_GTC_type_precision extension)
		typedef detail::tquat<f64>					f64quat;    //!< \brief Double-precision floating-point quaternion. (from GLM_GTC_type_precision extension)

		///@}

	}//namespace type_precision
	}//namespace gtc
}//namespace glm

#include "type_precision.inl"

namespace glm{using namespace gtc::type_precision;}

#endif//glm_gtc_type_precision
