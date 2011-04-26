///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-11
// Updated : 2009-05-11
// Licence : This source is under MIT License
// File    : glm/core/intrinsic_common.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_detail_intrinsic_common
#define glm_detail_intrinsic_common

#include "setup.hpp"

#if((GLM_ARCH & GLM_ARCH_SSE2) != GLM_ARCH_SSE2)
#	error "SSE2 instructions not supported or enabled"
#else

namespace glm{
namespace detail
{
	__m128 sse_abs_ps(__m128 x);

	__m128 sse_sgn_ps(__m128 x);

	//floor
	__m128 sse_flr_ps(__m128 v);

	//trunc
	__m128 sse_trc_ps(__m128 v);

	//round
	__m128 sse_nd_ps(__m128 v);

	//roundEven
	__m128 sse_rde_ps(__m128 v);

	__m128 sse_rnd_ps(__m128 x);

	__m128 sse_ceil_ps(__m128 v);

	__m128 sse_frc_ps(__m128 x);

	__m128 sse_mod_ps(__m128 x, __m128 y);

	__m128 sse_modf_ps(__m128 x, __m128i & i);

	//inline __m128 sse_min_ps(__m128 x, __m128 y)

	//inline __m128 sse_max_ps(__m128 x, __m128 y)

	__m128 sse_clp_ps(__m128 v, __m128 minVal, __m128 maxVal);

	__m128 sse_mix_ps(__m128 v1, __m128 v2, __m128 a);

	__m128 sse_stp_ps(__m128 edge, __m128 x);

	__m128 sse_ssp_ps(__m128 edge0, __m128 edge1, __m128 x);

	__m128 sse_nan_ps(__m128 x);

	__m128 sse_inf_ps(__m128 x);

}//namespace detail
}//namespace glm

#include "intrinsic_common.inl"

#endif//GLM_ARCH
#endif//glm_detail_intrinsic_common
