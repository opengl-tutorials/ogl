///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-06-09
// Updated : 2009-06-09
// Licence : This source is under MIT License
// File    : glm/core/intrinsic_vector_relational.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_detail_intrinsic_vector_relational
#define glm_detail_intrinsic_vector_relational

#include "setup.hpp"

#if((GLM_ARCH & GLM_ARCH_SSE2) != GLM_ARCH_SSE2)
#	error "SSE2 instructions not supported or enabled"
#else

namespace glm{
namespace detail
{

}//namespace detail
}//namespace glm

#include "intrinsic_vector_relational.inl"

#endif//GLM_ARCH
#endif//glm_detail_intrinsic_vector_relational
