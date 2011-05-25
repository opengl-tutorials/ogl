///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2008-07-24
// Licence : This source is under MIT License
// File    : glm/gtx/norm.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////
// ToDo:
// - Study the validity of the notion of length2 to quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_norm
#define glm_gtx_norm

// Dependency:
#include "../glm.hpp"
#include "../gtx/quaternion.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_norm extension included")
#endif

namespace glm
{
   	namespace test{
		void main_gtx_norm();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_norm extension: Various way to compute vector norms.
	namespace norm
	{
		/// \addtogroup gtx_norm
		///@{

		//! Returns the squared length of x.
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T length2(
			const T x);

		//! Returns the squared length of x.
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T length2(
			const detail::tvec2<T> & x);

		//! Returns the squared length of x.
		//! From GLM_GTX_norm extension.
		template <typename T>
		T length2(
			const detail::tvec3<T>& x);
		
		//! Returns the squared length of x.
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T length2(
			const detail::tvec4<T>& x);
		
		//! Returns the squared length of x.
		//! From GLM_GTX_norm extension.
		template <typename T>
		T length2(
			const detail::tquat<T>& q);

		//! Returns the squared distance between p0 and p1, i.e., length(p0 - p1).
		//! From GLM_GTX_norm extension.
		template <typename T>
		T distance2(
			const T p0, 
			const T p1);
		
		//! Returns the squared distance between p0 and p1, i.e., length(p0 - p1).
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T distance2(
			const detail::tvec2<T>& p0, 
			const detail::tvec2<T>& p1);

		//! Returns the squared distance between p0 and p1, i.e., length(p0 - p1).
		//! From GLM_GTX_norm extension.
		template <typename T>
		T distance2(
			const detail::tvec3<T>& p0,
			const detail::tvec3<T>& p1);

		//! Returns the squared distance between p0 and p1, i.e., length(p0 - p1).
		//! From GLM_GTX_norm extension.
		template <typename T>
		T distance2(
			const detail::tvec4<T>& p0, 
			const detail::tvec4<T>& p1);

		//! Returns the L1 norm between x and y.
		//! From GLM_GTX_norm extension.
		template <typename T>
		T l1Norm(
			const detail::tvec3<T>& x,
			const detail::tvec3<T>& y);
		
		//! Returns the L1 norm of v.
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T l1Norm(
			const detail::tvec3<T>& v);
		
		//! Returns the L2 norm between x and y.
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T l2Norm(
			const detail::tvec3<T>& x, 
			const detail::tvec3<T>& y);
		
		//! Returns the L2 norm of v.
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T l2Norm(
			const detail::tvec3<T>& x);
		
		//! Returns the L norm between x and y.
		//! From GLM_GTX_norm extension.
		template <typename T> 
		T lxNorm(
			const detail::tvec3<T>& x,
			const detail::tvec3<T>& y,
			unsigned int Depth);

		//! Returns the L norm of v.
		//! From GLM_GTX_norm extension.
		template <typename T>
		T lxNorm(
			const detail::tvec3<T>& x,
			unsigned int Depth);

		///@}

	}//namespace norm
	}//namespace gtx
}//namespace glm

#include "norm.inl"

namespace glm{using namespace gtx::norm;}

#endif//glm_gtx_norm
