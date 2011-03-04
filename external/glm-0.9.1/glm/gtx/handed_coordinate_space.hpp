///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/handed_coordinate_space.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_handed_coordinate_space
#define glm_gtx_handed_coordinate_space

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_handed_coordinate_space extension included")
#endif

namespace glm
{
	namespace gtx{
	//! GLM_GTX_handed_coordinate_space extension: To know if a set of three basis vectors defines a right or left-handed coordinate system.
	namespace handed_coordinate_space
	{
		/// \addtogroup gtx_handed_coordinate_space
		///@{

		//! Return if a trihedron right handed or not.
		//! From GLM_GTX_handed_coordinate_space extension.
		template <typename T> 
		bool rightHanded(
			detail::tvec3<T> const & tangent, 
			detail::tvec3<T> const & binormal, 
			detail::tvec3<T> const & normal);

		//! Return if a trihedron left handed or not.
		//! From GLM_GTX_handed_coordinate_space extension.
		template <typename T> 
		bool leftHanded(
			detail::tvec3<T> const & tangent, 
			detail::tvec3<T> const & binormal, 
			detail::tvec3<T> const & normal);

		///@}

	}//namespace handed_coordinate_space
	}//namespace gtx
}//namespace glm

#include "handed_coordinate_space.inl"

namespace glm{using namespace gtx::handed_coordinate_space;}

#endif//glm_gtx_handed_coordinate_space
