///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/orthonormalize.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_orthonormalize
#define glm_gtx_orthonormalize

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_orthonormalize extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_orthonormalize();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_orthonormalize extension: Orthonormalize matrices.
    namespace orthonormalize
    {
		/// \addtogroup gtx_orthonormalize
		///@{

		//! Returns the orthonormalized matrix of m.
		//! From GLM_GTX_orthonormalize extension.
		template <typename T> 
		detail::tmat3x3<T> orthonormalize(
			const detail::tmat3x3<T>& m);
		
        //! Orthonormalizes x according y.
		//! From GLM_GTX_orthonormalize extension.
		template <typename T> 
		detail::tvec3<T> orthonormalize(
			const detail::tvec3<T>& x, 
			const detail::tvec3<T>& y);

		///@}

    }//namespace orthonormalize
    }//namespace gtx
}//namespace glm

#include "orthonormalize.inl"

namespace glm{using namespace gtx::orthonormalize;}

#endif//glm_gtx_orthonormalize
