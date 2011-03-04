///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-04-03
// Updated : 2009-01-20
// Licence : This source is under MIT License
// File    : glm/gtx/intersect.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_closest_point
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_intersect
#define glm_gtx_intersect

// Dependency:
#include "../glm.hpp"
#include "../gtx/closest_point.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_closest_point extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_intesect();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_intersect extension: Add intersection functions
	namespace intersect
	{
		/// \addtogroup gtx_intersect
		///@{

		//! Compute the intersection of a ray and a triangle.
		//! From GLM_GTX_intersect extension.
		template <typename genType>
		bool intersectRayTriangle(
			genType const & orig, genType const & dir,
			genType const & vert0, genType const & vert1, genType const & vert2,
			genType & baryPosition);

        //! Compute the intersection of a line and a triangle.
		//! From GLM_GTX_intersect extension.
		template <typename genType>
		bool intersectLineTriangle(
			genType const & orig, genType const & dir,
			genType const & vert0, genType const & vert1, genType const & vert2,
			genType & position);

        //! Compute the intersection of a ray and a sphere.
		//! From GLM_GTX_intersect extension.
		template <typename genType>
		bool intersectRaySphere(
			genType const & orig, genType const & dir,
			genType const & center, typename genType::value_type radius,
			genType & position, genType & normal);

        //! Compute the intersection of a line and a sphere.
		//! From GLM_GTX_intersect extension
		template <typename genType>
		bool intersectLineSphere(
			genType const & point0, genType const & point1,
			genType const & center, typename genType::value_type radius,
			genType & position, genType & normal);

		///@}

	}//namespace intersect
}//namespace gtx
}//namespace glm

#include "intersect.inl"

namespace glm{using namespace gtx::intersect;}

#endif//glm_gtx_intersect
