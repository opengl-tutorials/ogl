///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-16
// Updated : 2007-08-30
// Licence : This source is under MIT License
// File    : glm/gtx/random.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_vecx
// - GLM_GTX_half_float
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_random
#define glm_gtx_random

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_random extension included")
#endif

namespace glm{
namespace gtx{
//! GLM_GTX_random extension: Generate random number from various distribution methods
namespace random
{
	/// \addtogroup gtx_random
	///@{

	//! Generate a random number in the interval [-1, 1], according a linear distribution.
	//! From GLM_GTX_random extension.
    template <typename T> T signedRand1();
	
	template <> float signedRand1();                                                                                     //!< \brief Generate a random number in the interval [-1, 1], according a linear distribution (From GLM_GTX_random extension)
    template <> double signedRand1();                                                                                   //!< \brief Generate a random number in the interval [-1, 1], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> signedRand2();                                                                           //!< \brief Generate 2 random numbers in the interval [-1, 1], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> signedRand3();                                                                           //!< \brief Generate 3 random numbers in the interval [-1, 1], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> signedRand4();                                                                           //!< \brief Generate 4 random numbers in the interval [-1, 1], according a linear distribution (From GLM_GTX_random extension)
    
	template <typename T> detail::tvec2<T> normalizedRand2();                                                                          //!< \brief Generate a normalized 2D vector regulary distribute on a circle (From GLM_GTX_random extension)
	template <typename T> detail::tvec2<T> normalizedRand2(T Min, T Max);                                                         //!< \brief Generate a scaled and normalized 2D vector regulary distribute on a circle (From GLM_GTX_random extension)
	template <typename T> detail::tvec3<T> normalizedRand3();                                                                          //!< \brief Generate a normalized 3D vector regulary distribute on a sphere (From GLM_GTX_random extension)
	template <typename T> detail::tvec3<T> normalizedRand3(T Min, T Max);                                                        //!< \brief Generate a scaled and normalized 3D vector regulary distribute on a sphere (From GLM_GTX_random extension)

    template <typename T> T compRand1();                                                                                       //!< \brief Generate a random number in the interval [0, 1], according a linear distribution (From GLM_GTX_random extension)
	template <> float compRand1();                                                                                         //!< \brief Generate a random number in the interval [0, 1], according a linear distribution (From GLM_GTX_random extension)
    template <> double compRand1();                                                                                      //!< \brief Generate a random number in the interval [0, 1], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> T compRand1(T Min, T Max);                                                                     //!< \brief Generate a random number in the interval [Min, Max], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> compRand2(T Min, T Max);                                                              //!< \brief Generate 2 random numbers in the interval [Min, Max], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> compRand3(T Min, T Max);                                                             //!< \brief Generate 3 random numbers in the interval [Min, Max], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> compRand4(T Min, T Max);                                                              //!< \brief Generate 4 random numbers in the interval [Min, Max], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> compRand2(const detail::tvec2<T>& Min, const detail::tvec2<T>& Max);                                //!< \brief Generate 2 random numbers in the interval [Min, Max], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> compRand3(const detail::tvec3<T>& Min, const detail::tvec3<T>& Max);                                //!< \brief Generate 3 random numbers in the interval [Min, Max], according a linear distribution (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> compRand4(const detail::tvec4<T>& Min, const detail::tvec4<T>& Max);                                //!< \brief Generate 4 random numbers in the interval [Min, Max], according a linear distribution (From GLM_GTX_random extension)

    template <typename T> detail::tvec2<T> vecRand2();                                                                                 //!< \brief Generate a random normalized 2 component vector. It's a spherical uniform distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> vecRand2(T MinRadius, T MaxRadius);                                        //!< \brief Generate a random normalized 2 component vector. It's a spherical uniform distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> vecRand3();                                                                                 //!< \brief Generate a random normalized 3 component vector. It's a spherical uniform distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> vecRand3(T MinRadius, T MaxRadius);                                        //!< \brief Generate a random normalized 3 component vector. It's a spherical uniform distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> vecRand4();                                                                                 //!< \brief Generate a random normalized 4 component vector. It's a spherical uniform distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> vecRand4(T MinRadius, T MaxRadius);                                        //!< \brief Generate a random normalized 4 component vector. It's a spherical uniform distribution. (From GLM_GTX_random extension)

    template <typename T> T gaussRand1(T mean, T std_deviation);                                           //!< \brief Gererate a random floating number according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> gaussRand2(T mean, T std_deviation);                                   //!< \brief Gererate 2 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> gaussRand3(T mean, T std_deviation);                                   //!< \brief Gererate 3 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> gaussRand4(T mean, T std_deviation);                                   //!< \brief Gererate 4 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> gaussRand2(const detail::tvec2<T>& mean, T std_deviation);                    //!< \brief Gererate 2 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> gaussRand3(const detail::tvec3<T>& mean, T std_deviation);                    //!< \brief Gererate 3 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> gaussRand4(const detail::tvec4<T>& mean, T std_deviation);                    //!< \brief Gererate 4 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> gaussRand2(T  mean, const detail::tvec2<T>& std_deviation);                   //!< \brief Gererate 2 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> gaussRand3(T  mean, const detail::tvec3<T>& std_deviation);                   //!< \brief Gererate 3 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> gaussRand4(T  mean, const detail::tvec4<T>& std_deviation);                   //!< \brief Gererate 4 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec2<T> gaussRand2(const detail::tvec2<T>& mean, const detail::tvec2<T>& std_deviation);     //!< \brief Gererate 2 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec3<T> gaussRand3(const detail::tvec3<T>& mean, const detail::tvec3<T>& std_deviation);     //!< \brief Gererate 3 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)
    template <typename T> detail::tvec4<T> gaussRand4(const detail::tvec4<T>& mean, const detail::tvec4<T>& std_deviation);     //!< \brief Gererate 4 random floating numbers according a Gauss distribution. (From GLM_GTX_random extension)

	///@}
}//namespace random
}//namespace gtx
}//namespace glm

#include "random.inl"

namespace glm{using namespace gtx::random;}

#endif//glm_gtx_random
