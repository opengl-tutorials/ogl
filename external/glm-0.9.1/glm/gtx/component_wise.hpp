///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-05-21
// Updated : 2007-05-21
// Licence : This source is under MIT License
// File    : glm/gtx/component_wise.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_component_wise
#define glm_gtx_component_wise

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_component_wise extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_component_wise();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_component_wise extension: Operations between components of a type
	namespace component_wise
	{
		/// \addtogroup gtx_component_wise
		///@{

		//! Add all vector components together. 
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compAdd(
			genType const & v);

		//! Multiply all vector components together. 
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compMul(
			genType const & v);

		//! Find the minimum value between single vector components.
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compMin(
			genType const & v);

		//! Find the maximum value between single vector components.
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compMax(
			genType const & v);

		///@}

	}//namespace component_wise
	}//namespace gtx
}//namespace glm

#include "component_wise.inl"

namespace glm{using namespace gtx::component_wise;}

#endif//glm_gtx_component_wise
