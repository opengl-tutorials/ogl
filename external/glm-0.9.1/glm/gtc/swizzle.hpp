///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-02-20
// Updated : 2010-02-20
// Licence : This source is under MIT License
// File    : glm/gtc/swizzle.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_swizzle
#define glm_gtc_swizzle

// Dependency:
#include "../glm.hpp"
#include "../gtc/type_precision.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_swizzle extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtc_swizzle();
	}//namespace test

	namespace gtc{
	//! GLM_GTC_swizzle extension
	namespace swizzle
	{
		using namespace gtc::half_float;

		template <typename T, template <typename> class vecType>
		T const & swizzle(	
			vecType<T> const & v,
			comp x);

		template <typename T, template <typename> class vecType>
		detail::tvec2<T> const & swizzle(
			vecType<T> const & v,
			comp x, comp y);

		template <typename T, template <typename> class vecType>
		detail::tvec3<T> const & swizzle(
			vecType<T> const & v,
			comp x, comp y, comp z);

		template <typename T, template <typename> class vecType>
		detail::tvec4<T> const & swizzle(
			vecType<T> const & v,
			comp x, comp y, comp z, comp w);

		template <typename T, template <typename> class vecType>
		T & swizzle(
			vecType<T> & v,
			comp x);

		template <typename T, template <typename> class vecType>
		detail::tref2<T> swizzle(
			vecType<T> & v,
			comp x, comp y);

		template <typename T, template <typename> class vecType>
		detail::tref3<T> swizzle(
			vecType<T> & v,
			comp x, comp y, comp z);

		template <typename T, template <typename> class vecType>
		detail::tref4<T> swizzle(
			vecType<T> & v,
			comp x, comp y, comp z, comp w);

#		define static_swizzle1(TYPE, SIZE)							\
			template <comp x>										\
			inline TYPE swizzle(detail::tvec##SIZE<TYPE> const & v)	\
			{return v[x];}											\
																	\
			template <comp x>										\
			inline TYPE& swizzle(detail::tvec##SIZE<TYPE> & v)		\
			{return v[x];}

		static_swizzle1(detail::float16, 2)
		static_swizzle1(detail::float16, 3)
		static_swizzle1(detail::float16, 4)
		static_swizzle1(detail::float32, 2)
		static_swizzle1(detail::float32, 3)
		static_swizzle1(detail::float32, 4)
		static_swizzle1(detail::float64, 2)
		static_swizzle1(detail::float64, 3)
		static_swizzle1(detail::float64, 4)

		static_swizzle1(detail::int8,  2)
		static_swizzle1(detail::int8,  3)
		static_swizzle1(detail::int8,  4)
		static_swizzle1(detail::int16, 2)
		static_swizzle1(detail::int16, 3)
		static_swizzle1(detail::int16, 4)
		static_swizzle1(detail::int32, 2)
		static_swizzle1(detail::int32, 3)
		static_swizzle1(detail::int32, 4)
		static_swizzle1(detail::int64, 2)
		static_swizzle1(detail::int64, 3)
		static_swizzle1(detail::int64, 4)

		static_swizzle1(detail::uint8,  2)
		static_swizzle1(detail::uint8,  3)
		static_swizzle1(detail::uint8,  4)
		static_swizzle1(detail::uint16, 2)
		static_swizzle1(detail::uint16, 3)
		static_swizzle1(detail::uint16, 4)
		static_swizzle1(detail::uint32, 2)
		static_swizzle1(detail::uint32, 3)
		static_swizzle1(detail::uint32, 4)
		static_swizzle1(detail::uint64, 2)
		static_swizzle1(detail::uint64, 3)
		static_swizzle1(detail::uint64, 4)

#		define static_swizzle2_const(TYPE) \
			template <comp x, comp y> \
			inline TYPE swizzle(TYPE const & v) \
			{return TYPE(v[x], v[y]);}

#		define static_swizzle3_const(TYPE) \
			template <comp x, comp y, comp z> \
			inline TYPE swizzle(TYPE const & v) \
			{return TYPE(v[x], v[y], v[z]);}

#		define static_swizzle4_const(TYPE) \
			template <comp x, comp y, comp z, comp w> \
			inline TYPE swizzle(TYPE const & v) \
			{return TYPE(v[x], v[y], v[z], v[w]);}
/*
#		define static_swizzle2_const(TYPE, SIZE)									\
			template <comp x, comp y>												\
			inline detail::tvec2<TYPE> swizzle(detail::tvec##SIZE<TYPE> const & v)	\
			{return detail::tvec2<TYPE>(v[x], v[y]);}

#		define static_swizzle3_const(TYPE, SIZE)									\
			template <comp x, comp y, comp z>										\
			inline detail::tvec3<TYPE> swizzle(detail::tvec##SIZE<TYPE> const & v)	\
			{return detail::tvec3<TYPE>(v[x], v[y], v[z]);}

#		define static_swizzle4_const(TYPE, SIZE)									\
			template <comp x, comp y, comp z, comp w>								\
			inline detail::tvec4<TYPE> swizzle(detail::tvec##SIZE<TYPE> const & v)	\
			{return detail::tvec4<TYPE>(v[x], v[y], v[z], v[w]);}
*/
		static_swizzle2_const(glm::f16vec2)
		static_swizzle2_const(glm::f16vec3)
		static_swizzle2_const(glm::f16vec4)
		static_swizzle2_const(glm::f32vec2)
		static_swizzle2_const(glm::f32vec3)
		static_swizzle2_const(glm::f32vec4)
		static_swizzle2_const(glm::f64vec2)
		static_swizzle2_const(glm::f64vec3)
		static_swizzle2_const(glm::f64vec4)

		static_swizzle2_const(glm::i8vec2)
		static_swizzle2_const(glm::i8vec3)
		static_swizzle2_const(glm::i8vec4)
		static_swizzle2_const(glm::i16vec2)
		static_swizzle2_const(glm::i16vec3)
		static_swizzle2_const(glm::i16vec4)
		static_swizzle2_const(glm::i32vec2)
		static_swizzle2_const(glm::i32vec3)
		static_swizzle2_const(glm::i32vec4)
		static_swizzle2_const(glm::i64vec2)
		static_swizzle2_const(glm::i64vec3)
		static_swizzle2_const(glm::i64vec4)

		static_swizzle2_const(glm::u8vec2)
		static_swizzle2_const(glm::u8vec3)
		static_swizzle2_const(glm::u8vec4)
		static_swizzle2_const(glm::u16vec2)
		static_swizzle2_const(glm::u16vec3)
		static_swizzle2_const(glm::u16vec4)
		static_swizzle2_const(glm::u32vec2)
		static_swizzle2_const(glm::u32vec3)
		static_swizzle2_const(glm::u32vec4)
		static_swizzle2_const(glm::u64vec2)
		static_swizzle2_const(glm::u64vec3)
		static_swizzle2_const(glm::u64vec4)

		static_swizzle3_const(glm::f16vec2)
		static_swizzle3_const(glm::f16vec3)
		static_swizzle3_const(glm::f16vec4)
		static_swizzle3_const(glm::f32vec2)
		static_swizzle3_const(glm::f32vec3)
		static_swizzle3_const(glm::f32vec4)
		static_swizzle3_const(glm::f64vec2)
		static_swizzle3_const(glm::f64vec3)
		static_swizzle3_const(glm::f64vec4)

		static_swizzle3_const(glm::i8vec2)
		static_swizzle3_const(glm::i8vec3)
		static_swizzle3_const(glm::i8vec4)
		static_swizzle3_const(glm::i16vec2)
		static_swizzle3_const(glm::i16vec3)
		static_swizzle3_const(glm::i16vec4)
		static_swizzle3_const(glm::i32vec2)
		static_swizzle3_const(glm::i32vec3)
		static_swizzle3_const(glm::i32vec4)
		static_swizzle3_const(glm::i64vec2)
		static_swizzle3_const(glm::i64vec3)
		static_swizzle3_const(glm::i64vec4)

		static_swizzle3_const(glm::u8vec2)
		static_swizzle3_const(glm::u8vec3)
		static_swizzle3_const(glm::u8vec4)
		static_swizzle3_const(glm::u16vec2)
		static_swizzle3_const(glm::u16vec3)
		static_swizzle3_const(glm::u16vec4)
		static_swizzle3_const(glm::u32vec2)
		static_swizzle3_const(glm::u32vec3)
		static_swizzle3_const(glm::u32vec4)
		static_swizzle3_const(glm::u64vec2)
		static_swizzle3_const(glm::u64vec3)
		static_swizzle3_const(glm::u64vec4)

		static_swizzle4_const(glm::f16vec2)
		static_swizzle4_const(glm::f16vec3)
		static_swizzle4_const(glm::f16vec4)
		static_swizzle4_const(glm::f32vec2)
		static_swizzle4_const(glm::f32vec3)
		static_swizzle4_const(glm::f32vec4)
		static_swizzle4_const(glm::f64vec2)
		static_swizzle4_const(glm::f64vec3)
		static_swizzle4_const(glm::f64vec4)

		static_swizzle4_const(glm::i8vec2)
		static_swizzle4_const(glm::i8vec3)
		static_swizzle4_const(glm::i8vec4)
		static_swizzle4_const(glm::i16vec2)
		static_swizzle4_const(glm::i16vec3)
		static_swizzle4_const(glm::i16vec4)
		static_swizzle4_const(glm::i32vec2)
		static_swizzle4_const(glm::i32vec3)
		static_swizzle4_const(glm::i32vec4)
		static_swizzle4_const(glm::i64vec2)
		static_swizzle4_const(glm::i64vec3)
		static_swizzle4_const(glm::i64vec4)

		static_swizzle4_const(glm::u8vec2)
		static_swizzle4_const(glm::u8vec3)
		static_swizzle4_const(glm::u8vec4)
		static_swizzle4_const(glm::u16vec2)
		static_swizzle4_const(glm::u16vec3)
		static_swizzle4_const(glm::u16vec4)
		static_swizzle4_const(glm::u32vec2)
		static_swizzle4_const(glm::u32vec3)
		static_swizzle4_const(glm::u32vec4)
		static_swizzle4_const(glm::u64vec2)
		static_swizzle4_const(glm::u64vec3)
		static_swizzle4_const(glm::u64vec4)

#		define static_swizzle2_ref(TYPE) \
			template <glm::comp x, glm::comp y> \
			inline glm::detail::tref2<typename TYPE::value_type> swizzle(TYPE & v) \
			{return glm::detail::tref2<typename TYPE::value_type>(v[x], v[y]);}	

#		define static_swizzle3_ref(TYPE) \
			template <glm::comp x, glm::comp y, glm::comp z> \
			inline glm::detail::tref3<typename TYPE::value_type> swizzle(TYPE & v) \
			{return glm::detail::tref3<typename TYPE::value_type>(v[x], v[y], v[z]);}	

#		define static_swizzle4_ref(TYPE) \
			template <glm::comp x, glm::comp y, glm::comp z, glm::comp w> \
			inline glm::detail::tref4<typename TYPE::value_type> swizzle(TYPE & v) \
			{return glm::detail::tref4<typename TYPE::value_type>(v[x], v[y], v[z], v[w]);}	

		static_swizzle2_ref(glm::f16vec2)
		static_swizzle2_ref(glm::f16vec3)
		static_swizzle2_ref(glm::f16vec4)
		static_swizzle2_ref(glm::f32vec2)
		static_swizzle2_ref(glm::f32vec3)
		static_swizzle2_ref(glm::f32vec4)
		static_swizzle2_ref(glm::f64vec2)
		static_swizzle2_ref(glm::f64vec3)
		static_swizzle2_ref(glm::f64vec4)

		static_swizzle2_ref(glm::i8vec2)
		static_swizzle2_ref(glm::i8vec3)
		static_swizzle2_ref(glm::i8vec4)
		static_swizzle2_ref(glm::i16vec2)
		static_swizzle2_ref(glm::i16vec3)
		static_swizzle2_ref(glm::i16vec4)
		static_swizzle2_ref(glm::i32vec2)
		static_swizzle2_ref(glm::i32vec3)
		static_swizzle2_ref(glm::i32vec4)
		static_swizzle2_ref(glm::i64vec2)
		static_swizzle2_ref(glm::i64vec3)
		static_swizzle2_ref(glm::i64vec4)

		static_swizzle2_ref(glm::u8vec2)
		static_swizzle2_ref(glm::u8vec3)
		static_swizzle2_ref(glm::u8vec4)
		static_swizzle2_ref(glm::u16vec2)
		static_swizzle2_ref(glm::u16vec3)
		static_swizzle2_ref(glm::u16vec4)
		static_swizzle2_ref(glm::u32vec2)
		static_swizzle2_ref(glm::u32vec3)
		static_swizzle2_ref(glm::u32vec4)
		static_swizzle2_ref(glm::u64vec2)
		static_swizzle2_ref(glm::u64vec3)
		static_swizzle2_ref(glm::u64vec4)

		static_swizzle3_ref(glm::f16vec3)
		static_swizzle3_ref(glm::f16vec4)
		static_swizzle3_ref(glm::f32vec3)
		static_swizzle3_ref(glm::f32vec4)
		static_swizzle3_ref(glm::f64vec3)
		static_swizzle3_ref(glm::f64vec4)

		static_swizzle3_ref(glm::i8vec3)
		static_swizzle3_ref(glm::i8vec4)
		static_swizzle3_ref(glm::i16vec3)
		static_swizzle3_ref(glm::i16vec4)
		static_swizzle3_ref(glm::i32vec3)
		static_swizzle3_ref(glm::i32vec4)
		static_swizzle3_ref(glm::i64vec3)
		static_swizzle3_ref(glm::i64vec4)

		static_swizzle3_ref(glm::u8vec3)
		static_swizzle3_ref(glm::u8vec4)
		static_swizzle3_ref(glm::u16vec3)
		static_swizzle3_ref(glm::u16vec4)
		static_swizzle3_ref(glm::u32vec3)
		static_swizzle3_ref(glm::u32vec4)
		static_swizzle3_ref(glm::u64vec3)
		static_swizzle3_ref(glm::u64vec4)

		static_swizzle4_ref(glm::f16vec4)
		static_swizzle4_ref(glm::f32vec4)
		static_swizzle4_ref(glm::f64vec4)

		static_swizzle4_ref(glm::i8vec4)
		static_swizzle4_ref(glm::i16vec4)
		static_swizzle4_ref(glm::i32vec4)
		static_swizzle4_ref(glm::i64vec4)

		static_swizzle4_ref(glm::u8vec4)
		static_swizzle4_ref(glm::u16vec4)
		static_swizzle4_ref(glm::u32vec4)
		static_swizzle4_ref(glm::u64vec4)

	}//namespace swizzle
	}//namespace gtc
}//namespace glm

#include "swizzle.inl"

namespace glm{using namespace gtc::swizzle;}

#endif//glm_gtc_swizzle
