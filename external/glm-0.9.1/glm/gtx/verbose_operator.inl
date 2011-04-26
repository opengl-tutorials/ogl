///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-04-20
// Updated : 2008-09-29
// Licence : This source is under MIT License
// File    : glm/gtx/verbose_operator.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace verbose_operator{

template <typename genType>
inline genType add(genType const & a, genType const & b)
{
    return a + b;
}

template <typename genType>
inline genType sub(genType const & a, genType const & b)
{
    return a - b;
}

template <typename T>
inline detail::tmat2x2<T> mul
(
	detail::tmat2x2<T> const & a, 
	detail::tmat2x2<T> const & b
)
{
    return a * b;
}

template <typename T>
inline detail::tmat3x3<T> mul
(
	detail::tmat3x3<T> const & a, 
	detail::tmat3x3<T> const & b
)
{
    return a * b;
}

template <typename T>
inline detail::tmat4x4<T> mul
(
	detail::tmat4x4<T> const & a, 
	detail::tmat4x4<T> const & b
)
{
    return a * b;
}

template <typename T>
inline detail::tvec2<T> mul
(
	detail::tmat2x2<T> const & m, 
	detail::tvec2<T> const & v
)
{
    return m * v;
}

template <typename T>
inline detail::tvec3<T> mul
(
	detail::tmat3x3<T> const & m, 
	detail::tvec3<T> const & v)
{
    return m * v;
}

template <typename T>
inline detail::tvec4<T> mul
(
	detail::tmat4x4<T> const & m, 
	detail::tvec4<T> const & v
)
{
    return m * v;
}

template <typename T>
inline detail::tvec2<T> mul
(
	detail::tvec2<T> const & v, 
	detail::tmat2x2<T> const & m
)
{
    return v * m;
}

template <typename T>
inline detail::tvec3<T> mul
(
	detail::tvec3<T> const & v, 
	detail::tmat3x3<T> const & m
)
{
    return v * m;
}

template <typename T>
inline detail::tvec4<T> mul
(
	detail::tvec4<T> const & v, 
	detail::tmat4x4<T> const & m
)
{
    return v * m;
}

template <typename genType>
inline genType div(genType const & a, genType const & b)
{
    return a / b;
}

template <typename genTypeT, typename genTypeU, typename genTypeV> 
inline genTypeT mad(genTypeT const & a, genTypeU const & b, genTypeV const & c)
{
	return a * b + c;
}

}//namespace verbose_operator
}//namespace gtx
}//namespace glm
