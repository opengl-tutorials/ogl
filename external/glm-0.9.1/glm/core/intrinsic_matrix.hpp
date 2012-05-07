///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-06-05
// Updated : 2009-06-05
// Licence : This source is under MIT License
// File    : glm/core/intrinsic_common.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_detail_intrinsic_matrix
#define glm_detail_intrinsic_matrix

#include "setup.hpp"

#if((GLM_ARCH & GLM_ARCH_SSE2) != GLM_ARCH_SSE2)
#	error "SSE2 instructions not supported or enabled"
#else

#include "intrinsic_geometric.hpp"

namespace glm{
namespace detail
{
	void sse_add_ps(__m128 in1[4], __m128 in2[4], __m128 out[4]);

	void sse_sub_ps(__m128 in1[4], __m128 in2[4], __m128 out[4]);

	__m128 sse_mul_ps(__m128 m[4], __m128 v);

	__m128 sse_mul_ps(__m128 v, __m128 m[4]);

	void sse_mul_ps(__m128 const in1[4], __m128 const in2[4], __m128 out[4]);

	void sse_transpose_ps(__m128 const in[4], __m128 out[4]);

	void sse_inverse_ps(__m128 const in[4], __m128 out[4]);

	void sse_rotate_ps(__m128 const in[4], float Angle, float const v[3], __m128 out[4]);

	__m128 sse_det_ps(__m128 const m[4]);

	__m128 sse_slow_det_ps(__m128 const m[4]);

}//namespace detail
}//namespace glm

#include "intrinsic_matrix.inl"

#endif//GLM_ARCH
#endif//glm_detail_intrinsic_matrix
