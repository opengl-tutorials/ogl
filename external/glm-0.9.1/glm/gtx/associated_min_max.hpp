///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-03-10
// Updated : 2008-03-15
// Licence : This source is under MIT License
// File    : gtx_associated_min_max.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_extented_min_max
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_associated_min_max
#define glm_gtx_associated_min_max

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_associated_min_max extension included")
#endif

namespace glm
{
	namespace test{
		void main_gtx_associated_min_max();
	}//namespace test

	namespace gtx
	{
		//! GLM_GTX_associated_min_max extension: Min and max functions that return associated values not the compared onces.
		namespace associated_min_max
		{
			/// \addtogroup gtx_associated_min_max
			///@{

			//! \brief Min comparison between 2 variables
			template<typename genTypeT, typename genTypeU>
			genTypeU associatedMin(
				const genTypeT& x, const genTypeU& a, 
				const genTypeT& y, const genTypeU& b);

			//! \brief Min comparison between 3 variables
			template<typename genTypeT, typename genTypeU>
			genTypeU associatedMin(
				const genTypeT& x, const genTypeU& a, 
				const genTypeT& y, const genTypeU& b, 
				const genTypeT& z, const genTypeU& c);

			//! \brief Min comparison between 4 variables
			template<typename genTypeT, typename genTypeU>
			genTypeU associatedMin(
				const genTypeT& x, const genTypeU& a, 
				const genTypeT& y, const genTypeU& b, 
				const genTypeT& z, const genTypeU& c, 
				const genTypeT& w, const genTypeU& d);

			//! \brief Max comparison between 2 variables
			template<typename genTypeT, typename genTypeU>
			genTypeU associatedMax(
				const genTypeT& x, const genTypeU& a, 
				const genTypeT& y, const genTypeU& b);

			//! \brief Max comparison between 3 variables
			template<typename genTypeT, typename genTypeU>
			genTypeU associatedMax(
				const genTypeT& x, const genTypeU& a, 
				const genTypeT& y, const genTypeU& b, 
				const genTypeT& z, const genTypeU& c);

			//! \brief Max comparison between 4 variables
			template<typename genTypeT, typename genTypeU>
			genTypeU associatedMax(
				const genTypeT& x, const genTypeU& a, 
				const genTypeT& y, const genTypeU& b, 
				const genTypeT& z, const genTypeU& c, 
				const genTypeT& w, const genTypeU& d);
			///@}

		}//namespace associated_min_max

		bool test();
	}//namespace gtx
}//namespace glm

#include "associated_min_max.inl"

namespace glm{using namespace gtx::associated_min_max;}

#endif//glm_gtx_associated_min_max
