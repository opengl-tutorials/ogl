///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-03
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/func_matrix.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_matrix
#define glm_core_func_matrix

namespace glm
{
	namespace test{
		void main_core_func_matrix();
	}//namespace test

	namespace core{
	namespace function{
	//! Define all matrix functions from Section 8.5 of GLSL 1.30.8 specification. Included in glm namespace.
	namespace matrix{

	/// \addtogroup core_funcs
	///@{

	//! Multiply matrix x by matrix y component-wise, i.e., 
	//! result[i][j] is the scalar product of x[i][j] and y[i][j].
	//! (From GLSL 1.30.08 specification, section 8.5)
	template <typename matType> 
	matType matrixCompMult(
		matType const & x, 
		matType const & y);

	//! Treats the first parameter c as a column vector 
	//! and the second parameter r as a row vector
	//! and does a linear algebraic matrix multiply c * r.
	//! (From GLSL 1.30.08 specification, section 8.5)
	template <typename vecType, typename matType> 
	matType outerProduct(
		vecType const & c, 
		vecType const & r);

	//! Returns the transposed matrix of x
	//! (From GLSL 1.30.08 specification, section 8.5)
	template <typename matType> 
	typename matType::transpose_type transpose(
		matType const & x);
	
	//! Return the determinant of a mat2 matrix. 
	//! (From GLSL 1.50.09 specification, section 8.5)..
	template <typename T> 
	typename detail::tmat2x2<T>::value_type determinant(
		detail::tmat2x2<T> const & m);

	//! Return the determinant of a mat3 matrix. 
	//! (From GLSL 1.50.09 specification, section 8.5).
	template <typename T> 
	typename detail::tmat3x3<T>::value_type determinant(
		detail::tmat3x3<T> const & m);

	//! Return the determinant of a mat4 matrix. 
	//! (From GLSL 1.50.09 specification, section 8.5).
	template <typename T> 
	typename detail::tmat4x4<T>::value_type determinant(
		detail::tmat4x4<T> const & m);

	//! Return the inverse of a mat2 matrix. 
	//! (From GLSL 1.40.07 specification, section 8.5).
	template <typename T> 
	detail::tmat2x2<T> inverse(
		detail::tmat2x2<T> const & m);

	//! Return the inverse of a mat3 matrix. 
	//! (From GLSL 1.40.07 specification, section 8.5).
	template <typename T> 
	detail::tmat3x3<T> inverse(
		detail::tmat3x3<T> const & m);

	//! Return the inverse of a mat4 matrix. 
	//! (From GLSL 1.40.07 specification, section 8.5).
	template <typename T> 
	detail::tmat4x4<T> inverse(
		detail::tmat4x4<T> const & m);

	///@}

	}//namespace matrix
	}//namespace function
	}//namespace core

	using namespace core::function::matrix;
}//namespace glm

#include "func_matrix.inl"

#endif//glm_core_func_matrix
