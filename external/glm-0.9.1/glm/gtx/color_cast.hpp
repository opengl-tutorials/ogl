///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-06-21
// Updated : 2009-06-05
// Licence : This source is under MIT License
// File    : glm/gtx/color_cast.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_number_precision
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_color_cast
#define glm_gtx_color_cast

// Dependency:
#include "../glm.hpp"
#include "../gtx/number_precision.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_color_cast extension included")
#endif

namespace glm
{
	namespace test{
		void main_ext_gtx_color_cast();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_color_cast extension: Conversion between two color types
	namespace color_cast
	{
		using namespace gtx::number_precision;

		/// \addtogroup gtx_color_cast
		///@{

		//! Conversion of a floating value into a 8bit unsigned int value. 
		//! From GLM_GTX_color_cast extension.
		template <typename valType> gtc::type_precision::uint8 u8channel_cast(valType a);

		//! Conversion of a floating value into a 16bit unsigned int value. 
		//! From GLM_GTX_color_cast extension.
		template <typename valType>	gtc::type_precision::uint16 u16channel_cast(valType a);

		template <typename T> gtc::type_precision::uint32 u32_rgbx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint32 u32_xrgb_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint32 u32_bgrx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint32 u32_xbgr_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::uint32 u32_rgba_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint32 u32_argb_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint32 u32_bgra_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint32 u32_abgr_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::uint64 u64_rgbx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint64 u64_xrgb_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint64 u64_bgrx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint64 u64_xbgr_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::uint64 u64_rgba_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint64 u64_argb_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint64 u64_bgra_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::uint64 u64_abgr_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)

		template <typename T> gtx::number_precision::f16vec1 f16_channel_cast(T a);	//!< \brief Conversion of a u8 or u16 value to a single channel floating value. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::f16vec3 f16_rgbx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f16vec3 f16_xrgb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f16vec3 f16_bgrx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f16vec3 f16_xbgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::f16vec4 f16_rgba_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f16vec4 f16_argb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f16vec4 f16_bgra_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f16vec4 f16_abgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)

		template <typename T> gtx::number_precision::f32vec1 f32_channel_cast(T a);	//!< \brief Conversion of a u8 or u16 value to a single channel floating value. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::f32vec3 f32_rgbx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f32vec3 f32_xrgb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f32vec3 f32_bgrx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f32vec3 f32_xbgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::f32vec4 f32_rgba_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f32vec4 f32_argb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f32vec4 f32_bgra_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f32vec4 f32_abgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)

		template <typename T> gtx::number_precision::f64vec1 f64_channel_cast(T a);	//!< \brief Conversion of a u8 or u16 value to a single channel floating value. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::f64vec3 f64_rgbx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f64vec3 f64_xrgb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f64vec3 f64_bgrx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f64vec3 f64_xbgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)

		template <typename T> gtc::type_precision::f64vec4 f64_rgba_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f64vec4 f64_argb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f64vec4 f64_bgra_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
		template <typename T> gtc::type_precision::f64vec4 f64_abgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)

		///@}
	}//namespace color_space
	}//namespace gtx
}//namespace glm

#include "color_cast.inl"

namespace glm{using namespace gtx::color_cast;}

#endif//glm_gtx_color_cast
