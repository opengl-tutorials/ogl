///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-03-06
// Licence : This source is under MIT License
// File    : glm/gtx/perpendicular.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace perpendicular{

template <typename T> 
inline detail::tvec2<T> perp(
	detail::tvec2<T> const & x, 
	detail::tvec2<T> const & Normal)
{
    return x - projection::proj(x, Normal);
}

template <typename T> 
inline detail::tvec3<T> perp(
	detail::tvec3<T> const & x, 
	detail::tvec3<T> const & Normal)
{
    return x - projection::proj(x, Normal);
}

template <typename T> 
inline detail::tvec4<T> perp(
	detail::tvec4<T> const & x, 
	detail::tvec4<T> const & Normal)
{
    return x - projection::proj(x, Normal);
}

}//namespace perpendicular
}//namespace gtx
}//namespace glm
