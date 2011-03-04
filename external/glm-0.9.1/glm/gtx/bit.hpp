///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-14
// Updated : 2008-11-14
// Licence : This source is under MIT License
// File    : glm/gtx/bit.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_half_float
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_bit
#define glm_gtx_bit

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_bit extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_bit();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_bit extension: Allow to perform bit operations on integer values
	namespace bit
	{
		using namespace gtc::half_float;

		/// \addtogroup gtx_bit
		///@{
		//! Build a mask of 'count' bits
		//! From GLM_GTX_bit extension.
		template <typename genIType>
		genIType mask(genIType const & count);

		//! Component wise extraction of bit fields.
		//! genType and genIType could be a scalar or a vector.
		//! From GLM_GTX_bit extension.
		template <typename genIUType, typename sizeType>
		genIUType extractField(
			genIUType const & v, 
			sizeType const & first, 
			sizeType const & count);

		//! Find the lowest bit set to 1 in a integer variable.
		//! From GLM_GTX_bit extension.
		template <typename genType> 
		int lowestBit(genType const & value);

		//! Find the highest bit set to 1 in a integer variable.
		//! From GLM_GTX_bit extension.
		template <typename genType> 
		int highestBit(genType const & value);

		//! Find the highest bit set to 1 in a integer variable and return its value. 
		//! From GLM_GTX_bit extension.
		template <typename genType> 
		genType highestBitValue(genType const & value);

		//! Return true if the value is a power of two number. 
		//! From GLM_GTX_bit extension. 
		template <typename genType> 
		bool isPowerOfTwo(genType const & value);

		//! Return the power of two number which value is just higher the input value.
		//! From GLM_GTX_bit extension.
		template <typename genType> 
		genType powerOfTwoAbove(genType const & value);

		//! Return the power of two number which value is just lower the input value. 
		//! From GLM_GTX_bit extension.
		template <typename genType> 
		genType powerOfTwoBelow(genType const & value);

		//! Return the power of two number which value is the closet to the input value. 
		//! From GLM_GTX_bit extension.
		template <typename genType> 
		genType powerOfTwoNearest(genType const & value);

		//! Revert all bits of any integer based type. 
		//! From GLM_GTX_bit extension.
		template <typename genType> 
		genType bitRevert(genType const & value);

		//! Rotate all bits to the right.
		//! From GLM_GTX_bit extension.
		template <typename genType>
		genType bitRotateRight(genType const & In, std::size_t Shift);

		//! Rotate all bits to the left.
		//! From GLM_GTX_bit extension.
		template <typename genType>
		genType bitRotateLeft(genType const & In, std::size_t Shift);
		///@}

	}//namespace bit
	}//namespace gtx
}//namespace glm

#include "bit.inl"

namespace glm{using namespace gtx::bit;}

#endif//glm_gtx_bit
