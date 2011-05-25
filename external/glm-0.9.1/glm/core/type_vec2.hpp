///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-18
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/type_tvec2.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_gentype2
#define glm_core_type_gentype2

#include "type_vec.hpp"
#include "type_float.hpp"
#include "type_int.hpp"
#include "type_size.hpp"
#include "_swizzle.hpp"

namespace glm
{
	namespace test
	{
		void main_vec2();
	}
	//namespace test

	namespace detail
	{
		template <typename T> struct tref2;
		template <typename T> struct tref3;
		template <typename T> struct tref4;
		template <typename T> struct tvec3;
		template <typename T> struct tvec4;

		//! The basic 2D vector type.
		//! \ingroup core_template
		template <typename T>
		struct tvec2
		{
			enum ctor{null};

			typedef T value_type;
			typedef std::size_t size_type;
			static size_type value_size();

			typedef tvec2<T> type;
			typedef tvec2<bool> bool_type;

			//////////////////////////////////////
			// Data

#		if(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
			value_type x, y;
#		elif(GLM_COMPONENT == GLM_COMPONENT_MS_EXT)
			union 
			{
				struct{value_type x, y;};
				struct{value_type r, g;};
				struct{value_type s, t;};
			};
#		else//(GLM_COMPONENT == GLM_COMPONENT_GLSL_NAMES)
			union {value_type x, r, s;};
			union {value_type y, g, t;};
#		endif//GLM_COMPONENT

			//////////////////////////////////////
			// Accesses

			value_type & operator[](size_type i);
			value_type const & operator[](size_type i) const;

			//////////////////////////////////////
			// Implicit basic constructors

			tvec2();
			tvec2(tvec2<T> const & v);

			//////////////////////////////////////
			// Explicit basic constructors

			explicit tvec2(
				ctor);
			explicit tvec2(
				value_type const & s);
			explicit tvec2(
				value_type const & s1, 
				value_type const & s2);

			//////////////////////////////////////
			// Swizzle constructors

			tvec2(tref2<T> const & r);

			//////////////////////////////////////
			// Convertion scalar constructors

			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec2(
				U const & x);
			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U, typename V> 
			explicit tvec2(
				U const & x, 
				V const & y);

			//////////////////////////////////////
			// Convertion vector constructors

			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec2(tvec2<U> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec2(tvec3<U> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec2(tvec4<U> const & v);

			//////////////////////////////////////
			// Unary arithmetic operators

			tvec2<T> & operator= (tvec2<T> const & v);
			template <typename U> 
			tvec2<T> & operator= (tvec2<U> const & v);

			template <typename U> 
			tvec2<T> & operator+=(U const & s);
			template <typename U> 
			tvec2<T> & operator+=(tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator-=(U const & s);
			template <typename U> 
			tvec2<T> & operator-=(tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator*=(U const & s);
			template <typename U> 
			tvec2<T> & operator*=(tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator/=(U const & s);
			template <typename U> 
			tvec2<T> & operator/=(tvec2<U> const & v);
			tvec2<T> & operator++();
			tvec2<T> & operator--();

			//////////////////////////////////////
			// Unary bit operators

			template <typename U> 
			tvec2<T> & operator%= (U const & s);
			template <typename U> 
			tvec2<T> & operator%= (tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator&= (U const & s);
			template <typename U> 
			tvec2<T> & operator&= (tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator|= (U const & s);
			template <typename U> 
			tvec2<T> & operator|= (tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator^= (U const & s);
			template <typename U> 
			tvec2<T> & operator^= (tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator<<=(U const & s);
			template <typename U> 
			tvec2<T> & operator<<=(tvec2<U> const & v);
			template <typename U> 
			tvec2<T> & operator>>=(U const & s);
			template <typename U> 
			tvec2<T> & operator>>=(tvec2<U> const & v);

			//////////////////////////////////////
			// Swizzle operators

			value_type swizzle(comp X) const;
			tvec2<T> swizzle(comp X, comp Y) const;
			tvec3<T> swizzle(comp X, comp Y, comp Z) const;
			tvec4<T> swizzle(comp X, comp Y, comp Z, comp W) const;
			tref2<T> swizzle(comp X, comp Y);
		};

		template <typename T>
		struct tref2
		{
			tref2(T & x, T & y);
			tref2(tref2<T> const & r);
			tref2(tvec2<T> const & v);

			tref2<T> & operator= (tref2<T> const & r);
			tref2<T> & operator= (tvec2<T> const & v);

			T& x;
			T& y;
		};

		GLM_DETAIL_IS_VECTOR(tvec2);

	} //namespace detail

	namespace core{
	namespace type{

	namespace precision
	{
		//! 2 components vector of high precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<highp_float>		highp_vec2;
		//! 2 components vector of medium precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<mediump_float>	mediump_vec2;
		//! 2 components vector of low precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<lowp_float>		lowp_vec2;

		//! 2 components vector of high precision signed integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<highp_int>		highp_ivec2;
		//! 2 components vector of medium precision signed integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<mediump_int>		mediump_ivec2;
		//! 2 components vector of low precision signed integer numbers.
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<lowp_int>			lowp_ivec2;
	
		//! 2 components vector of high precision unsigned integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<highp_uint>		highp_uvec2;
		//! 2 components vector of medium precision unsigned integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<mediump_uint>		mediump_uvec2;
		//! 2 components vector of low precision unsigned integer numbers.
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec2<lowp_uint>		lowp_uvec2;
	}
	//namespace precision

	}//namespace type
	}//namespace core
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_vec2.inl"
#endif

#endif//glm_core_type_gentype2
