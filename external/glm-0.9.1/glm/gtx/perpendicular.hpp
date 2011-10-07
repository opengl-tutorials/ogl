///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-03-06
// Licence : This source is under MIT License
// File    : glm/gtx/perpendicular.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_projection
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_perpendicular
#define glm_gtx_perpendicular

// Dependency:
#include "../glm.hpp"
#include "../gtx/projection.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_perpendicular extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_perpendicular();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_perpendicular extension: Perpendicular of a vector from other one
    namespace perpendicular
    {
		/// \addtogroup gtx_perpendicular
		///@{

		//! Projects x a perpendicular axis of Normal.
		//! From GLM_GTX_perpendicular extension.
		template <typename T> 
		detail::tvec2<T> perp(
			detail::tvec2<T> const & x, 
			detail::tvec2<T> const & Normal);

        //! Projects x a perpendicular axis of Normal.
		//! From GLM_GTX_perpendicular extension.
		template <typename T> 
		detail::tvec3<T> perp(
			detail::tvec3<T> const & x, 
			detail::tvec3<T> const & Normal);

        //! Projects x a perpendicular axis of Normal.
		//! From GLM_GTX_perpendicular extension.
		template <typename T> 
		detail::tvec4<T> perp(
			detail::tvec4<T> const & x, 
			detail::tvec4<T> const & Normal);


		///@}
		
    }//namespace perpendicular
    }//namespace gtx
}//namespace glm

#include "perpendicular.inl"

namespace glm{using namespace gtx::perpendicular;}

#endif//glm_gtx_perpendicular
