///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_cross_product.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_matrix_cross_product
#define glm_gtx_matrix_cross_product

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_matrix_cross_product extension included")
#endif

namespace glm
{
   	namespace test{
		void main_gtx_matrix_cross_product();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_matrix_cross_product: Build cross product matrices
	namespace matrix_cross_product
	{
		/// \addtogroup gtx_matrix_cross_product
		///@{

		//! Build a cross product matrix.
		//! From GLM_GTX_matrix_cross_product extension.
		template <typename T> 
		detail::tmat3x3<T> matrixCross3(
			detail::tvec3<T> const & x);
		
		//! Build a cross product matrix.
		//! From GLM_GTX_matrix_cross_product extension.
		template <typename T> 
		detail::tmat4x4<T> matrixCross4(
			detail::tvec3<T> const & x);

		///@}

	}//namespace matrix_cross_product
	}//namespace gtx
}//namespace glm

#include "matrix_cross_product.inl"

namespace glm{using namespace gtx::matrix_cross_product;}

#endif//glm_gtx_matrix_cross_product
