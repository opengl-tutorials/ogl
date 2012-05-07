///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-30
// Updated : 2008-10-05
// Licence : This source is under MIT License
// File    : glm/gtx/closest_point.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_closest_point
#define glm_gtx_closest_point

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_closest_point extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_closest_point();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_closest_point extension: Find the point on a straight line which is the closet of a point.
	namespace closest_point{

	/// \addtogroup gtx_closest_point
	///@{

	//! Find the point on a straight line which is the closet of a point. 
	//! From GLM_GTX_closest_point extension.
	template <typename T> 
	detail::tvec3<T> closestPointOnLine(
		detail::tvec3<T> const & point, 
		detail::tvec3<T> const & a, 
		detail::tvec3<T> const & b);
	///@}

	}//namespace closest_point
	}//namespace gtx
}//namespace glm

#include "closest_point.inl"

namespace glm{using namespace gtx::closest_point;}

#endif//glm_gtx_closest_point
