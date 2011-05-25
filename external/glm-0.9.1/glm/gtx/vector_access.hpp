///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-16
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/vector_access.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_vector_access
#define glm_gtx_vector_access

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_vector_access extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_vector_access();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_vector_access extension: Function to set values to vectors
    namespace vector_access
    {
		/// \addtogroup gtx_vector_access
		///@{

		//! Set values to a 2 components vector.
		//! From GLM_GTX_vector_access extension.
        template <typename valType> 
		void set(
			detail::tvec2<valType> & v, 
			valType const & x, 
			valType const & y);

		//! Set values to a 3 components vector.
		//! From GLM_GTX_vector_access extension.
        template <typename valType> 
		void set(
			detail::tvec3<valType> & v, 
			valType const & x, 
			valType const & y, 
			valType const & z);

		//! Set values to a 4 components vector.
		//! From GLM_GTX_vector_access extension.
        template <typename valType> 
		void set(
			detail::tvec4<valType> & v, 
			valType const & x, 
			valType const & y, 
			valType const & z, 
			valType const & w);

		///@}

    }//namespace vector_access
    }//namespace gtx
}//namespace glm

#include "vector_access.inl"

namespace glm{using namespace gtx::vector_access;}

#endif//glm_gtx_vector_access
