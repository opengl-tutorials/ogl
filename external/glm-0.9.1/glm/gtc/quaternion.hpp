///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-21
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/gtc/quaternion.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_half_float
///////////////////////////////////////////////////////////////////////////////////////////////////
// ToDo:
// - Study constructors with angles and axis
// - Study constructors with vec3 that are the imaginary component of quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_quaternion
#define glm_gtc_quaternion

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_quaternion extension included")
#endif

namespace glm
{
	namespace test{
		bool main_gtc_quaternion();
	}//namespace test

	namespace detail
	{
		//! \brief Template for quaternion. 
		//! From GLM_GTC_quaternion extension.
		/// \ingroup gtc_quaternion
		template <typename T> 
		struct tquat// : public genType<T, tquat>
		{
			typedef T value_type;

		public:
			value_type x, y, z, w;

			// Constructors
			tquat();
			explicit tquat(
				value_type const & s, 
				tvec3<T> const & v);
			explicit tquat(
				value_type const & w, 
				value_type const & x, 
				value_type const & y, 
				value_type const & z);

			// Convertions
			//explicit tquat(valType const & pitch, valType const & yaw, valType const & roll);
			//! pitch, yaw, roll
			explicit tquat(
				tvec3<T> const & eulerAngles);
			explicit tquat(
				tmat3x3<T> const & m);
			explicit tquat(
				tmat4x4<T> const & m);

			// Accesses
			value_type & operator[](int i);
			value_type const & operator[](int i) const;

			// Operators
			tquat<T> & operator*=(value_type const & s);
			tquat<T> & operator/=(value_type const & s);
		};

		template <typename T> 
		detail::tquat<T> operator- (
			detail::tquat<T> const & q);

		template <typename T> 
		detail::tquat<T> operator* ( 
			detail::tquat<T> const & q, 
			detail::tquat<T> const & p); 

		template <typename T> 
		detail::tvec3<T> operator* (
			detail::tquat<T> const & q, 
			detail::tvec3<T> const & v);

		template <typename T> 
		detail::tvec3<T> operator* (
			detail::tvec3<T> const & v,
			detail::tquat<T> const & q);

		template <typename T> 
		detail::tvec4<T> operator* (
			detail::tquat<T> const & q, 
			detail::tvec4<T> const & v);

		template <typename T> 
		detail::tvec4<T> operator* (
			detail::tvec4<T> const & v,
			detail::tquat<T> const & q);

		template <typename T> 
		detail::tquat<T> operator* (
			detail::tquat<T> const & q, 
			typename detail::tquat<T>::value_type const & s);

		template <typename T> 
		detail::tquat<T> operator* (
			typename detail::tquat<T>::value_type const & s,
			detail::tquat<T> const & q);

		template <typename T> 
		detail::tquat<T> operator/ (
			detail::tquat<T> const & q, 
			typename detail::tquat<T>::value_type const & s);

	} //namespace detail

	namespace gtc{
	//! GLM_GTC_quaternion extension: Quaternion types and functions
    namespace quaternion
    {
		/// \addtogroup gtc_quaternion
		///@{

		//! Returns the length of the quaternion x. 
		//! From GLM_GTC_quaternion extension.
        template <typename T> 
		typename detail::tquat<T>::value_type length(
			detail::tquat<T> const & q);

        //! Returns the normalized quaternion of from x. 
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		detail::tquat<T> normalize(
			detail::tquat<T> const & q);
		
        //! Returns dot product of q1 and q2, i.e., q1[0] * q2[0] + q1[1] * q2[1] + ... 
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		typename detail::tquat<T>::value_type dot(
			detail::tquat<T> const & q1, 
			detail::tquat<T> const & q2);

        //! Returns the cross product of q1 and q2. 
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		GLM_DEPRECATED detail::tquat<T> cross(
			detail::tquat<T> const & q1, 
			detail::tquat<T> const & q2);
		
		//! Returns a SLERP interpolated quaternion of x and y according a. 
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		detail::tquat<T> mix(
			detail::tquat<T> const & x, 
			detail::tquat<T> const & y, 
			typename detail::tquat<T>::value_type const & a);
		
		//! Returns the q conjugate. 
		//! From GLM_GTC_quaternion extension.
        template <typename T> 
		detail::tquat<T> conjugate(
			detail::tquat<T> const & q);

		//! Returns the q inverse. 
		//! From GLM_GTC_quaternion extension.
        template <typename T> 
		detail::tquat<T> inverse(
			detail::tquat<T> const & q);

		//! Rotates a quaternion from an vector of 3 components axis and an angle expressed in degrees.
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		detail::tquat<T> rotate(
			detail::tquat<T> const & q, 
			typename detail::tquat<T>::value_type const & angle, 
			detail::tvec3<T> const & v);

		//! Converts a quaternion to a 3 * 3 matrix. 
		//! From GLM_GTC_quaternion extension.
        template <typename T> 
		detail::tmat3x3<T> mat3_cast(
			detail::tquat<T> const & x);

		//! Converts a quaternion to a 4 * 4 matrix. 
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		detail::tmat4x4<T> mat4_cast(
			detail::tquat<T> const & x);

		//! Converts a 3 * 3 matrix to a quaternion. 
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		detail::tquat<T> quat_cast(
			detail::tmat3x3<T> const & x);

		//! Converts a 4 * 4 matrix to a quaternion. 
		//! From GLM_GTC_quaternion extension.
		template <typename T> 
		detail::tquat<T> quat_cast(
			detail::tmat4x4<T> const & x);

		//! Quaternion of floating-point numbers. 
		//! From GLM_GTC_quaternion extension.
        typedef detail::tquat<float> quat;

		//! Quaternion of half-precision floating-point numbers.
		//! From GLM_GTC_quaternion extension.
		typedef detail::tquat<detail::thalf>	hquat;

		//! Quaternion of single-precision floating-point numbers. 
		//! From GLM_GTC_quaternion extension.
		typedef detail::tquat<float>	fquat;

		//! Quaternion of double-precision floating-point numbers. 
		//! From GLM_GTC_quaternion extension.
		typedef detail::tquat<double>	dquat;

		///@}

    }//namespace quaternion
    }//namespace gtc
} //namespace glm

#include "quaternion.inl"

namespace glm{using namespace gtc::quaternion;}

#endif//glm_gtc_quaternion
