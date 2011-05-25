//////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
//////////////////////////////////////////////////////////////////////////////////
// Created : 2007-09-28
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/normalize_dot.inl
//////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace normalize_dot{

template <typename genType> 
inline genType normalizeDot
(
	genType const & x, 
	genType const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::inversesqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

template <typename valType> 
inline valType normalizeDot
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::inversesqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

template <typename valType> 
inline valType normalizeDot
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::inversesqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

template <typename valType> 
inline valType normalizeDot
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::inversesqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

template <typename genType> 
inline genType fastNormalizeDot
(
	genType const & x, 
	genType const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::gtx::fast_square_root::fastInverseSqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

template <typename valType> 
inline valType fastNormalizeDot
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::gtx::fast_square_root::fastInverseSqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

template <typename valType> 
inline valType fastNormalizeDot
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::gtx::fast_square_root::fastInverseSqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

template <typename valType> 
inline valType fastNormalizeDot
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y
)
{
	return 
		glm::dot(x, y) * 
		glm::gtx::fast_square_root::fastInverseSqrt(glm::dot(x, x) * 
		glm::dot(y, y));
}

}//namespace normalize_dot
}//namespace gtx
}//namespace glm
