///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-25
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/type_vec1.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_gentype1
#define glm_core_type_gentype1

#include "type_vec.hpp"
#include "type_float.hpp"
#include "type_int.hpp"
#include "type_size.hpp"
#include "_swizzle.hpp"

namespace glm
{
	namespace test
	{
		void main_vec1();
	}//namespace test

	namespace detail
	{
		template <typename T> struct tref1;
		template <typename T> struct tref2;
		template <typename T> struct tref3;
		template <typename T> struct tref4;
		template <typename T> struct tvec1;
		template <typename T> struct tvec2;
		template <typename T> struct tvec3;
		template <typename T> struct tvec4;

		template <typename T>
		struct tvec1
		{
			enum ctor{null};

			typedef T value_type;
			typedef std::size_t size_type;
			static size_type value_size();

			typedef tvec1<T> type;
			typedef tvec1<bool> bool_type;

			//////////////////////////////////////
			// Data

#		if(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
			value_type x;
#		else//(GLM_COMPONENT == GLM_COMPONENT_GLSL_NAMES)
			union {value_type x, r, s;};
#		endif//GLM_COMPONENT

			//////////////////////////////////////
			// Accesses

			value_type & operator[](size_type i);
			value_type const & operator[](size_type i) const;

			//////////////////////////////////////
			// Implicit basic constructors

			tvec1();
			tvec1(tvec1<T> const & v);

			//////////////////////////////////////
			// Explicit basic constructors

			explicit tvec1(
				ctor);
			explicit tvec1(
				value_type const & s);

			//////////////////////////////////////
			// Swizzle constructors

			tvec1(tref1<T> const & r);

			//////////////////////////////////////
			// Convertion scalar constructors

			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec1(U const & s);

			//////////////////////////////////////
			// Convertion vector constructors

			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec1(tvec2<U> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec1(tvec3<U> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec1(tvec4<U> const & v);

			//////////////////////////////////////
			// Unary arithmetic operators

			tvec1<T> & operator= (tvec1<T> const & v);

			tvec1<T> & operator+=(value_type const & s);
			tvec1<T> & operator+=(tvec1<T> const & v);
			tvec1<T> & operator-=(value_type const & s);
			tvec1<T> & operator-=(tvec1<T> const & v);
			tvec1<T> & operator*=(value_type const & s);
			tvec1<T> & operator*=(tvec1<T> const & v);
			tvec1<T> & operator/=(value_type const & s);
			tvec1<T> & operator/=(tvec1<T> const & v);
			tvec1<T> & operator++();
			tvec1<T> & operator--();

			//////////////////////////////////////
			// Unary bit operators

			tvec1<T> & operator%=(value_type const & s);
			tvec1<T> & operator%=(tvec1<T> const & v);
			tvec1<T> & operator&=(value_type const & s);
			tvec1<T> & operator&=(tvec1<T> const & v);
			tvec1<T> & operator|=(value_type const & s);
			tvec1<T> & operator|=(tvec1<T> const & v);
			tvec1<T> & operator^=(value_type const & s);
			tvec1<T> & operator^=(tvec1<T> const & v);
			tvec1<T> & operator<<=(value_type const & s);
			tvec1<T> & operator<<=(tvec1<T> const & v);
			tvec1<T> & operator>>=(value_type const & s);
			tvec1<T> & operator>>=(tvec1<T> const & v);

			//////////////////////////////////////
			// Swizzle operators

			value_type swizzle(comp X) const;
			tvec2<T> swizzle(comp X, comp Y) const;
			tvec3<T> swizzle(comp X, comp Y, comp Z) const;
			tvec4<T> swizzle(comp X, comp Y, comp Z, comp W) const;
			tref1<T> swizzle(comp X);
		};

		template <typename T>
		struct tref1
		{
			tref1(T & x);
			tref1(tref1<T> const & r);
			tref1(tvec1<T> const & v);

			tref1<T> & operator= (tref1<T> const & r);
			tref1<T> & operator= (tvec1<T> const & v);

			T& x;
		};

		GLM_DETAIL_IS_VECTOR(tvec1);

		typedef detail::tvec1<core::type::precision::highp_float>		highp_vec1_t;
		typedef detail::tvec1<core::type::precision::mediump_float>		mediump_vec1_t;
		typedef detail::tvec1<core::type::precision::lowp_float>		lowp_vec1_t;
		typedef detail::tvec1<core::type::precision::highp_int>			highp_ivec1_t;
		typedef detail::tvec1<core::type::precision::mediump_int>		mediump_ivec1_t;
		typedef detail::tvec1<core::type::precision::lowp_int>			lowp_ivec1_t;
		typedef detail::tvec1<core::type::precision::highp_uint>		highp_uvec1_t;
		typedef detail::tvec1<core::type::precision::mediump_uint>		mediump_uvec1_t;
		typedef detail::tvec1<core::type::precision::lowp_uint>			lowp_uvec1_t;

	} //namespace detail
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_vec1.inl"
#endif

#endif//glm_core_type_gentype1
