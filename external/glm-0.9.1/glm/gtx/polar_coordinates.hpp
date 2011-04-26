///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-06
// Updated : 2009-05-01
// Licence : This source is under MIT License
// File    : glm/gtx/polar_coordinates.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_polar_coordinates
#define glm_gtx_polar_coordinates

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_polar_coordinates extension included")
#endif

namespace glm
{
	namespace gtx{
	//! GLM_GTX_polar_coordinates extension: Conversion from Euclidean space to polar space and revert.
	namespace polar_coordinates
	{
		/// \addtogroup gtx_polar_coordinates
		///@{

		//! Convert Euclidean to Polar coordinates, x is the xz distance, y, the latitude and z the longitude.
		//! From GLM_GTX_polar_coordinates extension.
		template <typename T> 
		detail::tvec3<T> polar(const detail::tvec3<T>& euclidean);

		//! Convert Polar to Euclidean coordinates.
		//! From GLM_GTX_polar_coordinates extension.
		template <typename T> 
		detail::tvec3<T> euclidean(const detail::tvec3<T>& polar);

		///@}

	}//namespace polar_coordinates
	}//namespace gtx
}//namespace glm

#include "polar_coordinates.inl"

namespace glm{using namespace gtx::polar_coordinates;}

#endif//glm_gtx_polar_coordinates
