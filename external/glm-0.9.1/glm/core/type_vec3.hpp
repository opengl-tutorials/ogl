///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-22
// Updated : 2010-02-03
// Licence : This source is under MIT License
// File    : glm/core/type_tvec3.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_gentype3
#define glm_core_type_gentype3

#include "type_vec.hpp"
#include "type_float.hpp"
#include "type_int.hpp"
#include "type_size.hpp"
#include "_swizzle.hpp"

namespace glm
{
	namespace test
	{
		void main_vec3();
	}//namespace test

	namespace detail
	{
		template <typename T> struct tref2;
		template <typename T> struct tref3;
		template <typename T> struct tref4;
		template <typename T> struct tvec2;
		template <typename T> struct tvec4;

		//! Basic 3D vector type.
		//! \ingroup core_template
		template <typename T>
		struct tvec3
		{	
			enum ctor{null};

			typedef T value_type;
			typedef std::size_t size_type;
			static size_type value_size();

			typedef tvec3<T> type;
			typedef tvec3<bool> bool_type;

			//////////////////////////////////////
			// Data

#		if(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
			value_type x, y, z;
#		elif(GLM_COMPONENT == GLM_COMPONENT_MS_EXT)
			union 
			{
				struct{value_type x, y, z;};
				struct{value_type r, g, b;};
				struct{value_type s, t, p;};
			};
#		else//(GLM_COMPONENT == GLM_COMPONENT_GLSL_NAMES)
			union {value_type x, r, s;};
			union {value_type y, g, t;};
			union {value_type z, b, p;};
#		endif//GLM_COMPONENT

			//////////////////////////////////////
			// Accesses

			value_type & operator[](size_type i);
			value_type const & operator[](size_type i) const;

			//////////////////////////////////////
			// Implicit basic constructors

			tvec3();
			tvec3(tvec3<T> const & v);

			//////////////////////////////////////
			// Explicit basic constructors

			explicit tvec3(
				ctor);
			explicit tvec3(
				value_type const & s);
			explicit tvec3(
				value_type const & s1, 
				value_type const & s2, 
				value_type const & s3);

			//////////////////////////////////////
			// Swizzle constructors

			tvec3(tref3<T> const & r);

			//////////////////////////////////////
			// Convertion scalar constructors

			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec3(
				U const & x);
			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U, typename V, typename W> 
			explicit tvec3(
				U const & x, 
				V const & y, 
				W const & z);			

			//////////////////////////////////////
			// Convertion vector constructors

			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec3(tvec2<A> const & v, B const & s);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec3(A const & s, tvec2<B> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec3(tvec3<U> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec3(tvec4<U> const & v);

			//////////////////////////////////////
			// Unary arithmetic operators

			tvec3<T> & operator= (tvec3<T> const & v);
			template <typename U> 
			tvec3<T> & operator= (tvec3<U> const & v);

			template <typename U> 
			tvec3<T> & operator+=(U const & s);
			template <typename U> 
			tvec3<T> & operator+=(tvec3<U> const & v);
			template <typename U> 
			tvec3<T> & operator-=(U const & s);
			template <typename U> 
			tvec3<T> & operator-=(tvec3<U> const & v);
			template <typename U> 
			tvec3<T> & operator*=(U const & s);
			template <typename U> 
			tvec3<T> & operator*=(tvec3<U> const & v);
			template <typename U> 
			tvec3<T> & operator/=(U const & s);
			template <typename U> 
			tvec3<T> & operator/=(tvec3<U> const & v);
			tvec3<T> & operator++();
			tvec3<T> & operator--();

			//////////////////////////////////////
			// Unary bit operators

			template <typename U>
			tvec3<T> & operator%= (U const & s);
			template <typename U>
			tvec3<T> & operator%= (tvec3<U> const & v);
			template <typename U>
			tvec3<T> & operator&= (U const & s);
			template <typename U>
			tvec3<T> & operator&= (tvec3<U> const & v);
			template <typename U>
			tvec3<T> & operator|= (U const & s);
			template <typename U>
			tvec3<T> & operator|= (tvec3<U> const & v);
			template <typename U>
			tvec3<T> & operator^= (U const & s);
			template <typename U>
			tvec3<T> & operator^= (tvec3<U> const & v);
			template <typename U>
			tvec3<T> & operator<<=(U const & s);
			template <typename U>
			tvec3<T> & operator<<=(tvec3<U> const & v);
			template <typename U>
			tvec3<T> & operator>>=(U const & s);
			template <typename U>
			tvec3<T> & operator>>=(tvec3<U> const & v);

			//////////////////////////////////////
			// Swizzle operators

			value_type swizzle(comp X) const;
			tvec2<T> swizzle(comp X, comp Y) const;
			tvec3<T> swizzle(comp X, comp Y, comp Z) const;
			tvec4<T> swizzle(comp X, comp Y, comp Z, comp W) const;
			tref3<T> swizzle(comp X, comp Y, comp Z);
		};

		template <typename T>
		struct tref3
		{
			tref3(T & x, T & y, T & z);
			tref3(tref3<T> const & r);
			tref3(tvec3<T> const & v);

			tref3<T> & operator= (tref3<T> const & r);
			tref3<T> & operator= (tvec3<T> const & v);

			T & x;
			T & y;
			T & z;
		};

		GLM_DETAIL_IS_VECTOR(tvec3);
	} //namespace detail

	namespace core{
	namespace type{

	namespace precision
	{
		//! 3 components vector of high precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<highp_float>		highp_vec3;
		//! 3 components vector of medium precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<mediump_float>	mediump_vec3;
		//! 3 components vector of low precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<lowp_float>		lowp_vec3;

		//! 3 components vector of high precision signed integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<highp_int>		highp_ivec3;
		//! 3 components vector of medium precision signed integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<mediump_int>		mediump_ivec3;
		//! 3 components vector of low precision signed integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<lowp_int>			lowp_ivec3;

		//! 3 components vector of high precision unsigned integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<highp_uint>		highp_uvec3;
		//! 3 components vector of medium precision unsigned integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<mediump_uint>		mediump_uvec3;
		//! 3 components vector of low precision unsigned integer numbers. 
		//! There is no guarantee on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		//! \ingroup core_precision
		typedef detail::tvec3<lowp_uint>		lowp_uvec3;
	}
	//namespace precision

	}//namespace type
	}//namespace core
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_vec3.inl"
#endif

#endif//glm_core_type_gentype3
