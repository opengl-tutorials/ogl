///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-05-21
// Licence : This source is under MIT License
// File    : glm/gtx/quaternion.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////
// ToDo:
// - Study constructors with angles and axis
// - Study constructors with vec3 that are the imaginary component of quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_quaternion
#define glm_gtx_quaternion

// Dependency:
#include "../glm.hpp"
#include "../gtc/quaternion.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_quaternion extension included")
#endif

namespace glm
{
	namespace gtx{
	//! GLM_GTX_quaternion extension: Quaternion types and functions
    namespace quaternion
    {
		using namespace gtc::quaternion;

		/// \addtogroup gtx_quaternion
		///@{

		//! Compute a cross product between a quaternion and a vector. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tvec3<valType> cross(
			detail::tquat<valType> const & q, 
			detail::tvec3<valType> const & v);

		//! Compute a cross product between a vector and a quaternion.
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tvec3<valType> cross(
			detail::tvec3<valType> const & v, 
			detail::tquat<valType> const & q);

		//! Compute a point on a path according squad equation. 
		//! q1 and q2 are control points; s1 and s2 are intermediate control points.
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tquat<valType> squad(
			detail::tquat<valType> const & q1, 
			detail::tquat<valType> const & q2, 
			detail::tquat<valType> const & s1, 
			detail::tquat<valType> const & s2, 
			valType const & h);

		//! Returns an intermediate control point for squad interpolation.
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tquat<valType> intermediate(
			detail::tquat<valType> const & prev, 
			detail::tquat<valType> const & curr, 
			detail::tquat<valType> const & next);

		//! Returns a exp of a quaternion. 
		//! From GLM_GTX_quaternion extension.
        template <typename valType> 
		detail::tquat<valType> exp(
			detail::tquat<valType> const & q, 
			valType const & exponent);

		//! Returns a log of a quaternion. 
		//! From GLM_GTX_quaternion extension.
        template <typename valType> 
		detail::tquat<valType> log(
			detail::tquat<valType> const & q);

		//! Returns x raised to the y power.
		//! From GLM_GTX_quaternion extension.
        template <typename valType> 
		detail::tquat<valType> pow(
			detail::tquat<valType> const & x, 
			valType const & y);

		//! Returns quarternion square root.
		//! From GLM_GTX_quaternion extension.
		//template <typename valType> 
		//detail::tquat<valType> sqrt(
		//	detail::tquat<valType> const & q);

		//! Rotates a 3 components vector by a quaternion. 
		//! From GLM_GTX_transform extension.
		template <typename valType> 
		detail::tvec3<valType> rotate(
			detail::tquat<valType> const & q, 
			detail::tvec3<valType> const & v);

        //! Rotates a 4 components vector by a quaternion.
		//! From GLM_GTX_transform extension.
		template <typename valType> 
		detail::tvec4<valType> rotate(
			detail::tquat<valType> const & q, 
			detail::tvec4<valType> const & v);
		
        //! Returns the q rotation angle. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		valType angle(
			detail::tquat<valType> const & x);

		//! Returns the q rotation axis. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tvec3<valType> axis(
			detail::tquat<valType> const & x);

		//! Build a quaternion from an angle and an axis. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tquat<valType> angleAxis(
			valType const & angle, 
			valType const & x, 
			valType const & y, 
			valType const & z);

        //! Build a quaternion from an angle and an axis.
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tquat<valType> angleAxis(
			valType const & angle, 
			detail::tvec3<valType> const & v);

		//! Extract the real component of a quaternion.
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		valType extractRealComponent(
			detail::tquat<valType> const & q);

        //! Returns roll value of euler angles. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		valType roll(
			detail::tquat<valType> const & x);

		//! Returns pitch value of euler angles. 
		//! From GLM_GTX_quaternion extension.
        template <typename valType> 
		valType pitch(
			detail::tquat<valType> const & x);

        //! Returns yaw value of euler angles. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		valType yaw(
			detail::tquat<valType> const & x);
		
		//! Returns euler angles, yitch as x, yaw as y, roll as z. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tvec3<valType> eularAngles(
			detail::tquat<valType> const & x);

		//! Converts a quaternion to a 3 * 3 matrix. 
		//! From GLM_GTX_quaternion extension.
        template <typename valType> 
		detail::tmat3x3<valType> toMat3(
			detail::tquat<valType> const & x){return gtc::quaternion::mat3_cast(x);}

		//! Converts a quaternion to a 4 * 4 matrix. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tmat4x4<valType> toMat4(
			detail::tquat<valType> const & x){return gtc::quaternion::mat4_cast(x);}

		//! Converts a 3 * 3 matrix to a quaternion. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tquat<valType> toQuat(
			detail::tmat3x3<valType> const & x){return gtc::quaternion::quat_cast(x);}

		//! Converts a 4 * 4 matrix to a quaternion. 
		//! From GLM_GTX_quaternion extension.
		template <typename valType> 
		detail::tquat<valType> toQuat(
			detail::tmat4x4<valType> const & x){return gtc::quaternion::quat_cast(x);}

		///@}

    }//namespace quaternion
    }//namespace gtx
} //namespace glm

#include "quaternion.inl"

namespace glm{using namespace gtx::quaternion;}

#endif//glm_gtx_quaternion
