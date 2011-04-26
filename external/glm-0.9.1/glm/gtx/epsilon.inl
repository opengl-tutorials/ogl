///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2006-01-16
// Licence : This source is under MIT License
// File    : glm/gtx/epsilon.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace epsilon{

template <typename genType>
inline bool equalEpsilon
(
	genType const & x, 
	genType const & y, 
	genType const & epsilon
)
{
    return abs(x - y) < epsilon;
}

template <typename genType>
inline bool notEqualEpsilon
(
	genType const & x, 
	genType const & y, 
	genType const & epsilon
)
{
    return abs(x - y) >= epsilon;
}

template <typename valType>
inline detail::tvec2<bool> equalEpsilon
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y, 
	valType const & epsilon)
{
    return detail::tvec2<bool>(
        abs(x.x - y.x) < epsilon,
        abs(x.y - y.y) < epsilon);
}

template <typename valType>
inline detail::tvec3<bool> equalEpsilon
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y, 
	valType const & epsilon)
{
    return detail::tvec3<bool>(
        abs(x.x - y.x) < epsilon,
        abs(x.y - y.y) < epsilon,
        abs(x.z - y.z) < epsilon);
}

template <typename valType>
inline detail::tvec4<bool> equalEpsilon
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y, 
	valType const & epsilon
)
{
    return detail::tvec4<bool>(
        abs(x.x - y.x) < epsilon,
        abs(x.y - y.y) < epsilon,
        abs(x.z - y.z) < epsilon,
        abs(x.w - y.w) < epsilon);
}

template <typename valType>
inline detail::tvec2<bool> notEqualEpsilon
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y, 
	valType const & epsilon
)
{
    return detail::tvec2<bool>(
        abs(x.x - y.x) >= epsilon,
        abs(x.y - y.y) >= epsilon);
}

template <typename valType>
inline detail::tvec3<bool> notEqualEpsilon
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y, 
	valType const & epsilon
)
{
    return detail::tvec3<bool>(
        abs(x.x - y.x) >= epsilon,
        abs(x.y - y.y) >= epsilon,
        abs(x.z - y.z) >= epsilon);
}

template <typename valType>
inline detail::tvec4<bool> notEqualEpsilon
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y, 
	valType const & epsilon
)
{
    return detail::tvec4<bool>(
        abs(x.x - y.x) >= epsilon,
        abs(x.y - y.y) >= epsilon,
        abs(x.z - y.z) >= epsilon,
        abs(x.w - y.w) >= epsilon);
}

template <typename valType>
inline detail::tvec2<bool> equalEpsilon
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y, 
	detail::tvec2<valType> const & epsilon
)
{
    return detail::tvec2<bool>(
        abs(x.x - y.x) < epsilon.x,
        abs(x.y - y.y) < epsilon.y);
}

template <typename valType>
inline detail::tvec3<bool> equalEpsilon
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y, 
	detail::tvec3<valType> const & epsilon
)
{
    return detail::tvec3<bool>(
        abs(x.x - y.x) < epsilon.x,
        abs(x.y - y.y) < epsilon.y,
        abs(x.z - y.z) < epsilon.z);
}

template <typename valType>
inline detail::tvec4<bool> equalEpsilon
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y, 
	detail::tvec4<valType> const & epsilon
)
{
    return detail::tvec4<bool>(
        abs(x.x - y.x) < epsilon.x,
        abs(x.y - y.y) < epsilon.y,
        abs(x.z - y.z) < epsilon.z,
        abs(x.w - y.w) < epsilon.w);
}

template <typename valType>
inline detail::tvec2<bool> notEqualEpsilon
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y, 
	detail::tvec2<valType> const & epsilon
)
{
    return detail::tvec2<bool>(
        abs(x.x - y.x) >= epsilon.x,
        abs(x.y - y.y) >= epsilon.y);
}

template <typename valType>
inline detail::tvec3<bool> notEqualEpsilon
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y, 
	detail::tvec3<valType> const & epsilon
)
{
    return detail::tvec3<bool>(
        abs(x.x - y.x) >= epsilon.x,
        abs(x.y - y.y) >= epsilon.y,
        abs(x.z - y.z) >= epsilon.z);
}

template <typename valType>
inline detail::tvec4<bool> notEqualEpsilon
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y, 
	detail::tvec4<valType> const & epsilon
)
{
    return detail::tvec4<bool>(
        abs(x.x - y.x) >= epsilon.x,
        abs(x.y - y.y) >= epsilon.y,
        abs(x.z - y.z) >= epsilon.z,
        abs(x.w - y.w) >= epsilon.w);
}

}//namespace epsilon
}//namespace gtx
}//namespace glm
