///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-24
// Updated : 2008-10-24
// Licence : This source is under MIT License
// File    : glm/gtx/log_base.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_log_base
#define glm_gtx_log_base

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_log_base extension included")
#endif

namespace glm
{
   	namespace test{
		void main_ext_gtx_log_base();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_log_base extension: Logarithm for any base. base can be a vector or a scalar.
	namespace log_base
	{
		/// \addtogroup gtx_log_base
		///@{

		//! Logarithm for any base.
		//! From GLM_GTX_log_base.
		template <typename genType> 
		genType log(
			genType const & x, 
			genType const & base);

		///@}

	}//namespace extend
	}//namespace gtx
}//namespace glm

#include "log_base.inl"

namespace glm{using namespace gtx::log_base;}

#endif//glm_gtx_log_base
