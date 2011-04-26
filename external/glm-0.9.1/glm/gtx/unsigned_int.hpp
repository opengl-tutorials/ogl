///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-24
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/unsigned_int.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_integer
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_unsigned_int
#define glm_gtx_unsigned_int

// Dependency:
#include "../glm.hpp"
#include "../gtx/integer.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_unsigned_int extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_unsigned_int();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_unsigned_int extension: Add support for unsigned integer for core functions
	namespace unsigned_int
	{
		using namespace gtx::integer;

		/// \addtogroup gtx_unsigned_int
		///@{

		//! 32bit signed integer. 
		//! From GLM_GTX_unsigned_int extension.
		typedef signed int					sint;

		//! Returns x raised to the y power.
		//! From GLM_GTX_unsigned_int extension.
		uint pow(uint x, uint y);

		//! Returns the positive square root of x. 
		//! From GLM_GTX_unsigned_int extension.
		uint sqrt(uint x);

		//! Modulus. Returns x - y * floor(x / y) for each component in x using the floating point value y.
		//! From GLM_GTX_unsigned_int extension.
		uint mod(uint x, uint y);

		///@}

	}//namespace unsigned_int
	}//namespace gtx
}//namespace glm

#include "unsigned_int.inl"

namespace glm{using namespace gtx::unsigned_int;}

#endif//glm_gtx_unsigned_int
