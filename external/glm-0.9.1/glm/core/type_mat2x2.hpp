///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-01-27
// Updated : 2010-02-11
// Licence : This source is under MIT License
// File    : glm/core/type_mat2x2.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat2x2
#define glm_core_type_mat2x2

#include "type_mat.hpp"

namespace glm
{
	namespace test
	{
		void main_mat2x2();
	}//namespace test

	namespace detail
	{
		template <typename T> struct tvec1;
		template <typename T> struct tvec2;
		template <typename T> struct tvec3;
		template <typename T> struct tvec4;
		template <typename T> struct tmat2x2;
		template <typename T> struct tmat2x3;
		template <typename T> struct tmat2x4;
		template <typename T> struct tmat3x2;
		template <typename T> struct tmat3x3;
		template <typename T> struct tmat3x4;
		template <typename T> struct tmat4x2;
		template <typename T> struct tmat4x3;
		template <typename T> struct tmat4x4;

		//! \brief Template for 2 * 2 matrix of floating-point numbers.
		//! \ingroup core_template
		template <typename T> 
		struct tmat2x2
		{
			enum ctor{null};
			typedef T value_type;
			typedef std::size_t size_type;
			typedef tvec2<T> col_type;
			typedef tvec2<T> row_type;
			static size_type col_size();
			static size_type row_size();

			typedef tmat2x2<T> type;
			typedef tmat2x2<T> transpose_type;

		public:
			// Implementation detail
			tmat2x2<T> _inverse() const;

		private:
			// Data 
			col_type value[2];

		public:
			// Constructors
			tmat2x2();
			tmat2x2(
				tmat2x2 const & m);

			explicit tmat2x2(
				ctor Null);
			explicit tmat2x2(
				value_type const & x);
			explicit tmat2x2(
				value_type const & x1, value_type const & y1, 
				value_type const & x2, value_type const & y2);
			explicit tmat2x2(
				col_type const & v1, 
				col_type const & v2);

			// Conversions
			template <typename U> 
			explicit tmat2x2(tmat2x2<U> const & m);

			explicit tmat2x2(tmat3x3<T> const & x);
			explicit tmat2x2(tmat4x4<T> const & x);
			explicit tmat2x2(tmat2x3<T> const & x);
			explicit tmat2x2(tmat3x2<T> const & x);
			explicit tmat2x2(tmat2x4<T> const & x);
			explicit tmat2x2(tmat4x2<T> const & x);
			explicit tmat2x2(tmat3x4<T> const & x);
			explicit tmat2x2(tmat4x3<T> const & x);

			//////////////////////////////////////
			// Accesses

			col_type & operator[](size_type i);
			col_type const & operator[](size_type i) const;

			// Unary updatable operators
			tmat2x2<T> & operator=(tmat2x2<T> const & m);
			template <typename U> 
			tmat2x2<T> & operator=(tmat2x2<U> const & m);
			template <typename U> 
			tmat2x2<T> & operator+=(U const & s);
			template <typename U> 
			tmat2x2<T> & operator+=(tmat2x2<U> const & m);
			template <typename U> 
			tmat2x2<T> & operator-=(U const & s);
			template <typename U> 
			tmat2x2<T> & operator-=(tmat2x2<U> const & m);
			template <typename U> 
			tmat2x2<T> & operator*=(U const & s);
			template <typename U> 
			tmat2x2<T> & operator*=(tmat2x2<U> const & m);
			template <typename U> 
			tmat2x2<T> & operator/=(U const & s);
			template <typename U> 
			tmat2x2<T> & operator/=(tmat2x2<U> const & m);
			tmat2x2<T> & operator++();
			tmat2x2<T> & operator--();
		};

		// Binary operators
		template <typename T> 
		tmat2x2<T> operator+ (
			tmat2x2<T> const & m, 
			typename tmat2x2<T>::value_type const & s);

		template <typename T> 
		tmat2x2<T> operator+ (
			typename tmat2x2<T>::value_type const & s, 
			tmat2x2<T> const & m);

		template <typename T> 
		tmat2x2<T> operator+ (
			tmat2x2<T> const & m1, 
			tmat2x2<T> const & m2);
	    
		template <typename T> 
		tmat2x2<T> operator- (
			tmat2x2<T> const & m, 
			typename tmat2x2<T>::value_type const & s);

		template <typename T> 
		tmat2x2<T> operator- (
			typename tmat2x2<T>::value_type const & s, 
			tmat2x2<T> const & m);

		template <typename T> 
		tmat2x2<T> operator- (
			tmat2x2<T> const & m1, 
			tmat2x2<T> const & m2);

		template <typename T> 
		tmat2x2<T> operator* (
			tmat2x2<T> const & m, 
			typename tmat2x2<T>::value_type const & s);

		template <typename T> 
		tmat2x2<T> operator* (
			typename tmat2x2<T>::value_type const & s, 
			tmat2x2<T> const & m);

		template <typename T> 
		typename tmat2x2<T>::col_type operator* (
			tmat2x2<T> const & m, 
			typename tmat2x2<T>::row_type const & v);

		template <typename T> 
		typename tmat2x2<T>::row_type operator* (
			typename tmat2x2<T>::col_type const & v, 
			tmat2x2<T> const & m);

		template <typename T> 
		tmat2x2<T> operator* (
			tmat2x2<T> const & m1, 
			tmat2x2<T> const & m2);

		template <typename T> 
		tmat2x2<T> operator/ (
			tmat2x2<T> const & m, 
			typename tmat2x2<T>::value_type const & s);

		template <typename T> 
		tmat2x2<T> operator/ (
			typename tmat2x2<T>::value_type const & s,
			tmat2x2<T> const & m);

		template <typename T> 
		typename tmat2x2<T>::col_type operator/ (
			tmat2x2<T> const & m, 
			typename tmat2x2<T>::row_type const & v);

		template <typename T> 
		typename tmat2x2<T>::row_type operator/ (
			typename tmat2x2<T>::col_type const & v, 
			tmat2x2<T> const & m);

		template <typename T> 
		tmat2x2<T> operator/ (
			tmat2x2<T> const & m1, 
			tmat2x2<T> const & m2);

		// Unary constant operators
		template <typename T> 
		tmat2x2<T> const operator-  (
			tmat2x2<T> const & m);

		template <typename T> 
		tmat2x2<T> const operator-- (
			tmat2x2<T> const & m, 
			int);

		template <typename T> 
		tmat2x2<T> const operator++ (
			tmat2x2<T> const & m, 
			int);

	} //namespace detail

	namespace core{
	namespace type{

	namespace precision
	{
		//! 2 columns of 2 components matrix of low precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		//! \ingroup core_precision
		typedef detail::tmat2x2<lowp_float>		lowp_mat2x2;
		//! 2 columns of 2 components matrix of medium precision floating-point numbers. 
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		//! \ingroup core_precision
		typedef detail::tmat2x2<mediump_float>	mediump_mat2x2;
		//! 2 columns of 2 components matrix of high precision floating-point numbers. 
		//! There is no guarantee on the actual precision. 
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		//! \ingroup core_precision
		typedef detail::tmat2x2<highp_float>	highp_mat2x2;
	}
	//namespace precision

	}//namespace type
	}//namespace core
} //namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat2x2.inl"
#endif

#endif //glm_core_type_mat2x2
