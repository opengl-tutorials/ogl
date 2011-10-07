///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtx/transform.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_matric_transform
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_transform
#define glm_gtx_transform

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_transform.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_transform extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_transform();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_transform extension: Add transformation matrices
	namespace transform
	{
		using namespace gtc::matrix_transform; 

		/// \addtogroup gtx_transform
		///@{

		//! Builds a translation 4 * 4 matrix created from 3 scalars.
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> translate(
			T x, T y, T z);
		
		//! Transforms a matrix with a translation 4 * 4 matrix created from 3 scalars. 
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> translate(
			detail::tmat4x4<T> const & m, 
			T x, T y, T z);
		
		//! Transforms a matrix with a translation 4 * 4 matrix created from 3 scalars. 
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> translate(
			detail::tvec3<T> const & v);

		//! Builds a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in degrees. 
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> rotate(
			T angle, 
			T x, T y, T z);

		//! Builds a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in degrees. 
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> rotate(
			T angle, 
			detail::tvec3<T> const & v);

		//! Transforms a matrix with a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in degrees. 
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> rotate(
			detail::tmat4x4<T> const & m, 
			T angle, 
			T x, T y, T z);
		
		//! Builds a scale 4 * 4 matrix created from 3 scalars. 
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> scale(
			T x, T y, T z);
		
		//! Transforms a matrix with a scale 4 * 4 matrix created from 3 scalars.
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> scale(
			detail::tmat4x4<T> const & m, 
			T x, T y, T z);

		//! Transforms a matrix with a scale 4 * 4 matrix created from a vector of 3 components.
		//! From GLM_GTX_transform extension.
		template <typename T> 
		detail::tmat4x4<T> scale(
			detail::tvec3<T> const & v);

		///@}

	}//namespace transform
	}//namespace gtx
}//namespace glm

#include "transform.inl"

namespace glm{using namespace gtx::transform;}

#endif//glm_gtx_transform
