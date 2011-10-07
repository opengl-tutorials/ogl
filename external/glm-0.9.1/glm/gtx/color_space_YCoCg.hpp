///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-28
// Updated : 2008-10-28
// Licence : This source is under MIT License
// File    : glm/gtx/color_space_YCoCg.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_color_space_YCoCg
#define glm_gtx_color_space_YCoCg

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_color_space_YCoCg extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_color_space_YCoCg();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_color_space_YCoCg extension: RGB to YCoCg conversions and operations
    namespace color_space_YCoCg
    {
		/// \addtogroup gtx_color_space_YCoCg
		///@{

        //! Convert a color from RGB color space to YCoCg color space.
		//! From GLM_GTX_color_space_YCoCg extension.
		template <typename valType> 
		detail::tvec3<valType> rgb2YCoCg(
			detail::tvec3<valType> const & rgbColor);

        //! Convert a color from YCoCg color space to RGB color space.
		//! From GLM_GTX_color_space_YCoCg extension.
        template <typename valType> 
		detail::tvec3<valType> YCoCg2rgb(
			detail::tvec3<valType> const & YCoCgColor);

        //! Convert a color from RGB color space to YCoCgR color space.
		//! \see "YCoCg-R: A Color Space with RGB Reversibility and Low Dynamic Range"
		//! From GLM_GTX_color_space_YCoCg extension.
		template <typename valType> 
		detail::tvec3<valType> rgb2YCoCgR(
			detail::tvec3<valType> const & rgbColor);

        //! Convert a color from YCoCgR color space to RGB color space.
		//! \see "YCoCg-R: A Color Space with RGB Reversibility and Low Dynamic Range"
		//! From GLM_GTX_color_space_YCoCg extension.
        template <typename valType> 
		detail::tvec3<valType> YCoCgR2rgb(
			detail::tvec3<valType> const & YCoCgColor);

		///@}
	}//namespace color_space_YCoCg
	}//namespace gtx
}//namespace glm

#include "color_space_YCoCg.inl"

namespace glm{using namespace gtx::color_space_YCoCg;}

#endif//glm_gtx_color_space_YCoCg
