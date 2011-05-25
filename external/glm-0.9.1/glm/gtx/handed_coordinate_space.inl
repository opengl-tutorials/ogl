///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/handed_coordinate_space.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace handed_coordinate_space
{
    template <typename T> 
    inline bool rightHanded(
		detail::tvec3<T> const & tangent, 
		detail::tvec3<T> const & binormal,
		detail::tvec3<T> const & normal)
    {
        return dot(cross(normal, tangent), binormal) > T(0);
    }

    template <typename T> 
    inline bool leftHanded(
		detail::tvec3<T> const & tangent, 
		detail::tvec3<T> const & binormal, 
		detail::tvec3<T> const & normal)
    {
        return dot(cross(normal, tangent), binormal) < T(0);
    }

}//namespace handed_coordinate_space
}//namespace gtx
}//namespace glm
