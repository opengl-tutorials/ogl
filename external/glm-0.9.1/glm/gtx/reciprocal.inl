///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-09
// Updated : 2008-10-09
// Licence : This source is under MIT License
// File    : glm/gtx/reciprocal.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace reciprocal{

// sec
template <typename genType>
inline genType sec
(
	genType const & angle
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sec' only accept floating-point values");

	return genType(1) / glm::cos(angle);
}

template <typename valType>
inline detail::tvec2<valType> sec
(
	detail::tvec2<valType> const & angle
)
{
    return detail::tvec2<valType>(
        sec(angle.x),
        sec(angle.y));
}

template <typename valType>
inline detail::tvec3<valType> sec
(
	detail::tvec3<valType> const & angle
)
{
    return detail::tvec3<valType>(
        sec(angle.x),
        sec(angle.y),
        sec(angle.z));
}

template <typename valType>
inline detail::tvec4<valType> sec
(
	detail::tvec4<valType> const & angle
)
{
    return detail::tvec4<valType>(
        sec(angle.x),
        sec(angle.y),
        sec(angle.z),
        sec(angle.w));
}

// csc
template <typename genType>
inline genType csc
(
	genType const & angle
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'csc' only accept floating-point values");

    return genType(1) / glm::sin(angle);
}

template <typename valType>
inline detail::tvec2<valType> csc
(
	detail::tvec2<valType> const & angle
)
{
    return detail::tvec2<valType>(
        csc(angle.x),
        csc(angle.y));
}

template <typename valType>
inline detail::tvec3<valType> csc
(
	detail::tvec3<valType> const & angle
)
{
    return detail::tvec3<valType>(
        csc(angle.x),
        csc(angle.y),
        csc(angle.z));
}

template <typename valType>
inline detail::tvec4<valType> csc
(	
	detail::tvec4<valType> const & angle
)
{
    return detail::tvec4<valType>(
        csc(angle.x),
        csc(angle.y),
        csc(angle.z),
        csc(angle.w));
}

// cot
template <typename genType>
inline genType cot
(
	genType const & angle
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'cot' only accept floating-point values");

	return genType(1) / glm::tan(angle);
}

template <typename valType>
inline detail::tvec2<valType> cot
(
	detail::tvec2<valType> const & angle
)
{
    return detail::tvec2<valType>(
        cot(angle.x),
        cot(angle.y));
}

template <typename valType>
inline detail::tvec3<valType> cot
(
	detail::tvec3<valType> const & angle
)
{
    return detail::tvec3<valType>(
        cot(angle.x),
        cot(angle.y),
        cot(angle.z));
}

template <typename valType>
inline detail::tvec4<valType> cot
(
	detail::tvec4<valType> const & angle
)
{
    return detail::tvec4<valType>(
        cot(angle.x),
        cot(angle.y),
        cot(angle.z),
        cot(angle.w));
}

// asec
template <typename genType>
inline genType asec
(
	genType const & x
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asec' only accept floating-point values");
	
	return acos(genType(1) / x);
}

template <typename valType>
inline detail::tvec2<valType> asec
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        asec(x.x),
        asec(x.y));
}

template <typename valType>
inline detail::tvec3<valType> asec
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        asec(x.x),
        asec(x.y),
        asec(x.z));
}

template <typename valType>
inline detail::tvec4<valType> asec
(
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        asec(x.x),
        asec(x.y),
        asec(x.z),
        asec(x.w));
}

// acsc
template <typename genType>
inline genType acsc
(
	genType const & x
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acsc' only accept floating-point values");

	return asin(genType(1) / x);
}

template <typename valType>
inline detail::tvec2<valType> acsc
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        acsc(x.x),
        acsc(x.y));
}

template <typename valType>
inline detail::tvec3<valType> acsc
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        acsc(x.x),
        acsc(x.y),
        acsc(x.z));
}

template <typename valType>
inline detail::tvec4<valType> acsc
(	
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        acsc(x.x),
        acsc(x.y),
        acsc(x.z),
        acsc(x.w));
}

// acot
template <typename genType>
inline genType acot
(
	genType const & x
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acot' only accept floating-point values");

	genType const pi_over_2 = genType(3.1415926535897932384626433832795 / 2.0);
	return pi_over_2 - atan(x);
}

template <typename valType>
inline detail::tvec2<valType> acot
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        acot(x.x),
        acot(x.y));
}

template <typename valType>
inline detail::tvec3<valType> acot
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        acot(x.x),
        acot(x.y),
        acot(x.z));
}

template <typename valType>
inline detail::tvec4<valType> acot
(
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        acot(x.x),
        acot(x.y),
        acot(x.z),
        acot(x.w));
}

// sech
template <typename genType>
inline genType sech
(
	genType const & angle
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sech' only accept floating-point values");

	return genType(1) / glm::cosh(angle);
}

template <typename valType>
inline detail::tvec2<valType> sech
(
	detail::tvec2<valType> const & angle
)
{
    return detail::tvec2<valType>(
        sech(angle.x),
        sech(angle.y));
}

template <typename valType>
inline detail::tvec3<valType> sech
(
	detail::tvec3<valType> const & angle
)
{
    return detail::tvec3<valType>(
        sech(angle.x),
        sech(angle.y),
        sech(angle.z));
}

template <typename valType>
inline detail::tvec4<valType> sech
(
	detail::tvec4<valType> const & angle
)
{
    return detail::tvec4<valType>(
        sech(angle.x),
        sech(angle.y),
        sech(angle.z),
        sech(angle.w));
}

// csch
template <typename genType>
inline genType csch
(
	genType const & angle
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'csch' only accept floating-point values");

    return genType(1) / glm::sinh(angle);
}

template <typename valType>
inline detail::tvec2<valType> csch
(
	detail::tvec2<valType> const & angle
)
{
    return detail::tvec2<valType>(
        csch(angle.x),
        csch(angle.y));
}

template <typename valType>
inline detail::tvec3<valType> csch
(
	detail::tvec3<valType> const & angle
)
{
    return detail::tvec3<valType>(
        csch(angle.x),
        csch(angle.y),
        csch(angle.z));
}

template <typename valType>
inline detail::tvec4<valType> csch
(	
	detail::tvec4<valType> const & angle
)
{
    return detail::tvec4<valType>(
        csch(angle.x),
        csch(angle.y),
        csch(angle.z),
        csch(angle.w));
}

// coth
template <typename genType>
inline genType coth
(
	genType const & angle
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'coth' only accept floating-point values");

	return glm::cosh(angle) / glm::sinh(angle);
}

template <typename valType>
inline detail::tvec2<valType> coth
(
	detail::tvec2<valType> const & angle
)
{
    return detail::tvec2<valType>(
        coth(angle.x),
        coth(angle.y));
}

template <typename valType>
inline detail::tvec3<valType> coth
(
	detail::tvec3<valType> const & angle
)
{
    return detail::tvec3<valType>(
        coth(angle.x),
        coth(angle.y),
        coth(angle.z));
}

template <typename valType>
inline detail::tvec4<valType> coth
(
	detail::tvec4<valType> const & angle
)
{
    return detail::tvec4<valType>(
        coth(angle.x),
        coth(angle.y),
        coth(angle.z),
        coth(angle.w));
}

// asech
template <typename genType>
inline genType asech
(
	genType const & x
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asech' only accept floating-point values");

	return acosh(genType(1) / x);
}

template <typename valType>
inline detail::tvec2<valType> asech
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        asech(x.x),
        asech(x.y));
}

template <typename valType>
inline detail::tvec3<valType> asech
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        asech(x.x),
        asech(x.y),
        asech(x.z));
}

template <typename valType>
inline detail::tvec4<valType> asech
(
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        asech(x.x),
        asech(x.y),
        asech(x.z),
        asech(x.w));
}

// acsch
template <typename genType>
inline genType acsch
(
	genType const & x
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acsch' only accept floating-point values");

    return asinh(genType(1) / x);
}

template <typename valType>
inline detail::tvec2<valType> acsch
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        acsch(x.x),
        acsch(x.y));
}

template <typename valType>
inline detail::tvec3<valType> acsch
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        acsch(x.x),
        acsch(x.y),
        acsch(x.z));
}

template <typename valType>
inline detail::tvec4<valType> acsch
(	
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        acsch(x.x),
        acsch(x.y),
        acsch(x.z),
        acsch(x.w));
}

// acoth
template <typename genType>
inline genType acoth
(
	genType const & x
)
{
	GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acoth' only accept floating-point values");

	return atanh(genType(1) / x);
}

template <typename valType>
inline detail::tvec2<valType> acoth
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        acoth(x.x),
        acoth(x.y));
}

template <typename valType>
inline detail::tvec3<valType> acoth
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        acoth(x.x),
        acoth(x.y),
        acoth(x.z));
}

template <typename valType>
inline detail::tvec4<valType> acoth
(
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        acoth(x.x),
        acoth(x.y),
        acoth(x.z),
        acoth(x.w));
}

}//namespace reciprocal
}//namespace gtx
}//namespace glm
