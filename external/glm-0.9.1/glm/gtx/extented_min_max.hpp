///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-14
// Updated : 2010-02-19
// Licence : This source is under MIT License
// File    : gtx_extented_min_max.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_half_float
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_extented_min_max
#define glm_gtx_extented_min_max

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_extented_min_max extension included")
#endif

namespace glm
{
   	namespace test{
		void main_ext_gtx_extented_min_max();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_extented_min_max extension: Min and max functions for 3 to 4 parameters.
	namespace extented_min_max
	{
		/// \addtogroup gtx_extented_min_max
		///@{

		//< Return the minimum component-wise values of 3 inputs 
		//< From GLM_GTX_extented_min_max extension
		template <typename T>
		T min(
			T const & x, 
			T const & y, 
			T const & z);

		//< Return the minimum component-wise values of 3 inputs
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> min(
			C<T> const & x, 
			typename C<T>::value_type const & y, 
			typename C<T>::value_type const & z);

		//< Return the minimum component-wise values of 3 inputs 
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> min(
			C<T> const & x, 
			C<T> const & y, 
			C<T> const & z);

		//< Return the minimum component-wise values of 4 inputs 
		//< From GLM_GTX_extented_min_max extension
		template <typename T>
		T min(
			T const & x, 
			T const & y, 
			T const & z, 
			T const & w);

		//< Return the minimum component-wise values of 4 inputs 
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> min(
			C<T> const & x, 
			typename C<T>::value_type const & y, 
			typename C<T>::value_type const & z, 
			typename C<T>::value_type const & w);

		//< Return the minimum component-wise values of 4 inputs
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> min(
			C<T> const & x, 
			C<T> const & y, 
			C<T> const & z,
			C<T> const & w);

		//< Return the maximum component-wise values of 3 inputs 
		//< From GLM_GTX_extented_min_max extension
		template <typename T>
		T max(
			T const & x, 
			T const & y, 
			T const & z);

		//< Return the maximum component-wise values of 3 inputs
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> max(
			C<T> const & x, 
			typename C<T>::value_type const & y, 
			typename C<T>::value_type const & z);

		//< Return the maximum component-wise values of 3 inputs 
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> max(
			C<T> const & x, 
			C<T> const & y, 
			C<T> const & z);

		//< Return the maximum component-wise values of 4 inputs
		//< From GLM_GTX_extented_min_max extension
		template <typename T>
		T max(
			T const & x, 
			T const & y, 
			T const & z, 
			T const & w);

		//< Return the maximum component-wise values of 4 inputs 
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> max(
			C<T> const & x, 
			typename C<T>::value_type const & y, 
			typename C<T>::value_type const & z, 
			typename C<T>::value_type const & w);

		//< Return the maximum component-wise values of 4 inputs 
		//< From GLM_GTX_extented_min_max extension
		template 
		<
			typename T, 
			template <typename> class C
		>
		C<T> max(
			C<T> const & x, 
			C<T> const & y, 
			C<T> const & z, 
			C<T> const & w);

		///@}

	}//namespace extented_min_max
	}//namespace gtx
}//namespace glm

#include "extented_min_max.inl"

namespace glm{using namespace gtx::extented_min_max;}

#endif//glm_gtx_extented_min_max
