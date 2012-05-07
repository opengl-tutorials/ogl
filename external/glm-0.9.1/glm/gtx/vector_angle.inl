///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-30
// Updated : 2008-09-29
// Licence : This source is under MIT License
// File    : glm/gtx/vector_angle.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace vector_angle{

template <typename genType> 
inline typename genType::value_type angle
(
	genType const & x, 
	genType const & y
)
{
	return degrees(acos(dot(x, y)));
}

//! \todo epsilon is hard coded to 0.01
template <typename valType> 
inline valType orientedAngle
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y
)
{
    valType Angle = acos(dot(x, y));
    valType c = cos(Angle);
    valType s = sin(Angle);
    detail::tvec2<valType> TransformedVector = detail::tvec2<valType>(c * y.x - s * y.y, s * y.x + c * y.y);
    if(all(equalEpsilon(x, TransformedVector, valType(0.01))))
		return -glm::degrees(Angle);
    else
        return glm::degrees(Angle);
}

//! \todo epsilon is hard coded to 0.01
template <typename valType> 
inline valType orientedAngle
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y
)
{
    valType Angle = degrees(acos(dot(x, y)));
	detail::tvec3<valType> TransformedVector = glm::gtx::rotate_vector::rotate(y, Angle, glm::core::function::geometric::cross(x, y));
    if(all(equalEpsilon(x, TransformedVector, valType(0.01))))
		return -Angle;
    else
	   return Angle;
}

//! \todo epsilon is hard coded to 0.01
template <typename valType>
inline valType orientedAngle
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y
)
{
    valType Angle = degrees(acos(dot(x, y)));
    detail::tvec4<valType> TransformedVector = glm::gtx::rotate_vector::rotate(y, Angle, glm::core::function::geometric::cross(x, y));
    if(all(equalEpsilon(x, TransformedVector, valType(0.01))))
        return -Angle;
    else
        return Angle;
}

template <typename valType>
inline valType orientedAngleFromRef
(
    detail::tvec2<valType> const & x,
    detail::tvec2<valType> const & y,
	detail::tvec3<valType> const & ref
)
{
	valType Angle = glm::acos(glm::dot(x, y));

	if(glm::dot(ref, detail::tvec3<valType>(glm::cross(x, y), valType(0))) < valType(0))
		return -glm::degrees(Angle);
	else
		return glm::degrees(Angle);
}

template <typename valType>
inline valType orientedAngleFromRef
(
	detail::tvec3<valType> const & x,
	detail::tvec3<valType> const & y,
	detail::tvec3<valType> const & ref
)
{
	valType Angle = glm::acos(glm::dot(x, y));

	if(glm::dot(ref, glm::cross(x, y)) < valType(0))
		return -glm::degrees(Angle);
	else
		return glm::degrees(Angle);
}

template <typename valType>
inline valType orientedAngleFromRef
(
	detail::tvec4<valType> const & x,
	detail::tvec4<valType> const & y,
	detail::tvec3<valType> const & ref
)
{
	valType Angle = glm::acos(glm::dot(x, y));

	if(glm::dot(ref, glm::cross(detail::tvec3<valType>(x), detail::tvec3<valType>(y))) < valType(0))
		return -glm::degrees(Angle);
	else
		return glm::degrees(Angle);
}

}//namespace vector_angle
}//namespace gtx
}//namespace glm
