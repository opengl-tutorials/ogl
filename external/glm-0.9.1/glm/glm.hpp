///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-01-14
// Updated : 2011-01-19
// Licence : This source is under MIT License
// File    : glm/glm.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "core/_fixes.hpp"

#ifndef glm_glm
#define glm_glm

//! TODO: to delete
#define GLMvalType typename genType::value_type

#include <cmath>
#include <climits>
#include <cfloat>
#include <limits>
#include "core/setup.hpp"

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_CORE_INCLUDED_DISPLAYED))
#	define GLM_MESSAGE_CORE_INCLUDED_DISPLAYED
#	pragma message("GLM: Core library included")
#endif//GLM_MESSAGE

//! GLM namespace, it contains all GLSL based features.
namespace glm
{
	namespace test
	{
		bool main_bug();
		bool main_core();
	}//namespace test

	//! GLM core. Namespace that includes all the feature define by GLSL 4.10.6 specification. This namespace is included in glm namespace.
	namespace core
	{
		//! Scalar, vectors and matrices 
		//! from section 4.1.2 Booleans, 4.1.3 Integers section, 4.1.4 Floats section,
		//! 4.1.5 Vectors and section 4.1.6 Matrices of GLSL 1.30.8 specification. 
		//! This namespace resolves precision qualifier define in section 4.5 of GLSL 1.30.8 specification.
		namespace type{}

		//! Some of the functions defined in section 8 Built-in Functions of GLSL 1.30.8 specification.
		//! Angle and trigonometry, exponential, common, geometric, matrix and vector relational functions.
		namespace function{}
	}
	//namespace core

	//! G-Truc Creation stable extensions.
	namespace gtc{}

	//! G-Truc Creation experimental extensions. 
	//! The interface could change between releases.
	namespace gtx{}

	//! VIRTREV extensions.
	namespace img{}

} //namespace glm

#include "./core/_detail.hpp"
#include "./core/type.hpp"

#include "./core/func_trigonometric.hpp"
#include "./core/func_exponential.hpp"
#include "./core/func_common.hpp"
#include "./core/func_packing.hpp"
#include "./core/func_geometric.hpp"
#include "./core/func_matrix.hpp"
#include "./core/func_vector_relational.hpp"
#include "./core/func_integer.hpp"
#include "./core/func_noise.hpp"
#include "./core/_swizzle.hpp"

namespace glm
{
 	using namespace core::type;
	using namespace core::type::precision;
	using namespace core::function;
} //namespace glm

////////////////////
// check type sizes
#ifndef GLM_STATIC_ASSERT_NULL
	GLM_STATIC_ASSERT(sizeof(glm::detail::int8) == 1, "int8 size isn't 1 byte on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::int16) == 2, "int16 size isn't 2 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::int32) == 4, "int32 size isn't 4 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::int64) == 8, "int64 size isn't 8 bytes on this platform");

	GLM_STATIC_ASSERT(sizeof(glm::detail::uint8) == 1, "uint8 size isn't 1 byte on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::uint16) == 2, "uint16 size isn't 2 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::uint32) == 4, "uint32 size isn't 4 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::uint64) == 8, "uint64 size isn't 8 bytes on this platform");

	GLM_STATIC_ASSERT(sizeof(glm::detail::float16) == 2, "float16 size isn't 2 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::float32) == 4, "float32 size isn't 4 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::float64) == 8, "float64 size isn't 8 bytes on this platform");
#endif//GLM_STATIC_ASSERT_NULL

#endif //glm_glm
