///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-11
// Updated : 2009-05-11
// Licence : This source is under MIT License
// File    : glm/core/intrinsic_exponential.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_detail_intrinsic_exponential
#define glm_detail_intrinsic_exponential

#include "setup.hpp"

#if((GLM_ARCH & GLM_ARCH_SSE2) != GLM_ARCH_SSE2)
#	error "SSE2 instructions not supported or enabled"
#else

namespace glm{
namespace detail
{
/*
inline __m128 sse_rsqrt_nr_ss(__m128 const x)
{
	__m128 recip = _mm_rsqrt_ss( x );  // "estimate" opcode
	const static __m128 three = { 3, 3, 3, 3 }; // aligned consts for fast load
	const static __m128 half = { 0.5,0.5,0.5,0.5 };
	__m128 halfrecip = _mm_mul_ss( half, recip );
	__m128 threeminus_xrr = _mm_sub_ss( three, _mm_mul_ss( x, _mm_mul_ss ( recip, recip ) ) );
	return _mm_mul_ss( halfrecip, threeminus_xrr );
}
 
inline __m128 sse_normalize_fast_ps(  float * RESTRICT vOut, float * RESTRICT vIn )
{
        __m128 x = _mm_load_ss(&vIn[0]);
        __m128 y = _mm_load_ss(&vIn[1]);
        __m128 z = _mm_load_ss(&vIn[2]);
 
        const __m128 l =  // compute x*x + y*y + z*z
                _mm_add_ss(
                 _mm_add_ss( _mm_mul_ss(x,x),
                             _mm_mul_ss(y,y)
                            ),
                 _mm_mul_ss( z, z )
                );
 
 
        const __m128 rsqt = _mm_rsqrt_nr_ss( l );
        _mm_store_ss( &vOut[0] , _mm_mul_ss( rsqt, x ) );
        _mm_store_ss( &vOut[1] , _mm_mul_ss( rsqt, y ) );
        _mm_store_ss( &vOut[2] , _mm_mul_ss( rsqt, z ) );
 
        return _mm_mul_ss( l , rsqt );
}
*/
}//namespace detail
}//namespace glm

#endif//GLM_ARCH
#endif//glm_detail_intrinsic_exponential
