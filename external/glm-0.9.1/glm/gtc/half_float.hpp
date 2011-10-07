///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-04-29
// Updated : 2010-02-07
// Licence : This source is under MIT License
// File    : glm/gtc/half_float.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_half_float
#define glm_gtc_half_float

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_half_float extension included")
#endif

namespace glm
{
	namespace test{
		bool main_gtc_half_float();
	}//namespace 
	namespace detail
	{
#ifndef _MSC_EXTENSIONS
		template <>
		struct tvec2<thalf>
		{
			enum ctor{null};
			typedef thalf value_type;
			typedef std::size_t size_type;
			static size_type value_size();

			typedef tvec2<thalf> type;
			typedef tvec2<bool> bool_type;

			//////////////////////////////////////
			// Data

			thalf x, y;

			//////////////////////////////////////
			// Accesses

			thalf & operator[](size_type i);
			thalf const & operator[](size_type i) const;

			//////////////////////////////////////
			// Implicit basic constructors

			tvec2();
			tvec2(tvec2<thalf> const & v);

			//////////////////////////////////////
			// Explicit basic constructors

			explicit tvec2(ctor);
			explicit tvec2(
				thalf const & s);
			explicit tvec2(
				thalf const & s1, 
				thalf const & s2);

			//////////////////////////////////////
			// Swizzle constructors

			tvec2(tref2<thalf> const & r);

			//////////////////////////////////////
			// Convertion scalar constructors

			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec2(U const & x);
			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U, typename V> 
			explicit tvec2(U const & x, V const & y);			

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

			tvec2<thalf>& operator= (tvec2<thalf> const & v);

			tvec2<thalf>& operator+=(thalf const & s);
			tvec2<thalf>& operator+=(tvec2<thalf> const & v);
			tvec2<thalf>& operator-=(thalf const & s);
			tvec2<thalf>& operator-=(tvec2<thalf> const & v);
			tvec2<thalf>& operator*=(thalf const & s);
			tvec2<thalf>& operator*=(tvec2<thalf> const & v);
			tvec2<thalf>& operator/=(thalf const & s);
			tvec2<thalf>& operator/=(tvec2<thalf> const & v);
			tvec2<thalf>& operator++();
			tvec2<thalf>& operator--();

			//////////////////////////////////////
			// Swizzle operators

			thalf swizzle(comp X) const;
			tvec2<thalf> swizzle(comp X, comp Y) const;
			tvec3<thalf> swizzle(comp X, comp Y, comp Z) const;
			tvec4<thalf> swizzle(comp X, comp Y, comp Z, comp W) const;
			tref2<thalf> swizzle(comp X, comp Y);
		};

		template <>
		struct tvec3<thalf>
		{
			enum ctor{null};
			typedef thalf value_type;
			typedef std::size_t size_type;
			static size_type value_size();

			typedef tvec3<thalf> type;
			typedef tvec3<bool> bool_type;

			//////////////////////////////////////
			// Data

			thalf x, y, z;

			//////////////////////////////////////
			// Accesses

			thalf & operator[](size_type i);
			thalf const & operator[](size_type i) const;

			//////////////////////////////////////
			// Implicit basic constructors

			tvec3();
			tvec3(tvec3<thalf> const & v);

			//////////////////////////////////////
			// Explicit basic constructors

			explicit tvec3(ctor);
			explicit tvec3(
				thalf const & s);
			explicit tvec3(
				thalf const & s1, 
				thalf const & s2, 
				thalf const & s3);

			//////////////////////////////////////
			// Swizzle constructors

			tvec3(tref3<thalf> const & r);

			//////////////////////////////////////
			// Convertion scalar constructors

			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec3(U const & x);
			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U, typename V, typename W> 
			explicit tvec3(U const & x, V const & y, W const & z);			

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

			tvec3<thalf>& operator= (tvec3<thalf> const & v);

			tvec3<thalf>& operator+=(thalf const & s);
			tvec3<thalf>& operator+=(tvec3<thalf> const & v);
			tvec3<thalf>& operator-=(thalf const & s);
			tvec3<thalf>& operator-=(tvec3<thalf> const & v);
			tvec3<thalf>& operator*=(thalf const & s);
			tvec3<thalf>& operator*=(tvec3<thalf> const & v);
			tvec3<thalf>& operator/=(thalf const & s);
			tvec3<thalf>& operator/=(tvec3<thalf> const & v);
			tvec3<thalf>& operator++();
			tvec3<thalf>& operator--();

			//////////////////////////////////////
			// Swizzle operators

			thalf swizzle(comp X) const;
			tvec2<thalf> swizzle(comp X, comp Y) const;
			tvec3<thalf> swizzle(comp X, comp Y, comp Z) const;
			tvec4<thalf> swizzle(comp X, comp Y, comp Z, comp W) const;
			tref3<thalf> swizzle(comp X, comp Y, comp Z);
		};

		template <>
		struct tvec4<thalf>
		{
			enum ctor{null};
			typedef thalf value_type;
			typedef std::size_t size_type;
			static size_type value_size();

			typedef tvec4<thalf> type;
			typedef tvec4<bool> bool_type;

			//////////////////////////////////////
			// Data

			thalf x, y, z, w;

			//////////////////////////////////////
			// Accesses

			thalf & operator[](size_type i);
			thalf const & operator[](size_type i) const;

			//////////////////////////////////////
			// Implicit basic constructors

			tvec4();
			tvec4(tvec4<thalf> const & v);

			//////////////////////////////////////
			// Explicit basic constructors

			explicit tvec4(ctor);
			explicit tvec4(
				thalf const & s);
			explicit tvec4(
				thalf const & s0, 
				thalf const & s1, 
				thalf const & s2, 
				thalf const & s3);

			//////////////////////////////////////
			// Swizzle constructors

			tvec4(tref4<thalf> const & r);

			//////////////////////////////////////
			// Convertion scalar constructors

			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec4(U const & x);
			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C, typename D> 
			explicit tvec4(A const & x, B const & y, C const & z, D const & w);			

			//////////////////////////////////////
			// Convertion vector constructors

			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C> 
			explicit tvec4(tvec2<A> const & v, B const & s1, C const & s2);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C> 
			explicit tvec4(A const & s1, tvec2<B> const & v, C const & s2);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C> 
			explicit tvec4(A const & s1, B const & s2, tvec2<C> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec4(tvec3<A> const & v, B const & s);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec4(A const & s, tvec3<B> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec4(tvec2<A> const & v1, tvec2<B> const & v2);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec4(tvec4<U> const & v);

			//////////////////////////////////////
			// Unary arithmetic operators

			tvec4<thalf>& operator= (tvec4<thalf> const & v);

			tvec4<thalf>& operator+=(thalf const & s);
			tvec4<thalf>& operator+=(tvec4<thalf> const & v);
			tvec4<thalf>& operator-=(thalf const & s);
			tvec4<thalf>& operator-=(tvec4<thalf> const & v);
			tvec4<thalf>& operator*=(thalf const & s);
			tvec4<thalf>& operator*=(tvec4<thalf> const & v);
			tvec4<thalf>& operator/=(thalf const & s);
			tvec4<thalf>& operator/=(tvec4<thalf> const & v);
			tvec4<thalf>& operator++();
			tvec4<thalf>& operator--();

			//////////////////////////////////////
			// Swizzle operators

			thalf swizzle(comp X) const;
			tvec2<thalf> swizzle(comp X, comp Y) const;
			tvec3<thalf> swizzle(comp X, comp Y, comp Z) const;
			tvec4<thalf> swizzle(comp X, comp Y, comp Z, comp W) const;
			tref4<thalf> swizzle(comp X, comp Y, comp Z, comp W);
		};
#endif//_MSC_EXTENSIONS
	}
	//namespace detail

	namespace gtc{
	//! GLM_GTC_half_float extension: Add support for half precision floating-point types
	namespace half_float
	{
		/// \addtogroup gtc_half_float
		///@{

		//! Type for half-precision floating-point numbers. 
		//! From GLM_GTC_half_float extension.
		typedef detail::thalf					half;

		//! Vector of 2 half-precision floating-point numbers. 
		//! From GLM_GTC_half_float extension.
		typedef detail::tvec2<detail::thalf>	hvec2;

		//! Vector of 3 half-precision floating-point numbers.
		//! From GLM_GTC_half_float extension.
		typedef detail::tvec3<detail::thalf>	hvec3;

		//! Vector of 4 half-precision floating-point numbers. 
		//! From GLM_GTC_half_float extension.
		typedef detail::tvec4<detail::thalf>	hvec4;

		//! 2 * 2 matrix of half-precision floating-point numbers.
		//! From GLM_GTC_half_float extension.
		typedef detail::tmat2x2<detail::thalf>	hmat2;

		//! 3 * 3 matrix of half-precision floating-point numbers.
		//! From GLM_GTC_half_float extension.
		typedef detail::tmat3x3<detail::thalf>	hmat3;

		//! 4 * 4 matrix of half-precision floating-point numbers.
		//! From GLM_GTC_half_float extension.
		typedef detail::tmat4x4<detail::thalf>	hmat4;

		///@}

	}//namespace half_float
	}//namespace gtc
}//namespace glm

#include "half_float.inl"

namespace glm{using namespace gtc::half_float;}

#endif//glm_gtc_half_float
