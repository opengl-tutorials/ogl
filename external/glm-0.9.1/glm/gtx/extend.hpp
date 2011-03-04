///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-07
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/extend.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_extend
#define glm_gtx_extend

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_extend extension included")
#endif

namespace glm
{
   	namespace test{
		void main_gtx_extend();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_extend extension: Extend a position from a source to a position at a defined length.
	namespace extend
	{
		/// \addtogroup gtx_extend
		///@{

		//! Extends of Length the Origin position using the (Source - Origin) direction.
		//! From GLM_GTX_extend extension.
		template <typename genType> 
		genType extend(
			genType const & Origin, 
			genType const & Source, 
			typename genType::value_type const Length);

		///@}

	}//namespace extend
	}//namespace gtx
}//namespace glm

#include "extend.inl"

namespace glm{using namespace gtx::extend;}

#endif//glm_gtx_extend
