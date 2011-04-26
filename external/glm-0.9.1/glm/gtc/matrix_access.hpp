///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-27
// Updated : 2010-11-12
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_access.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_matrix_access
#define glm_gtc_matrix_access

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_matrix_access extension included")
#endif

namespace glm{
namespace gtc{
//! GLM_GTC_matrix_access extension: Set a column or a row of a matrix
namespace matrix_access
{
	/// \addtogroup gtc_matrix_access
	///@{

	//! Get a specific row of a matrix.
	//! From GLM_GTC_matrix_access extension.
	template <typename genType> 
	typename genType::row_type row(
		genType const & m, 
		int index);

	//! Set a specific row to a matrix.
	//! From GLM_GTC_matrix_access extension.
    template <typename genType> 
	genType row(
		genType const & m, 
		int index, 
		typename genType::row_type const & x);

	//! Get a specific column of a matrix.
	//! From GLM_GTC_matrix_access extension.
	template <typename genType> 
	typename genType::col_type column(
		genType const & m, 
		int index);

	 //! Set a specific column to a matrix.
	 //! From GLM_GTC_matrix_access extension.
	template <typename genType> 
	genType column(
		genType const & m, 
		int index, 
		typename genType::col_type const & x);

	///@}

}//namespace matrix_access
}//namespace gtc
}//namespace glm

#include "matrix_access.inl"

namespace glm{using namespace gtc::matrix_access;}

#endif//glm_gtc_matrix_access
