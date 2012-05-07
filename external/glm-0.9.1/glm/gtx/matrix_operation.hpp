///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-08-29
// Updated : 2009-08-29
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_operation.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_matrix_operation
#define glm_gtx_matrix_operation

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_matrix_operation extension included")
#endif

namespace glm
{
   	namespace test{
		void main_gtx_matrix_operation();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_matrix_operation: Build diagonal matrices
	namespace matrix_operation
	{
		/// \addtogroup gtx_matrix_operation
		///@{

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat2x2<valType> diagonal2x2(
			detail::tvec2<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat2x3<valType> diagonal2x3(
			detail::tvec2<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat2x4<valType> diagonal2x4(
			detail::tvec2<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat3x2<valType> diagonal3x2(
			detail::tvec2<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat3x3<valType> diagonal3x3(
			detail::tvec3<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat3x4<valType> diagonal3x4(
			detail::tvec3<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat4x2<valType> diagonal4x2(
			detail::tvec2<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat4x3<valType> diagonal4x3(
			detail::tvec3<valType> const & v);

		//! Build a diagonal matrix.
		//! From GLM_GTX_matrix_operation extension.
		template <typename valType> 
		detail::tmat4x4<valType> diagonal4x4(
			detail::tvec4<valType> const & v);

		///@}

	}//namespace matrix_operation
	}//namespace gtx
}//namespace glm

#include "matrix_operation.inl"

namespace glm{using namespace gtx::matrix_operation;}

#endif//glm_gtx_matrix_operation
