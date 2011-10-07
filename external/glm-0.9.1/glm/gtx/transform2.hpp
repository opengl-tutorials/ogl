///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/transform2.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_transform
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_transform2
#define glm_gtx_transform2

// Dependency:
#include "../glm.hpp"
#include "../gtx/transform.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_transform2 extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_transform2();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_transform2 extension: Add extra transformation matrices
	namespace transform2
	{
		using namespace gtx::transform;

		/// \addtogroup gtx_transform2
		///@{

		//! Transforms a matrix with a shearing on X axis.
		//! From GLM_GTX_transform2 extension.
		template <typename T> 
		detail::tmat3x3<T> shearX2D(
			detail::tmat3x3<T> const & m, 
			T y);

		//! Transforms a matrix with a shearing on Y axis.
		//! From GLM_GTX_transform2 extension.
		template <typename T> 
		detail::tmat3x3<T> shearY2D(
			detail::tmat3x3<T> const & m, 
			T x);

		//! Transforms a matrix with a shearing on X axis
		//! From GLM_GTX_transform2 extension.
		template <typename T> 
		detail::tmat4x4<T> shearX3D(
			const detail::tmat4x4<T> & m,
			T y, 
			T z);
		
		//! Transforms a matrix with a shearing on Y axis.
		//! From GLM_GTX_transform2 extension.
		template <typename T> 
		detail::tmat4x4<T> shearY3D(
			const detail::tmat4x4<T> & m, 
			T x, 
			T z);
		
		//! Transforms a matrix with a shearing on Z axis. 
		//! From GLM_GTX_transform2 extension.
		template <typename T> 
		detail::tmat4x4<T> shearZ3D(
			const detail::tmat4x4<T> & m, 
			T x, 
			T y);

		//template <typename T> inline detail::tmat4x4<T> shear(const detail::tmat4x4<T> & m, shearPlane, planePoint, angle)
		// Identity + tan(angle) * cross(Normal, OnPlaneVector)     0
		// - dot(PointOnPlane, normal) * OnPlaneVector              1

		// Reflect functions seem to don't work
		//template <typename T> detail::tmat3x3<T> reflect2D(const detail::tmat3x3<T> & m, const detail::tvec3<T>& normal){return reflect2DGTX(m, normal);}									//!< \brief Build a reflection matrix (from GLM_GTX_transform2 extension)
		//template <typename T> detail::tmat4x4<T> reflect3D(const detail::tmat4x4<T> & m, const detail::tvec3<T>& normal){return reflect3DGTX(m, normal);}									//!< \brief Build a reflection matrix (from GLM_GTX_transform2 extension)
		
		//! Build planar projection matrix along normal axis.
		//! From GLM_GTX_transform2 extension.
		template <typename T> 
		detail::tmat3x3<T> proj2D(
			const detail::tmat3x3<T> & m, 
			const detail::tvec3<T>& normal);
				
		//! Build planar projection matrix along normal axis.
		//! From GLM_GTX_transform2 extension.
		template <typename T> 
		detail::tmat4x4<T> proj3D(
			const detail::tmat4x4<T> & m, 
			const detail::tvec3<T>& normal);

		//! Build a scale bias matrix. 
		//! From GLM_GTX_transform2 extension.
		template <typename valType> 
		detail::tmat4x4<valType> scaleBias(
			valType scale, 
			valType bias);

		//! Build a scale bias matrix.
		//! From GLM_GTX_transform2 extension.
		template <typename valType> 
		detail::tmat4x4<valType> scaleBias(
			detail::tmat4x4<valType> const & m, 
			valType scale, 
			valType bias);

		///@}

	}//namespace transform2
    }//namespace gtx
}//namespace glm

#include "transform2.inl"

namespace glm{using namespace gtx::transform2;}

#endif//glm_gtx_transform2
