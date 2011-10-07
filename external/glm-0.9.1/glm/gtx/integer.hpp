///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-24
// Updated : 2006-11-14
// Licence : This source is under MIT License
// File    : glm/gtx/integer.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_integer
#define glm_gtx_integer

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_integer extension included")
#endif

namespace glm
{
	namespace gtx{
	//! GLM_GTX_integer extension: Add support for integer for core functions
	namespace integer
	{
		/// \addtogroup gtx_integer
		///@{

		//! Returns x raised to the y power. 
		//! From GLM_GTX_integer extension.
		int pow(int x, int y);

		//! Returns the positive square root of x.
		//! From GLM_GTX_integer extension.
		int sqrt(int x);

		//! Modulus. Returns x - y * floor(x / y) for each component in x using the floating point value y.
		//! From GLM_GTX_integer extension.
		int mod(int x, int y);

		//! Return the factorial value of a number (!12 max, integer only)
		//! From GLM_GTX_integer extension.
		template <typename genType> 
		genType factorial(genType const & x);

		///@}

	}//namespace integer
	}//namespace gtx
}//namespace glm

#include "integer.inl"

namespace glm{using namespace gtx::integer;}

#endif//glm_gtx_integer
