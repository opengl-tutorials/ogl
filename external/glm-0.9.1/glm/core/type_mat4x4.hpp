///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-01-27
// Updated : 2008-08-30
// Licence : This source is under MIT License
// File    : glm/core/type_mat4x4.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat4x4
#define glm_core_type_mat4x4

#include "type_mat.hpp"

namespace glm
{
	namespace test
	{
		void main_mat4x4();
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

		//! \brief Template for 4 * 4 matrix of floating-point numbers.
		//! \ingroup core_template
		template <typename T> 
		struct tmat4x4
		{
			enum ctor{null};
			typedef T value_type;
			typedef std::size_t size_type;
			typedef tvec4<T> col_type;
			typedef tvec4<T> row_type;
			static size_type col_size();
			static size_type row_size();

			typedef tmat4x4<T> type;
			typedef tmat4x4<T> transpose_type;

		public:
			// Implementation detail
			tmat4x4<T> _inverse() const;

		private:
			// Data 
			col_type value[4];

		public:
			// Constructors
			tmat4x4();
			tmat4x4(tmat4x4 const & m);

			explicit tmat4x4(
				ctor Null);
			explicit tmat4x4(
				value_type const & x);
			explicit tmat4x4(
				value_type const & x0, value_type const & y0, value_type const & z0, value_type const & w0,
				value_type const & x1, value_type const & y1, value_type const & z1, value_type const & w1,
				value_type const & x2, value_type const & y2, value_type const & z2, value_type const & w2,
				value_type const & x3, value_type const & y3, value_type const & z3, value_type const & w3);
			explicit tmat4x4(
				col_type const & v0, 
				col_type const & v1,
				col_type const & v2,
				col_type const & v3);

			// Conversions
			template <typename U> 
			explicit tmat4x4(tmat4x4<U> const & m);

			explicit tmat4x4(tmat2x2<T> const & x);
			explicit tmat4x4(tmat3x3<T> const & x);
			explicit tmat4x4(tmat2x3<T> const & x);
			explicit tmat4x4(tmat3x2<T> const & x);
			explicit tmat4x4(tmat2x4<T> const & x);
			explicit tmat4x4(tmat4x2<T> const & x);
			explicit tmat4x4(tmat3x4<T> const & x);
			explicit tmat4x4(tmat4x3<T> const & x);

			// Accesses
			col_type & operator[](size_type i);
			col_type const & operator[](size_type i) const;

			// Unary updatable operators
			tmat4x4<T> & operator=  (tmat4x4<T> const & m);
			template <typename U>
			tmat4x4<T> & operator=  (tmat4x4<U> const & m);
			template <typename U>
			tmat4x4<T> & operator+= (U const & s);
			template <typename U>
			tmat4x4<T> & operator+= (tmat4x4<U> const & m);
			template <typename U>
			tmat4x4<T> & operator-= (U const & s);
			template <typename U>
			tmat4x4<T> & operator-= (tmat4x4<U> const & m);
			template <typename U>
			tmat4x4<T> & operator*= (U const & s);
			template <typename U>
			tmat4x4<T> & operator*= (tmat4x4<U> const & m);
			template <typename U>
			tmat4x4<T> & operator/= (U const & s);
			template <typename U>
			tmat4x4<T> & operator/= (tmat4x4<U> const & m);
			tmat4x4<T> & operator++ ();
			tmat4x4<T> & operator-- ();
		};

		// Binary operators
		template <typename T> 
		tmat4x4<T> operator+ (
			tmat4x4<T> const & m, 
			typename tmat4x4<T>::value_type const & s);

		template <typename T> 
		tmat4x4<T> operator+ (
			typename tmat4x4<T>::value_type const & s, 
			tmat4x4<T> const & m);

		template <typename T> 
		tmat4x4<T> operator+ (
			tmat4x4<T> const & m1, 
			tmat4x4<T> const & m2);
	    
		template <typename T> 
		tmat4x4<T> operator- (
			tmat4x4<T> const & m, 
			typename tmat4x4<T>::value_type const & s);

		template <typename T> 
		tmat4x4<T> operator- (
			typename tmat4x4<T>::value_type const & s, 
			tmat4x4<T> const & m);

		template <typename T> 
		tmat4x4<T> operator- (
			tmat4x4<T> const & m1, 
			tmat4x4<T> const & m2);

		template <typename T> 
		tmat4x4<T> operator* (
			tmat4x4<T> const & m, 
			typename tmat4x4<T>::value_type const & s);

		template <typename T> 
		tmat4x4<T> operator* (
			typename tmat4x4<T>::value_type const & s, 
			tmat4x4<T> const & m);

		template <typename T> 
		typename tmat4x4<T>::col_type operator* (
			tmat4x4<T> const & m, 
			typename tmat4x4<T>::row_type const & v);

		template <typename T> 
		typename tmat4x4<T>::row_type operator* (
			typename tmat4x4<T>::col_type const & v, 
			tmat4x4<T> const & m);

		template <typename T> 
		tmat4x4<T> operator* (
			tmat4x4<T> const & m1, 
			tmat4x4<T> const & m2);

		template <typename T> 
		tmat4x4<T> operator/ (
			tmat4x4<T> const & m, 
			typename tmat4x4<T>::value_type const & s);

		template <typename T> 
		tmat4x4<T> operator/ (
			typename tmat4x4<T>::value_type const & s, 
			tmat4x4<T> const & m);

		template <typename T> 
		typename tmat4x4<T>::col_type operator/ (
			tmat4x4<T> const & m, 
			typename tmat4x4<T>::row_type const & v);

		template <typename T> 
		typename tmat4x4<T>::row_type operator/ (
			typename tmat4x4<T>::col_type & v, 
			tmat4x4<T> const & m);

		template <typename T> 
		tmat4x4<T> operator/ (
			tmat4x4<T> const & m1, 
			tmat4x4<T> const & m2);

		// Unary constant operators
		template <typename T> 
		tmat4x4<T> const operator-  (
			tmat4x4<T> const & m);

		template <typename T> 
		tmat4x4<T> const operator-- (
			tmat4x4<T> const & m, int);

		template <typename T> 
		tmat4x4<T> const operator++ (
			tmat4x4<T> const & m, int);

	} //namespace detail

	namespace core{
	namespace type{

	namespace precision
	{
		//! 4 columns of 4 components matrix of low precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		//! \ingroup core_precision
		typedef detail::tmat4x4<lowp_float>		lowp_mat4x4;
		//! 4 columns of 4 components matrix of medium precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		//! \ingroup core_precision
		typedef detail::tmat4x4<mediump_float>	mediump_mat4x4;
		//! 4 columns of 4 components matrix of high precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		//! \ingroup core_precision
		typedef detail::tmat4x4<highp_float>	highp_mat4x4;
	}
	//namespace precision

	}//namespace type
	}//namespace core
} //namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat4x4.inl"
#endif

#endif //glm_core_type_mat4x4
