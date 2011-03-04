///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-08
// Updated : 2009-05-08
// Licence : This source is under MIT License
// File    : glm/core/intrinsic_geometric.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_intrinsic_geometric
#define glm_core_intrinsic_geometric

#include "setup.hpp"

#if((GLM_ARCH & GLM_ARCH_SSE2) != GLM_ARCH_SSE2)
#	error "SSE2 instructions not supported or enabled"
#else

#include "intrinsic_common.hpp"

namespace glm{
namespace detail
{
	//length
	__m128 sse_len_ps(__m128 x);

	//distance
	__m128 sse_dst_ps(__m128 p0, __m128 p1);

	//dot
	__m128 sse_dot_ps(__m128 v1, __m128 v2);

	// SSE1
	__m128 sse_dot_ss(__m128 v1, __m128 v2);

	//cross
	__m128 sse_xpd_ps(__m128 v1, __m128 v2);

	//normalize
	__m128 sse_nrm_ps(__m128 v);

	//faceforward
	__m128 sse_ffd_ps(__m128 N, __m128 I, __m128 Nref);

	//reflect
	__m128 sse_rfe_ps(__m128 I, __m128 N);

	//refract
	__m128 sse_rfa_ps(__m128 I, __m128 N, __m128 eta);

}//namespace detail
}//namespace glm

#include "intrinsic_geometric.inl"

#endif//GLM_ARCH
#endif//glm_core_intrinsic_geometric
