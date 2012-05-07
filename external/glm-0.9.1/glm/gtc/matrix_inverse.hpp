///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2010-12-13
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_inverse.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_matrix_inverse
#define glm_gtc_matrix_inverse

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_matrix_inverse extension included")
#endif

namespace glm{
namespace gtc{
//! GLM_GTC_matrix_inverse extension: Inverse matrix functions
namespace matrix_inverse
{
	/// \addtogroup gtc_matrix_inverse
	///@{

	//! Fast matrix inverse for affine matrix.
	//! From GLM_GTC_matrix_inverse extension.
	template <typename genType> 
	genType affineInverse(genType const & m);

	//! Compute the inverse transpose of a matrix.
	//! From GLM_GTC_matrix_inverse extension.
	template <typename genType> 
	inline typename genType::value_type inverseTranspose(
		genType const & m);

	///@}

}//namespace matrix_inverse
}//namespace gtc
}//namespace glm

#include "matrix_inverse.inl"

namespace glm{using namespace gtc::matrix_inverse;}

#endif//glm_gtc_matrix_inverse
