///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-05-10
// Updated : 2009-06-04
// Licence : This source is under MIT License
// File    : glm/gtx/number_precision.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_type_precision
// - GLM_GTC_quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_number_precision
#define glm_gtx_number_precision

// Dependency:
#include "../glm.hpp"
#include "../gtc/type_precision.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_number_precision extension included")
#endif

namespace glm{
namespace gtx{
//! GLM_GTX_number_precision extension: Defined size types.
namespace number_precision
{
	using namespace gtc::type_precision;

	/////////////////////////////
	// Unsigned int vector types 

	/// \addtogroup gtx_number_precision
	///@{

	typedef u8			u8vec1;		//!< \brief 8bit unsigned integer scalar. (from GLM_GTX_number_precision extension)
	typedef u16			u16vec1;    //!< \brief 16bit unsigned integer scalar. (from GLM_GTX_number_precision extension)
	typedef u32			u32vec1;    //!< \brief 32bit unsigned integer scalar. (from GLM_GTX_number_precision extension)
	typedef u64			u64vec1;    //!< \brief 64bit unsigned integer scalar. (from GLM_GTX_number_precision extension)

	//////////////////////
	// Float vector types 

	typedef f16			f16vec1;    //!< \brief Half-precision floating-point scalar. (from GLM_GTX_number_precision extension)
	typedef f32			f32vec1;    //!< \brief Single-precision floating-point scalar. (from GLM_GTX_number_precision extension)
	typedef f64			f64vec1;    //!< \brief Single-precision floating-point scalar. (from GLM_GTX_number_precision extension)

	//////////////////////
	// Float matrix types 

	typedef f16			f16mat1;    //!< \brief Half-precision floating-point scalar. (from GLM_GTX_number_precision extension)
	typedef f16			f16mat1x1;	//!< \brief Half-precision floating-point scalar. (from GLM_GTX_number_precision extension)
	typedef f32			f32mat1;	//!< \brief Single-precision floating-point scalar. (from GLM_GTX_number_precision extension)
	typedef f32			f32mat1x1;	//!< \brief Single-precision floating-point scalar. (from GLM_GTX_number_precision extension)
	typedef f64			f64mat1;	//!< \brief Double-precision floating-point scalar. (from GLM_GTX_number_precision extension)
	typedef f64			f64mat1x1;	//!< \brief Double-precision floating-point scalar. (from GLM_GTX_number_precision extension)

	///@}
}//namespace number_precision
}//namespace gtx
}//namespace glm

#include "number_precision.inl"

namespace glm{using namespace gtx::number_precision;}

#endif//glm_gtx_number_precision
