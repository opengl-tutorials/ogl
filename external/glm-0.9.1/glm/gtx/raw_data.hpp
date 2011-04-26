///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-11-19
// Updated : 2010-01-28
// Licence : This source is under MIT License
// File    : glm/gtx/raw_data.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_raw_data
#define glm_gtx_raw_data

// Dependency:
#include "../glm.hpp"
#include "../gtc/type_precision.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_raw_data extension included")
#endif

namespace glm{
namespace gtx
{
	//! GLM_GTX_raw_data extension: Projection of a vector to other one
    namespace raw_data
    {
		using namespace gtc::type_precision;

		/// \addtogroup gtx_raw_data
		///@{

		//! Type for byte numbers. 
		//! From GLM_GTX_raw_data extension.
		typedef uint8		byte;

		//! Type for word numbers. 
		//! From GLM_GTX_raw_data extension.
		typedef uint16		word;

		//! Type for dword numbers. 
		//! From GLM_GTX_raw_data extension.
		typedef uint32		dword;

		//! Type for qword numbers. 
		//! From GLM_GTX_raw_data extension.
		typedef uint64		qword;

		///@}
	}
}//namespace gtx
}//namespace glm

#include "raw_data.inl"

namespace glm{using namespace gtx::raw_data;}

#endif//glm_gtx_raw_data
