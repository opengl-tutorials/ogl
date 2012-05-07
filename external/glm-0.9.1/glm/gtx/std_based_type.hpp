///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-06-08
// Updated : 2008-06-08
// Licence : This source is under MIT License
// File    : glm/gtx/std_based_type.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_std_based_type
#define glm_gtx_std_based_type

// Dependency:
#include "../glm.hpp"
#include <cstdlib>

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_std_based_type extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_std_based_type();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_std_based_type extension: Add support vector types based on C++ standard type
	namespace std_based_type
	{
		typedef detail::tvec2<std::size_t>		size2;
		typedef detail::tvec3<std::size_t>		size3;
		typedef detail::tvec4<std::size_t>		size4;

		typedef detail::tvec2<signed char>		scvec2;
		typedef detail::tvec3<signed char>		scvec3;
		typedef detail::tvec4<signed char>		scvec4;

		typedef detail::tvec2<unsigned char>	ucvec2;
		typedef detail::tvec3<unsigned char>	ucvec3;
		typedef detail::tvec4<unsigned char>	ucvec4;

		typedef detail::tvec2<signed short>		ssvec2;
		typedef detail::tvec3<signed short>		ssvec3;
		typedef detail::tvec4<signed short>		ssvec4;

		typedef detail::tvec2<unsigned short>	usvec2;
		typedef detail::tvec3<unsigned short>	usvec3;
		typedef detail::tvec4<unsigned short>	usvec4;

		typedef detail::tvec2<signed int>		sivec2;
		typedef detail::tvec3<signed int>		sivec3;
		typedef detail::tvec4<signed int>		sivec4;

		typedef detail::tvec2<unsigned int>		uivec2;
		typedef detail::tvec3<unsigned int>		uivec3;
		typedef detail::tvec4<unsigned int>		uivec4;

		typedef detail::tvec2<signed long>		slvec2;
		typedef detail::tvec3<signed long>		slvec3;
		typedef detail::tvec4<signed long>		slvec4;

		typedef detail::tvec2<unsigned long>	ulvec2;
		typedef detail::tvec3<unsigned long>	ulvec3;
		typedef detail::tvec4<unsigned long>	ulvec4;

	}//namespace std_based_type
	}//namespace gtx
}//namespace glm

#include "std_based_type.inl"

namespace glm{using namespace gtx::std_based_type;}

#endif//glm_gtx_std_based_type
