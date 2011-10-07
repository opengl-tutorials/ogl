///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-09
// Updated : 2008-10-09
// Licence : This source is under MIT License
// File    : glm/gtx/reciprocal.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_reciprocal
#define glm_gtx_reciprocal

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_reciprocal extension included")
#endif

namespace glm
{
   	namespace test{
		void main_gtx_reciprocal();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_reciprocal extension: Define secant, cosecant and cotangent functions.
	namespace reciprocal
	{
		/// \addtogroup gtx_reciprocal
		///@{

		//! Secant function. 
		//! hypotenuse / adjacent or 1 / cos(x)
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType sec(genType const & angle);

		//! Cosecant function. 
		//! hypotenuse / opposite or 1 / sin(x)
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType csc(genType const & angle);
		
		//! Cotangent function. 
		//! adjacent / opposite or 1 / tan(x)
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType cot(genType const & angle);

		//! Inverse secant function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType asec(genType const & x);

		//! Inverse cosecant function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType acsc(genType const & x);
		
		//! Inverse cotangent function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType acot(genType const & x);

		//! Secant hyperbolic function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType sech(genType const & angle);

		//! Cosecant hyperbolic function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType csch(genType const & angle);
		
		//! Cotangent hyperbolic function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType coth(genType const & angle);

		//! Inverse secant hyperbolic function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType asech(genType const & x);

		//! Inverse cosecant hyperbolic function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType acsch(genType const & x);
		
		//! Inverse cotangent hyperbolic function. 
		//! From GLM_GTX_reciprocal extension.
		template <typename genType> 
		genType acoth(genType const & x);

		///@}

	}//namespace reciprocal
	}//namespace gtx
}//namespace glm

#include "reciprocal.inl"

namespace glm{using namespace gtx::reciprocal;}

#endif//glm_gtx_reciprocal
