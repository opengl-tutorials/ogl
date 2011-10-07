///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-04-03
// Updated : 2008-09-17
// Licence : This source is under MIT License
// File    : glm/gtx/mixed_product.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_mixed_product
#define glm_gtx_mixed_product

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_mixed_product extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_matrix_selection();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_mixed_product extension: Mixed product of 3 vectors.
	namespace mixed_product
	{
		/// \addtogroup gtx_mixed_product
		///@{

		//! \brief Mixed product of 3 vectors (from GLM_GTX_mixed_product extension)
		template <typename valType> 
		valType mixedProduct(
			detail::tvec3<valType> const & v1, 
			detail::tvec3<valType> const & v2, 
			detail::tvec3<valType> const & v3);

		///@}
	}//namespace mixed_product
	}//namespace gtx
}//namespace glm

#include "mixed_product.inl"

namespace glm{using namespace gtx::mixed_product;}

#endif//glm_gtx_mixed_product
