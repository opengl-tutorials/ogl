///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-11-25
// Updated : 2009-11-25
// Licence : This source is under MIT License
// File    : glm/gtx/wrap.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_wrap
#define glm_gtx_wrap

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_wrap extension included")
#endif

namespace glm
{
	namespace test{
		bool main_gtx_wrap();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_wrap: Wrapping mode using my texture samping.
	namespace wrap
	{
		/// \addtogroup gtx_wrap
		///@{

		//! Simulate GL_CLAMP OpenGL wrap mode
		//! From GLM_GTX_wrap extension.
		template <typename genType> 
		genType clamp(genType const & Texcoord);

		//! Simulate GL_REPEAT OpenGL wrap mode
		//! From GLM_GTX_wrap extension.
		template <typename genType> 
		genType repeat(genType const & Texcoord);

		//! Simulate GL_MIRROR_REPEAT OpenGL wrap mode
		//! From GLM_GTX_wrap extension.
		template <typename genType> 
		genType mirrorRepeat(genType const & Texcoord);

		///@}

	}//namespace wrap
	}//namespace gtx
}//namespace glm

#include "wrap.inl"

namespace glm{using namespace gtx::wrap;}

#endif//glm_img_wrap
