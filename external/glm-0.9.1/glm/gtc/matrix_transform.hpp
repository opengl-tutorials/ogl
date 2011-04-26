///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-04-29
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_transform.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_matrix_operation
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_matrix_transform
#define glm_gtc_matrix_transform

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_matrix_transform extension included")
#endif

namespace glm
{
	namespace test{
		bool main_gtc_matrix_transform();
	}//namespace test

	namespace gtc{
	//! GLM_GTC_matrix_transform extension: Add transformation matrices
	namespace matrix_transform
	{
		/// \addtogroup gtc_matrix_transform
		///@{

		//! Builds a translation 4 * 4 matrix created from a vector of 3 components.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> translate(
			detail::tmat4x4<T> const & m,
			detail::tvec3<T> const & v);
		
		//! Builds a rotation 4 * 4 matrix created from an axis vector and an angle expressed in degrees. 
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> rotate(
			detail::tmat4x4<T> const & m,
			T const & angle, 
			detail::tvec3<T> const & v);

		//! Builds a scale 4 * 4 matrix created from 3 scalars. 
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> scale(
			detail::tmat4x4<T> const & m,
			detail::tvec3<T> const & v);

		//! Creates a matrix for an orthographic parallel viewing volume.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> ortho(
			T const & left, 
			T const & right, 
			T const & bottom, 
			T const & top, 
			T const & zNear, 
			T const & zFar);

		//! Creates a matrix for projecting two-dimensional coordinates onto the screen.
		//! From GLM_GTC_matrix_transform extension.
        template <typename T> 
		detail::tmat4x4<T> ortho(
			T const & left, 
			T const & right, 
			T const & bottom, 
			T const & top);

		//! Creates a frustum matrix.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> frustum(
			T const & left, 
			T const & right, 
			T const & bottom, 
			T const & top, 
			T const & nearVal, 
			T const & farVal);

		//! Creates a matrix for a symetric perspective-view frustum.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> perspective(
			T const & fovy, 
			T const & aspect, 
			T const & zNear, 
			T const & zFar);

		//! Builds a perspective projection matrix based on a field of view
		//! From GLM_GTC_matrix_transform extension.
		template <typename valType> 
		detail::tmat4x4<valType> perspectiveFov(
			valType const & fov, 
			valType const & width, 
			valType const & height, 
			valType const & zNear, 
			valType const & zFar);

		//! Creates a matrix for a symmetric perspective-view frustum with far plane at infinite .
		//! From GLM_GTC_matrix_transform extension.
        template <typename T> 
		detail::tmat4x4<T> infinitePerspective(
			T fovy, T aspect, T zNear);

		//! Creates a matrix for a symmetric perspective-view frustum with far plane at infinite for graphics hardware that doesn't support depth clamping.
		//! From GLM_GTC_matrix_transform extension.
        template <typename T> 
		detail::tmat4x4<T> tweakedInfinitePerspective(
			T fovy, T aspect, T zNear);

		//! Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T, typename U> 
		detail::tvec3<T> project(
			detail::tvec3<T> const & obj, 
			detail::tmat4x4<T> const & model, 
			detail::tmat4x4<T> const & proj, 
			detail::tvec4<U> const & viewport);

		//! Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T, typename U> 
		detail::tvec3<T> unProject(
			detail::tvec3<T> const & win, 
			detail::tmat4x4<T> const & model, 
			detail::tmat4x4<T> const & proj, 
			detail::tvec4<U> const & viewport);

		//! Define a picking region
		//! From GLM_GTC_matrix_transform extension.
		template <typename T, typename U> 
		detail::tmat4x4<T> pickMatrix(
			detail::tvec2<T> const & center, 
			detail::tvec2<T> const & delta, 
			detail::tvec4<U> const & viewport);

		//! Build a look at view matrix.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> lookAt(
			detail::tvec3<T> const & eye, 
			detail::tvec3<T> const & center, 
			detail::tvec3<T> const & up);

		///@}
	}//namespace matrix_transform
	}//namespace gtc
}//namespace glm

#include "matrix_transform.inl"

namespace glm{using namespace gtc::matrix_transform;}

#endif//glm_gtc_matrix_transform
