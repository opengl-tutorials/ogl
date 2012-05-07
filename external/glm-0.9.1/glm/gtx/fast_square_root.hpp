///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-04
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/fast_square_root.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////
// Note:
// - Sqrt optimisation based on Newton's method, 
// www.gamedev.net/community/forums/topic.asp?topic id=139956
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_fast_square_root
#define glm_gtx_fast_square_root

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_fast_square_root extension included")
#endif

namespace glm
{
   	namespace test{
		void main_gtx_fast_square_root();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_fast_square_root extension: Fast but less accurate implementations of square root based functions.
	namespace fast_square_root
	{
		/// \addtogroup gtx_fast_square_root
		///@{

		//! Faster than the common sqrt function but less accurate.
		//! From GLM_GTX_fast_square_root extension.
		template <typename genType> 
		genType fastSqrt(genType const & x);

		//! Faster than the common inversesqrt function but less accurate.
		//! From GLM_GTX_fast_square_root extension.
		template <typename genType> 
		genType fastInverseSqrt(genType const & x);
		
		//! Faster than the common length function but less accurate.
		//! From GLM_GTX_fast_square_root extension.
		template <typename genType> 
		typename genType::value_type fastLength(genType const & x);

		//! Faster than the common distance function but less accurate.
		//! From GLM_GTX_fast_square_root extension.
		template <typename genType> 
		typename genType::value_type fastDistance(genType const & x, genType const & y);

		//! Faster than the common normalize function but less accurate.
		//! From GLM_GTX_fast_square_root extension.
		template <typename genType> 
		genType fastNormalize(genType const & x);

		///@}

	}//namespace fast_square_root
	}//	namespace gtx
}//namespace glm

#include "fast_square_root.inl"

namespace glm{using namespace gtx::fast_square_root;}

#endif//glm_gtx_fast_square_root
