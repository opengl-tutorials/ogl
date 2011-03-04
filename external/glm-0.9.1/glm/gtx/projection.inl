///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-03-06
// Licence : This source is under MIT License
// File    : glm/gtx/projection.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace projection{

template <typename T> 
inline detail::tvec2<T> proj(
	detail::tvec2<T> const & x, 
	detail::tvec2<T> const & Normal)
{
	return glm::dot(x, Normal) / glm::dot(Normal, Normal) * Normal;
}

template <typename T> 
inline detail::tvec3<T> proj(
	detail::tvec3<T> const & x, 
	detail::tvec3<T> const & Normal)
{
	return dot(x, Normal) / glm::dot(Normal, Normal) * Normal;
}

template <typename T> 
inline detail::tvec4<T> proj(
	detail::tvec4<T> const & x, 
	detail::tvec4<T> const & Normal)
{
	return glm::dot(x, Normal) / glm::dot(Normal, Normal) * Normal;
}

}//namespace projection
}//namespace gtx
}//namespace glm
