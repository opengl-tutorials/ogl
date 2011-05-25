///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtx/transform.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace transform
{
    template <typename T> 
    inline detail::tmat4x4<T> translate(
		T x, T y, T z)
    {
		return gtc::matrix_transform::translate(
			detail::tmat4x4<T>(1.0f), 
			detail::tvec3<T>(x, y , z));
    }

    template <typename T> 
    inline detail::tmat4x4<T> translate(
		detail::tmat4x4<T> const & m, 
		T x, T y, T z)
    {
        return gtc::matrix_transform::translate(
			m, detail::tvec3<T>(x, y , z));
    }

    template <typename T> 
    inline detail::tmat4x4<T> translate(
		detail::tvec3<T> const & v)
    {
		return gtc::matrix_transform::translate(
			detail::tmat4x4<T>(1.0f), v);
    }

    template <typename T> 
    inline detail::tmat4x4<T> rotate(
		T angle, 
		T x, T y, T z)
    {
		return gtc::matrix_transform::rotate(
			detail::tmat4x4<T>(1), angle, detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    inline detail::tmat4x4<T> rotate(
		T angle, 
		detail::tvec3<T> const & v)
    {
		return gtc::matrix_transform::rotate(
			detail::tmat4x4<T>(1), angle, v);
    }

    template <typename T> 
    inline detail::tmat4x4<T> rotate(
		detail::tmat4x4<T> const & m, 
		T angle, 
		T x, T y, T z)
    {
		return gtc::matrix_transform::rotate(
			m, angle, detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    inline detail::tmat4x4<T> scale(T x, T y, T z)
    {
		return gtc::matrix_transform::scale(
			detail::tmat4x4<T>(1), detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    inline detail::tmat4x4<T> scale(
		detail::tmat4x4<T> const & m, 
		T x, T y, T z)
    {
        return gtc::matrix_transform::scale(
			m, detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    inline detail::tmat4x4<T> scale(
		detail::tvec3<T> const & v)
    {
        return gtc::matrix_transform::scale(
			detail::tmat4x4<T>(1.0f), v);
    }

}//namespace transform
}//namespace gtx
}//namespace glm
