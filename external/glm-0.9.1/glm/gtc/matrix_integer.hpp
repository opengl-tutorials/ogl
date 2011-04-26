///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-01-20
// Updated : 2011-01-20
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_integer.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_matrix_integer
#define glm_gtc_matrix_integer

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_matrix_integer extension included")
#endif

namespace glm
{
	namespace test{
		bool main_gtc_matrix_integer();
	}//namespace test

	namespace gtc{
	//! GLM_GTC_matrix_integer extension: Add integer matrices
	namespace matrix_integer
	{
		/// \addtogroup gtc_matrix_integer
		///@{

		typedef detail::tmat2x2<highp_int>				highp_imat2;	//!< \brief High-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<highp_int>				highp_imat3;	//!< \brief High-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<highp_int>				highp_imat4;	//!< \brief High-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<highp_int>				highp_imat2x2; //!< \brief High-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x3<highp_int>				highp_imat2x3; //!< \brief High-precision signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x4<highp_int>				highp_imat2x4; //!< \brief High-precision signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x2<highp_int>				highp_imat3x2; //!< \brief High-precision signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<highp_int>				highp_imat3x3; //!< \brief High-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x4<highp_int>				highp_imat3x4; //!< \brief High-precision signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x2<highp_int>				highp_imat4x2; //!< \brief High-precision signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x3<highp_int>				highp_imat4x3; //!< \brief High-precision signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<highp_int>				highp_imat4x4; //!< \brief High-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<mediump_int>			mediump_imat2;	//!< \brief Medium-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<mediump_int>			mediump_imat3;	//!< \brief Medium-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<mediump_int>			mediump_imat4;	//!< \brief Medium-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<mediump_int>			mediump_imat2x2; //!< \brief Medium-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x3<mediump_int>			mediump_imat2x3; //!< \brief Medium-precision signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x4<mediump_int>			mediump_imat2x4; //!< \brief Medium-precision signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x2<mediump_int>			mediump_imat3x2; //!< \brief Medium-precision signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<mediump_int>			mediump_imat3x3; //!< \brief Medium-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x4<mediump_int>			mediump_imat3x4; //!< \brief Medium-precision signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x2<mediump_int>			mediump_imat4x2; //!< \brief Medium-precision signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x3<mediump_int>			mediump_imat4x3; //!< \brief Medium-precision signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<mediump_int>			mediump_imat4x4; //!< \brief Medium-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<lowp_int>				lowp_imat2;	//!< \brief Low-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<lowp_int>				lowp_imat3;	//!< \brief Low-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<lowp_int>				lowp_imat4;	//!< \brief Low-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<lowp_int>				lowp_imat2x2; //!< \brief Low-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x3<lowp_int>				lowp_imat2x3; //!< \brief Low-precision signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x4<lowp_int>				lowp_imat2x4; //!< \brief Low-precision signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x2<lowp_int>				lowp_imat3x2; //!< \brief Low-precision signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<lowp_int>				lowp_imat3x3; //!< \brief Low-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x4<lowp_int>				lowp_imat3x4; //!< \brief Low-precision signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x2<lowp_int>				lowp_imat4x2; //!< \brief Low-precision signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x3<lowp_int>				lowp_imat4x3; //!< \brief Low-precision signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<lowp_int>				lowp_imat4x4; //!< \brief Low-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<highp_uint>				highp_umat2; //!< \brief High-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<highp_uint>				highp_umat3; //!< \brief High-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<highp_uint>				highp_umat4; //!< \brief High-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<highp_uint>				highp_umat2x2; //!< \brief High-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x3<highp_uint>				highp_umat2x3; //!< \brief High-precision signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x4<highp_uint>				highp_umat2x4; //!< \brief High-precision signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x2<highp_uint>				highp_umat3x2; //!< \brief High-precision signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<highp_uint>				highp_umat3x3; //!< \brief High-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x4<highp_uint>				highp_umat3x4; //!< \brief High-precision signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x2<highp_uint>				highp_umat4x2; //!< \brief High-precision signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x3<highp_uint>				highp_umat4x3; //!< \brief High-precision signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<highp_uint>				highp_umat4x4; //!< \brief High-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<mediump_uint>			mediump_umat2; //!< \brief Medium-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<mediump_uint>			mediump_umat3; //!< \brief Medium-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<mediump_uint>			mediump_umat4; //!< \brief Medium-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<mediump_uint>			mediump_umat2x2; //!< \brief Medium-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x3<mediump_uint>			mediump_umat2x3; //!< \brief Medium-precision signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x4<mediump_uint>			mediump_umat2x4; //!< \brief Medium-precision signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x2<mediump_uint>			mediump_umat3x2; //!< \brief Medium-precision signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<mediump_uint>			mediump_umat3x3; //!< \brief Medium-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x4<mediump_uint>			mediump_umat3x4; //!< \brief Medium-precision signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x2<mediump_uint>			mediump_umat4x2; //!< \brief Medium-precision signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x3<mediump_uint>			mediump_umat4x3; //!< \brief Medium-precision signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<mediump_uint>			mediump_umat4x4; //!< \brief Medium-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<lowp_uint>				lowp_umat2;	//!< \brief Low-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<lowp_uint>				lowp_umat3;	//!< \brief Low-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<lowp_uint>				lowp_umat4;	//!< \brief Low-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef detail::tmat2x2<lowp_uint>				lowp_umat2x2; //!< \brief Low-precision signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x3<lowp_uint>				lowp_umat2x3; //!< \brief Low-precision signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat2x4<lowp_uint>				lowp_umat2x4; //!< \brief Low-precision signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x2<lowp_uint>				lowp_umat3x2; //!< \brief Low-precision signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x3<lowp_uint>				lowp_umat3x3; //!< \brief Low-precision signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat3x4<lowp_uint>				lowp_umat3x4; //!< \brief Low-precision signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x2<lowp_uint>				lowp_umat4x2; //!< \brief Low-precision signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x3<lowp_uint>				lowp_umat4x3; //!< \brief Low-precision signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef detail::tmat4x4<lowp_uint>				lowp_umat4x4; //!< \brief Low-precision signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

#if(defined(GLM_PRECISION) && (GLM_PRECISION & GLM_PRECISION_HIGHP_INT))
		typedef highp_imat2								imat2; //!< \brief Signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat3								imat3; //!< \brief Signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat4								imat4; //!< \brief Signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

		typedef highp_imat2x2							imat2x2; //!< \brief Signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat2x3							imat2x3; //!< \brief Signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat2x4							imat2x4; //!< \brief Signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat3x2							imat3x2; //!< \brief Signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat3x3							imat3x3; //!< \brief Signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat3x4							imat3x4; //!< \brief Signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat4x2							imat4x2; //!< \brief Signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat4x3							imat4x3; //!< \brief Signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_imat4x4							imat4x4; //!< \brief Signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

#elif(defined(GLM_PRECISION) && (GLM_PRECISION & GLM_PRECISION_LOWP_INT))
		typedef lowp_imat2								imat2; //!< \brief Signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat3								imat3; //!< \brief Signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat4								imat4; //!< \brief Signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat2x2							imat2x2; //!< \brief Signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat2x3							imat2x3; //!< \brief Signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat2x4							imat2x4; //!< \brief Signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat3x2							imat3x2; //!< \brief Signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat3x3							imat3x3; //!< \brief Signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat3x4							imat3x4; //!< \brief Signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat4x2							imat4x2; //!< \brief Signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat4x3							imat4x3; //!< \brief Signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_imat4x4							imat4x4; //!< \brief Signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

#else //if(defined(GLM_PRECISION) && (GLM_PRECISION & GLM_PRECISION_MEDIUMP_INT))
		typedef mediump_imat2							imat2; //!< \brief Signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat3							imat3; //!< \brief Signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat4							imat4; //!< \brief Signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat2x2							imat2x2; //!< \brief Signed integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat2x3							imat2x3; //!< \brief Signed integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat2x4							imat2x4; //!< \brief Signed integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat3x2							imat3x2; //!< \brief Signed integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat3x3							imat3x3; //!< \brief Signed integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat3x4							imat3x4; //!< \brief Signed integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat4x2							imat4x2; //!< \brief Signed integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat4x3							imat4x3; //!< \brief Signed integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_imat4x4							imat4x4; //!< \brief Signed integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)
#endif//GLM_PRECISION

#if(defined(GLM_PRECISION) && (GLM_PRECISION & GLM_PRECISION_HIGHP_UINT))
		typedef highp_umat2								umat2; //!< \brief Unsigned integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat3								umat3; //!< \brief Unsigned integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat4								umat4; //!< \brief Unsigned integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat2x2							umat2x2; //!< \brief Unsigned integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat2x3							umat2x3; //!< \brief Unsigned integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat2x4							umat2x4; //!< \brief Unsigned integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat3x2							umat3x2; //!< \brief Unsigned integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat3x3							umat3x3; //!< \brief Unsigned integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat3x4							umat3x4; //!< \brief Unsigned integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat4x2							umat4x2; //!< \brief Unsigned integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat4x3							umat4x3; //!< \brief Unsigned integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef highp_umat4x4							umat4x4; //!< \brief Unsigned integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

#elif(defined(GLM_PRECISION) && (GLM_PRECISION & GLM_PRECISION_LOWP_UINT))
		typedef lowp_umat2								umat2; //!< \brief Unsigned integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat3								umat3; //!< \brief Unsigned integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat4								umat4; //!< \brief Unsigned integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat2x2							umat2x2; //!< \brief Unsigned integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat2x3							umat2x3; //!< \brief Unsigned integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat2x4							umat2x4; //!< \brief Unsigned integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat3x2							umat3x2; //!< \brief Unsigned integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat3x3							umat3x3; //!< \brief Unsigned integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat3x4							umat3x4; //!< \brief Unsigned integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat4x2							umat4x2; //!< \brief Unsigned integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat4x3							umat4x3; //!< \brief Unsigned integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef lowp_umat4x4							umat4x4; //!< \brief Unsigned integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)

#else //if(defined(GLM_PRECISION) && (GLM_PRECISION & GLM_PRECISION_MEDIUMP_UINT))
		typedef mediump_umat2							umat2; //!< \brief Unsigned integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat3							umat3; //!< \brief Unsigned integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat4							umat4; //!< \brief Unsigned integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat2x2							umat2x2; //!< \brief Unsigned integer 2x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat2x3							umat2x3; //!< \brief Unsigned integer 2x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat2x4							umat2x4; //!< \brief Unsigned integer 2x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat3x2							umat3x2; //!< \brief Unsigned integer 3x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat3x3							umat3x3; //!< \brief Unsigned integer 3x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat3x4							umat3x4; //!< \brief Unsigned integer 3x4 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat4x2							umat4x2; //!< \brief Unsigned integer 4x2 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat4x3							umat4x3; //!< \brief Unsigned integer 4x3 matrix. (from GLM_GTC_matrix_integer extension)
		typedef mediump_umat4x4							umat4x4; //!< \brief Unsigned integer 4x4 matrix. (from GLM_GTC_matrix_integer extension)
#endif//GLM_PRECISION

		///@}

	}//namespace matrix_integer
	}//namespace gtc
}//namespace glm

namespace glm{using namespace gtc::matrix_integer;}

#endif//glm_gtc_matrix_integer
