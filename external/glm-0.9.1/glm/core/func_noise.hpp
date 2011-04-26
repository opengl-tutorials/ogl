///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-01
// Updated : 2008-09-10
// Licence : This source is under MIT License
// File    : glm/core/func_noise.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_noise
#define glm_core_func_noise

namespace glm
{
	namespace test{
		void main_core_func_noise();
	}//namespace test

	namespace core{
	namespace function{
	// Define all noise functions from Section 8.9 of GLSL 1.30.8 specification. Included in glm namespace.
	namespace noise{

	/// \addtogroup core_funcs
	///@{

	// Returns a 1D noise value based on the input value x.
	// From GLSL 1.30.08 specification, section 8.9.
	template <typename genType>
	typename genType::value_type noise1(genType const & x);

	// Returns a 2D noise value based on the input value x.
	// From GLSL 1.30.08 specification, section 8.9.
	template <typename genType>
	detail::tvec2<typename genType::value_type> noise2(genType const & x);

	// Returns a 3D noise value based on the input value x.
	// From GLSL 1.30.08 specification, section 8.9.
	template <typename genType>
	detail::tvec3<typename genType::value_type> noise3(genType const & x);

	// Returns a 4D noise value based on the input value x.
	// From GLSL 1.30.08 specification, section 8.9.
	template <typename genType>
	detail::tvec4<typename genType::value_type> noise4(genType const & x);

	///@}

	}//namespace noise
	}//namespace function
	}//namespace core

	using namespace core::function::noise;
}//namespace glm

#include "func_noise.inl"

#endif//glm_core_func_noise
