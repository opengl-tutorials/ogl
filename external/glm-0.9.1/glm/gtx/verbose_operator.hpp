///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-05-21
// Updated : 2007-05-21
// Licence : This source is under MIT License
// File    : glm/gtx/verbose_operator.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_verbose_operator
#define glm_gtx_verbose_operator

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_verbose_operator extension included")
#endif

namespace glm
{
	namespace test{
		void main_ext_gtx_verbose_operator();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_verbose_operator extension: Use words to replace operators
	namespace verbose_operator
	{
		/// \addtogroup gtx_verbose_operator
		///@{

		//! Addition of two values
		//! From GLM_GTX_verbose_operator extension.
		template <typename genTypeT, typename genTypeU> 
		genTypeT add(genTypeT const & a, genTypeU const & b);

		//! Substration of two values
		//! From GLM_GTX_verbose_operator extension.
		template <typename genTypeT, typename genTypeU> 
		genTypeT sub(genTypeT const & a, genTypeU const & b);

		//! Multiplication of two values
		//! From GLM_GTX_verbose_operator extension.
		template <typename genTypeT, typename genTypeU> 
		genTypeT mul(genTypeT const & a, genTypeU const & b);

		//! Division of two values
		//! From GLM_GTX_verbose_operator extension.
		template <typename genTypeT, typename genTypeU> 
		genTypeT div(genTypeT const & a, genTypeU const & b);

		//! Multiplication and addition of three values
		//! From GLM_GTX_verbose_operator extension.
		template <typename genTypeT, typename genTypeU, typename genTypeV> 
		genTypeT mad(genTypeT const & a, genTypeU const & b, genTypeV const & c);

		///@}
	}//namespace verbose_operator
	}//namespace gtx
}//namespace glm

#include "verbose_operator.inl"

namespace glm{using namespace gtx::verbose_operator;}

#endif//glm_gtx_verbose_operator
