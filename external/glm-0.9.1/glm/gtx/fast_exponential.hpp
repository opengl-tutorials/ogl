///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-09
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/fast_exponential.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_half_float
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_fast_exponential
#define glm_gtx_fast_exponential

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_fast_exponential extension included")
#endif

namespace glm
{
   	namespace test{
		void main_gtx_fast_exponential();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_fast_exponential extension: Fast but less accurate implementations of exponential based functions.
	namespace fast_exponential
	{
		using namespace gtc::half_float;
		/// \addtogroup gtx_fast_exponential
		///@{

		//! Faster than the common pow function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename valType> 
		valType fastPow(
			valType const & x, 
			valType const & y);

		//! Faster than the common pow function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T, typename U> 
		T fastPow(
			const T& x, 
			const U& y);
		
		//! Faster than the common exp function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastExp(const T& x);
		
		//! Faster than the common log function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastLog(const T& x);

		//! Faster than the common exp2 function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastExp2(const T& x);
		
		//! Faster than the common log2 function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastLog2(const T& x);

		//! Faster than the common ln function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastLn(const T& x);

		///@}

	}//namespace fast_exponential
	}//namespace gtx
}//namespace glm

#include "fast_exponential.inl"

namespace glm{using namespace gtx::fast_exponential;}

#endif//glm_gtx_fast_exponential
