///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/optimum_pow.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_optimum_pow
#define glm_gtx_optimum_pow

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_optimum_pow extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_optimum_pow();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_optimum_pow extension: Integer exponentiation of power functions.
    namespace optimum_pow
    {
		/// \addtogroup gtx_optimum_pow
		///@{

		//! Returns x raised to the power of 2.
		//! From GLM_GTX_optimum_pow extension.
        template <typename genType> 
		genType pow2(const genType& x);

		//! Returns x raised to the power of 3.
		//! From GLM_GTX_optimum_pow extension.
        template <typename genType> 
		genType pow3(const genType& x);

		//! Returns x raised to the power of 4.
		//! From GLM_GTX_optimum_pow extension.
		template <typename genType> 
		genType pow4(const genType& x);
        
		//! Checks if the parameter is a power of 2 number. 
		//! From GLM_GTX_optimum_pow extension.
        bool powOfTwo(int num);

		//! Checks to determine if the parameter component are power of 2 numbers.
		//! From GLM_GTX_optimum_pow extension.
        detail::tvec2<bool> powOfTwo(const detail::tvec2<int>& x);

		//! Checks to determine if the parameter component are power of 2 numbers. 
		//! From GLM_GTX_optimum_pow extension.
        detail::tvec3<bool> powOfTwo(const detail::tvec3<int>& x);

		//! Checks to determine if the parameter component are power of 2 numbers. 
		//! From GLM_GTX_optimum_pow extension.
        detail::tvec4<bool> powOfTwo(const detail::tvec4<int>& x);

		///@}

    }//namespace optimum_pow
    }//namespace gtx
}//namespace glm

#include "optimum_pow.inl"

namespace glm{using namespace gtx::optimum_pow;}

#endif//glm_gtx_optimum_pow
