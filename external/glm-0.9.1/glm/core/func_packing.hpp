///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-03-17
// Updated : 2010-03-17
// Licence : This source is under MIT License
// File    : glm/core/func_packing.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_packing
#define glm_core_func_packing

namespace glm
{
	namespace test{
		void main_core_func_packing();
	}//namespace test

	namespace core{
	namespace function{
	//! Define packing functions from section 8.4 floating-point pack and unpack functions of GLSL 4.00.8 specification
	namespace packing
	{
		/// \addtogroup core_funcs
		///@{

		detail::uint32 packUnorm2x16(detail::tvec2<detail::float32> const & v);
		detail::uint32 packUnorm4x8(detail::tvec4<detail::float32> const & v);
		detail::uint32 packSnorm4x8(detail::tvec4<detail::float32> const & v);

		detail::tvec2<detail::float32> unpackUnorm2x16(detail::uint32 const & p);
		detail::tvec4<detail::float32> unpackUnorm4x8(detail::uint32 const & p);
		detail::tvec4<detail::float32> unpackSnorm4x8(detail::uint32 const & p);

		double packDouble2x32(detail::tvec2<detail::uint32> const & v);
		detail::tvec2<detail::uint32> unpackDouble2x32(double const & v);

		///@}

	}//namespace packing
	}//namespace function
	}//namespace core

	using namespace core::function::packing;
}//namespace glm

#include "func_packing.inl"

#endif//glm_core_func_packing

