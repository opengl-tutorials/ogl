///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-03-17
// Updated : 2010-03-31
// Licence : This source is under MIT License
// File    : glm/core/func_integer.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_integer
#define glm_core_func_integer

namespace glm
{
	namespace test{
		void main_core_func_integer();
	}//namespace test

	namespace core{
	namespace function{
	//! Define integer functions from Section 8.8 of GLSL 4.00.8 specification. 
	namespace integer{

		/// \addtogroup core_funcs
		///@{

		//! Adds 32-bit unsigned integer x and y, returning the sum
		//! modulo pow(2, 32). The value carry is set to 0 if the sum was
		//! less than pow(2, 32), or to 1 otherwise.
		//!
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename genUType>
		genUType uaddCarry(
			genUType const & x, 
			genUType const & y, 
			genUType & carry);

		//! Subtracts the 32-bit unsigned integer y from x, returning
		//! the difference if non-negative, or pow(2, 32) plus the difference
		//! otherwise. The value borrow is set to 0 if x >= y, or to 1 otherwise.
		//! 
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename genUType>
		genUType usubBorrow(
			genUType const & x, 
			genUType const & y, 
			genUType & borrow);
		
		//! Multiplies 32-bit integers x and y, producing a 64-bit
		//! result. The 32 least-significant bits are returned in lsb.
		//! The 32 most-significant bits are returned in msb.
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename genUType>
		void umulExtended(
			genUType const & x, 
			genUType const & y, 
			genUType & msb, 
			genUType & lsb);
		
		//! Multiplies 32-bit integers x and y, producing a 64-bit
		//! result. The 32 least-significant bits are returned in lsb.
		//! The 32 most-significant bits are returned in msb.
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename genIType>
		void imulExtended(
			genIType const & x, 
			genIType const & y, 
			genIType & msb, 
			genIType & lsb);

		//! Extracts bits [offset, offset + bits - 1] from value,
		//! returning them in the least significant bits of the result.
		//! For unsigned data types, the most significant bits of the
		//! result will be set to zero. For signed data types, the
		//! most significant bits will be set to the value of bit offset + base – 1.
		//!
		//! If bits is zero, the result will be zero. The result will be
		//! undefined if offset or bits is negative, or if the sum of
		//! offset and bits is greater than the number of bits used
		//! to store the operand.
		//!
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename genIUType>
		genIUType bitfieldExtract(
			genIUType const & Value, 
			int const & Offset, 
			int const & Bits);

		//! Returns the insertion the bits least-significant bits of insert into base.
		//!
		//! The result will have bits [offset, offset + bits - 1] taken
		//! from bits [0, bits – 1] of insert, and all other bits taken
		//! directly from the corresponding bits of base. If bits is
		//! zero, the result will simply be base. The result will be
		//! undefined if offset or bits is negative, or if the sum of
		//! offset and bits is greater than the number of bits used to
		//! store the operand.
		//!
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename genIUType>
		genIUType bitfieldInsert(
			genIUType const & Base, 
			genIUType const & Insert, 
			int const & Offset, 
			int const & Bits);

		//! Returns the reversal of the bits of value. 
		//! The bit numbered n of the result will be taken from bit (bits - 1) - n of value, 
		//! where bits is the total number of bits used to represent value.
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename genIUType>
		genIUType bitfieldReverse(genIUType const & value);
		
		//! Returns the number of bits set to 1 in the binary representation of value.
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename T, template <typename> class C>
		typename C<T>::signed_type bitCount(C<T> const & Value);

		//! Returns the bit number of the least significant bit set to
		//! 1 in the binary representation of value. 
		//! If value is zero, -1 will be returned.
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename T, template <typename> class C>
		typename C<T>::signed_type findLSB(C<T> const & Value);

		//! Returns the bit number of the most significant bit in the binary representation of value.
		//! For positive integers, the result will be the bit number of the most significant bit set to 1. 
		//! For negative integers, the result will be the bit number of the most significant
		//! bit set to 0. For a value of zero or negative one, -1 will be returned.
		//! (From GLSL 4.00.08 specification, section 8.8)
		template <typename T, template <typename> class C>
		typename C<T>::signed_type findMSB(C<T> const & Value);

		///@}

	}//namespace integer
	}//namespace function
	}//namespace core

	using namespace core::function::integer;
}//namespace glm

#include "func_integer.inl"

#endif//glm_core_func_integer

