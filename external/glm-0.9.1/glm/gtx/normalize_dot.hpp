//////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
//////////////////////////////////////////////////////////////////////////////////
// Created : 2007-09-28
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/normalize_dot.hpp
//////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_fast_square_root
//////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_normalize_dot
#define glm_gtx_normalize_dot

// Dependency:
#include "../glm.hpp"
#include "../gtx/fast_square_root.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_normalize_dot extension included")
#endif

namespace glm
{
	namespace gtx{
	//! GLM_GTX_normalize_dot extension: Dot product of vectors that need to be normalize with a single square root.
	namespace normalize_dot
	{
		using namespace gtx::fast_square_root;

		/// \addtogroup gtx_normalize_dot
		///@{

		//! Normalize parameters and returns the dot product of x and y.
		//! It's faster that dot(normalize(x), normalize(y)).
		//! From GLM_GTX_normalize_dot extension.
		template <typename genType> 
		typename genType::value_type normalizeDot(
			genType const & x, 
			genType const & y);

		//! Normalize parameters and returns the dot product of x and y.
		//! Faster that dot(fastNormalize(x), fastNormalize(y)).
		//! From GLM_GTX_normalize_dot extension.
		template <typename genType> 
		typename genType::value_type fastNormalizeDot(
			genType const & x, 
			genType const & y);

		///@}

	}//namespace normalize_dot
	}//namespace gtx
}//namespace glm

#include "normalize_dot.inl"

namespace glm{using namespace gtx::normalize_dot;}

#endif//glm_gtx_normalize_dot
