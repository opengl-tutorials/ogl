///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-04-21
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/inertia.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_inertia
#define glm_gtx_inertia

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_inertia extension included")
#endif

namespace glm
{
	namespace gtx{
	//! GLM_GTX_inertia extension: Create inertia matrices
	namespace inertia
	{
		/// \addtogroup gtx_inertia
		///@{

		//! Build an inertia matrix for a box.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat3x3<T> boxInertia3(
			const T Mass, 
			const detail::tvec3<T>& Scale);
		
		//! Build an inertia matrix for a box.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat4x4<T> boxInertia4(
			const T Mass, 
			const detail::tvec3<T>& Scale);
		
		//! Build an inertia matrix for a disk.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat3x3<T> diskInertia3(
			const T Mass, 
			const T Radius);

		//! Build an inertia matrix for a disk.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat4x4<T> diskInertia4(
			const T Mass, 
			const T Radius);

		//! Build an inertia matrix for a ball.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat3x3<T> ballInertia3(
			const T Mass, 
			const T Radius);
		
		//! Build an inertia matrix for a ball.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat4x4<T> ballInertia4(
			const T Mass, 
			const T Radius);

		//! Build an inertia matrix for a sphere.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat3x3<T> sphereInertia3(
			const T Mass, 
			const T Radius);

		//! Build an inertia matrix for a sphere.
		//! From GLM_GTX_inertia extension.
		template <typename T> 
		detail::tmat4x4<T> sphereInertia4(
			const T Mass, 
			const T Radius);

		///@}

	}//namespace inertia
	}//namespace gtx
}//namespace glm

#include "inertia.inl"

namespace glm{using namespace gtx::inertia;}

#endif//glm_gtx_inertia
