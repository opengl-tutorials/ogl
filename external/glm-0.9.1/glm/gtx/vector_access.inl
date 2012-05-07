///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-16
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/vector_access.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace vector_access{

template <typename valType> 
inline void set
(
	detail::tvec2<valType>& v, 
	valType const & x, 
	valType const & y
)
{
    v.x = x;
    v.y = y;
}

template <typename valType> 
inline void set
(
	detail::tvec3<valType>& v, 
	valType const & x, 
	valType const & y, 
	valType const & z
)
{
    v.x = x;
    v.y = y;
    v.z = z;
}

template <typename valType>
inline void set
(
	detail::tvec4<valType>& v, 
	valType const & x, 
	valType const & y, 
	valType const & z, 
	valType const & w
)
{
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
}

}//namespace vector_access
}//namespace gtx
}//namespace glm
