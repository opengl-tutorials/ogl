///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-07
// Updated : 2009-05-07
// Licence : This source is under MIT License
// File    : glm/gtx/number_precision.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_ocl_type
#define glm_gtx_ocl_type

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_ocl_type extension included")
#endif

namespace glm{
namespace gtx{
//! GLM_GTX_ocl_type extension: OpenCL types.
namespace ocl_type
{
	///////////////////////////
	// Scalar types 

	/// \addtogroup gtx_ocl_type
	///@{

	typedef detail::int8						cl_char;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::int16						cl_short;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::int32						cl_int;			//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::int64						cl_long;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	typedef detail::uint8						cl_uchar;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::uint16						cl_ushort;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::uint32						cl_uint;		//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::uint64						cl_ulong;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	typedef detail::float16						cl_half;	//!< \brief Half-precision floating-point scalar. (from GLM_GTX_ocl_type extension)
	typedef detail::float32						cl_float;	//!< \brief Single-precision floating-point scalar. (from GLM_GTX_ocl_type extension)


	typedef detail::int8						cl_char1;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::int16						cl_short1;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::int32						cl_int1;			//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::int64						cl_long1;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	typedef detail::uint8						cl_uchar1;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::uint16						cl_ushort1;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::uint32						cl_uint1;		//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::uint64						cl_ulong1;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	//typedef detail::float16						cl_half1;	//!< \brief Half-precision floating-point scalar. (from GLM_GTX_ocl_type extension)
	typedef detail::float32						cl_float1;	//!< \brief Single-precision floating-point scalar. (from GLM_GTX_ocl_type extension)


	typedef detail::tvec2<detail::int8>			cl_char2;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec2<detail::int16>		cl_short2;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec2<detail::int32>		cl_int2;			//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec2<detail::int64>		cl_long2;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	typedef detail::tvec2<detail::uint8>		cl_uchar2;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec2<detail::uint16>		cl_ushort2;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec2<detail::uint32>		cl_uint2;		//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec2<detail::uint64>		cl_ulong2;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	//typedef detail::tvec2<detail::float16>		cl_half2;	//!< \brief Half-precision floating-point scalar. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec2<detail::float32>		cl_float2;	//!< \brief Single-precision floating-point scalar. (from GLM_GTX_ocl_type extension)


	typedef detail::tvec3<detail::int8>			cl_char3;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec3<detail::int16>		cl_short3;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec3<detail::int32>		cl_int3;			//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec3<detail::int64>		cl_long3;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	typedef detail::tvec3<detail::uint8>		cl_uchar3;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec3<detail::uint16>		cl_ushort3;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec3<detail::uint32>		cl_uint3;		//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec3<detail::uint64>		cl_ulong3;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	//typedef detail::tvec3<detail::float16>		cl_half3;	//!< \brief Half-precision floating-point scalar. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec3<detail::float32>		cl_float3;	//!< \brief Single-precision floating-point scalar. (from GLM_GTX_ocl_type extension)


	typedef detail::tvec4<detail::int8>			cl_char4;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::int16>		cl_short4;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::int32>		cl_int4;			//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::int64>		cl_long4;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::uint8>		cl_uchar4;		//!< \brief 8bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::uint16>		cl_ushort4;		//!< \brief 16bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::uint32>		cl_uint4;		//!< \brief 32bit signed integer. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::uint64>		cl_ulong4;		//!< \brief 64bit signed integer. (from GLM_GTX_ocl_type extension)

	//typedef detail::tvec4<detail::float16>		cl_half4;	//!< \brief Half-precision floating-point scalar. (from GLM_GTX_ocl_type extension)
	typedef detail::tvec4<detail::float32>		cl_float4;	//!< \brief Single-precision floating-point scalar. (from GLM_GTX_ocl_type extension)

	///@}

}//namespace ocl_type
}//namespace gtx
}//namespace glm

#include "ocl_type.inl"

namespace glm{using namespace gtx::ocl_type;}

#endif//glm_gtx_ocl_type
