///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-04-19
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_major_storage.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_matrix_major_storage
#define glm_gtx_matrix_major_storage

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_matrix_major_storage extension included")
#endif

namespace glm
{
	namespace gtx{
	//! GLM_GTX_matrix_major_storage: Build matrices with specific matrix order, row or column
	namespace matrix_major_storage
	{
		/// \addtogroup gtx_matrix_major_storage
		///@{

		//! Build a row major matrix from row vectors.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat2x2<T> rowMajor2(
			const detail::tvec2<T>& v1, 
			const detail::tvec2<T>& v2);
		
		//! Build a row major matrix from other matrix.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat2x2<T> rowMajor2(
			const detail::tmat2x2<T>& m);

		//! Build a row major matrix from row vectors.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat3x3<T> rowMajor3(
			const detail::tvec3<T>& v1, 
			const detail::tvec3<T>& v2, 
			const detail::tvec3<T>& v3);

		//! Build a row major matrix from other matrix.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat3x3<T> rowMajor3(
			const detail::tmat3x3<T>& m);

		//! Build a row major matrix from row vectors.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat4x4<T> rowMajor4(
			const detail::tvec4<T>& v1, 
			const detail::tvec4<T>& v2,
			const detail::tvec4<T>& v3, 
			const detail::tvec4<T>& v4);

		//! Build a row major matrix from other matrix.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat4x4<T> rowMajor4(
			const detail::tmat4x4<T>& m);

		//! Build a column major matrix from column vectors.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat2x2<T> colMajor2(
			const detail::tvec2<T>& v1, 
			const detail::tvec2<T>& v2);
		
		//! Build a column major matrix from other matrix.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat2x2<T> colMajor2(
			const detail::tmat2x2<T>& m);

		//! Build a column major matrix from column vectors.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat3x3<T> colMajor3(
			const detail::tvec3<T>& v1, 
			const detail::tvec3<T>& v2, 
			const detail::tvec3<T>& v3);
		
		//! Build a column major matrix from other matrix.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat3x3<T> colMajor3(
			const detail::tmat3x3<T>& m);
		
		//! Build a column major matrix from column vectors.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat4x4<T> colMajor4(
			const detail::tvec4<T>& v1, 
			const detail::tvec4<T>& v2, 
			const detail::tvec4<T>& v3, 
			const detail::tvec4<T>& v4);
				
		//! Build a column major matrix from other matrix.
		//! From GLM_GTX_matrix_major_storage extension.
		template <typename T> 
		detail::tmat4x4<T> colMajor4(
			const detail::tmat4x4<T>& m);

		///@}
		
	}//namespace matrix_major_storage
	}//namespace gtx
}//namespace glm

#include "matrix_major_storage.inl"

namespace glm{using namespace gtx::matrix_major_storage;}

#endif//glm_gtx_matrix_major_storage
