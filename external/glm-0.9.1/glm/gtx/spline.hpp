///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-01-25
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/spline.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_spline
#define glm_gtx_spline

// Dependency:
#include "../glm.hpp"
#include "../gtx/optimum_pow.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_spline extension included")
#endif

namespace glm
{
    namespace gtx{
	//! GLM_GTX_spline extension: Spline functions
    namespace spline
    {
		using namespace gtx::optimum_pow;

		/// \addtogroup gtx_spline
		///@{

		//! Return a point from a catmull rom curve.
		//! From GLM_GTX_spline extension.
		template <typename genType> 
		genType catmullRom(
			const genType& v1, 
			const genType& v2, 
			const genType& v3, 
			const genType& v4, 
			const GLMvalType& s);
		
		//! Return a point from a hermite curve.
		//! From GLM_GTX_spline extension.
        template <typename genType> 
		genType hermite(
			const genType& v1, 
			const genType& t1, 
			const genType& v2, 
			const genType& t2, 
			const GLMvalType& s);
		
        //! Return a point from a cubic curve. 
		//! From GLM_GTX_spline extension.
		template <typename genType> 
		genType cubic(
			const genType& v1, 
			const genType& v2, 
			const genType& v3, 
			const genType& v4, 
			const GLMvalType& s);

		///@}

	}//namespace spline
    }//namespace gtx
}//namespace glm

#include "spline.inl"

namespace glm{using namespace gtx::spline;}

#endif//glm_gtx_spline

