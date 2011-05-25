///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-08-05
// Updated : 2010-02-05
// Licence : This source is under MIT License
// File    : glm/core/type_mat3x4.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat3x4
#define glm_core_type_mat3x4

#include "type_mat.hpp"

namespace glm
{
	namespace test
	{
		void main_mat3x4();
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

		//! \brief Template for 3 columns and 4 rows matrix of floating-point numbers.
		//! \ingroup core_template
		template <typename T> 
		struct tmat3x4
		{
			enum ctor{null};
			typedef T value_type;
			typedef std::size_t size_type;
			typedef tvec4<T> col_type;
			typedef tvec3<T> row_type;
			static size_type col_size();
			static size_type row_size();

			typedef tmat3x4<T> type;
			typedef tmat4x3<T> transpose_type;

		private:
			// Data 
			col_type value[3];

		public:
			// Constructors
			tmat3x4();
			tmat3x4(tmat3x4 const & m);

			explicit tmat3x4(
				ctor Null);
			explicit tmat3x4(
				value_type const & s);
			explicit tmat3x4(
				value_type const & x0, value_type const & y0, value_type const & z0, value_type const & w0,
				value_type const & x1, value_type const & y1, value_type const & z1, value_type const & w1,
				value_type const & x2, value_type const & y2, value_type const & z2, value_type const & w2);
			explicit tmat3x4(
				col_type const & v0, 
				col_type const & v1,
				col_type const & v2);

			// Conversion
			template <typename U> 
			explicit tmat3x4(tmat3x4<U> const & m);

			explicit tmat3x4(tmat2x2<T> const & x);
			explicit tmat3x4(tmat3x3<T> const & x);
			explicit tmat3x4(tmat4x4<T> const & x);
			explicit tmat3x4(tmat2x3<T> const & x);
			explicit tmat3x4(tmat3x2<T> const & x);
			explicit tmat3x4(tmat2x4<T> const & x);
			explicit tmat3x4(tmat4x2<T> const & x);
			explicit tmat3x4(tmat4x3<T> const & x);

			// Accesses
			col_type & operator[](size_type i);
			col_type const & operator[](size_type i) const;

			// Unary updatable operators
			tmat3x4<T> & operator=  (tmat3x4<T> const & m);
			template <typename U> 
			tmat3x4<T> & operator=  (tmat3x4<U> const & m);
			template <typename U> 
			tmat3x4<T> & operator+= (U const & s);
			template <typename U> 
			tmat3x4<T> & operator+= (tmat3x4<U> const & m);
			template <typename U> 
			tmat3x4<T> & operator-= (U const & s);
			template <typename U> 
			tmat3x4<T> & operator-= (tmat3x4<U> const & m);
			template <typename U> 
			tmat3x4<T> & operator*= (U const & s);
			template <typename U> 
			tmat3x4<T> & operator*= (tmat3x4<U> const & m);
			template <typename U> 
			tmat3x4<T> & operator/= (U const & s);

			tmat3x4<T> & operator++ ();
			tmat3x4<T> & operator-- ();
		};

		// Binary operators
		template <typename T> 
		tmat3x4<T> operator+ (
			tmat3x4<T> const & m, 
			typename tmat3x4<T>::value_type const & s);
	    
		template <typename T> 
		tmat3x4<T> operator+ (
			tmat3x4<T> const & m1, 
			tmat3x4<T> const & m2);
	    
		template <typename T> 
		tmat3x4<T> operator- (
			tmat3x4<T> const & m, 
			typename tmat3x4<T>::value_type const & s);

		template <typename T> 
		tmat3x4<T> operator- (
			tmat3x4<T> const & m1, 
			tmat3x4<T> const & m2);

		template <typename T> 
		tmat3x4<T> operator* (
			tmat3x4<T> const & m, 
			typename tmat3x4<T>::value_type const & s);

		template <typename T> 
		tmat3x4<T> operator* (
			typename tmat3x4<T>::value_type const & s, 
			tmat3x4<T> const & m);

		template <typename T>
		typename tmat3x4<T>::col_type operator* (
			tmat3x4<T> const & m, 
			typename tmat3x4<T>::row_type const & v);

		template <typename T> 
		typename tmat3x4<T>::row_type operator* (
			typename tmat3x4<T>::col_type const & v, 
			tmat3x4<T> const & m);

		template <typename T>
		tmat4x4<T> operator* (
			tmat3x4<T> const & m1, 
			tmat4x3<T> const & m2);

		template <typename T> 
		tmat3x4<T> operator/ (
			tmat3x4<T> const & m, 
			typename tmat3x4<T>::value_type const & s);

		template <typename T> 
		tmat3x4<T> operator/ (
			typename tmat3x4<T>::value_type const & s, 
			tmat3x4<T> const & m);

		// Unary constant operators
		template <typename T> 
		tmat3x4<T> const operator-  (
			tmat3x4<T> const & m);

		template <typename T> 
		tmat3x4<T> const operator-- (
			tmat3x4<T> const & m, 
			int);

		template <typename T> 
		tmat3x4<T> const operator++ (
			tmat3x4<T> const & m, 
			int);

	} //namespace detail

	namespace core{
	namespace type{

	namespace precision
	{
		//! 3 columns of 4 components matrix of low precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		typedef detail::tmat3x4<lowp_float>		lowp_mat3x4;
		//! 3 columns of 4 components matrix of medium precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		typedef detail::tmat3x4<mediump_float>	mediump_mat3x4;
		//! 3 columns of 4 components matrix of high precision floating-point numbers.
		//! There is no guarantee on the actual precision.
		//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
		typedef detail::tmat3x4<highp_float>	highp_mat3x4;
	}
	//namespace precision

	}//namespace type
	}//namespace core
} //namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat3x4.inl"
#endif

#endif //glm_core_type_mat3x4
