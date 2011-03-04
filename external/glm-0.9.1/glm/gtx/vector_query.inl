///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-05
// Updated : 2010-02-16
// Licence : This source is under MIT License
// File    : glm/gtx/vector_query.inl
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>

namespace glm{
namespace gtx{
namespace vector_query
{
	template <typename T>
	inline bool areCollinear(
		const detail::tvec2<T>& v0, 
		const detail::tvec2<T>& v1, 
		const T epsilon)
	{
		return length(cross(detail::tvec3<T>(v0, T(0)), detail::tvec3<T>(v1, T(0)))) < epsilon;
	}

	template <typename T>
	inline bool areCollinear(
		const detail::tvec3<T>& v0, 
		const detail::tvec3<T>& v1, 
		const T epsilon)
	{
		return length(cross(v0, v1)) < epsilon;
	}

	template <typename T>
	inline bool areCollinear(
		const detail::tvec4<T>& v0, 
		const detail::tvec4<T>& v1, 
		const T epsilon)
	{
		return length(cross(detail::tvec3<T>(v0), detail::tvec3<T>(v1))) < epsilon;
	}

	template <typename genType>
	inline bool areOpposite(
		const genType& v0, 
		const genType& v1, 
		const GLMvalType epsilon)
	{
		assert(isNormalized(v0) && isNormalized(v1));
        return((genType::value_type(1) + dot(v0, v1)) <= epsilon);
	}

	template <typename genType>
	inline bool areOrthogonal(
		const genType& v0, 
		const genType& v1, 
		const GLMvalType epsilon)
	{
		return abs(dot(v0, v1)) <= max(GLMvalType(1), length(v0)) * max(GLMvalType(1), length(v1)) * epsilon;
	}

	template <typename genType> 
	inline bool isNormalized(
		const genType& v, 
		const GLMvalType epsilon)
	{
		return abs(length(v) - GLMvalType(1)) <= GLMvalType(2) * epsilon;
	}

	template <typename genType> 
	inline bool isNull(const genType& v, const GLMvalType epsilon)
	{
		return length(v) <= epsilon;
	}

    template <typename T> 
    inline bool isCompNull(
		const T s, 
		const T epsilon)
    {
        return abs(s) < epsilon;
    }

    template <typename T> 
    inline detail::tvec2<bool> isCompNull(
		const detail::tvec2<T>& v, 
		const T epsilon)
    {
        return detail::tvec2<bool>(
            (abs(v.x) < epsilon),
            (abs(v.y) < epsilon));
    }

    template <typename T> 
    inline detail::tvec3<bool> isCompNull(
		const detail::tvec3<T>& v, 
		const T epsilon)
    {
        return detail::tvec3<bool>(
            abs(v.x) < epsilon,
            abs(v.y) < epsilon,
            abs(v.z) < epsilon);
    }

    template <typename T> 
    inline detail::tvec4<bool> isCompNull(
		const detail::tvec4<T>& v, 
		const T epsilon)
    {
        return detail::tvec4<bool>(
            abs(v.x) < epsilon,
            abs(v.y) < epsilon,
            abs(v.z) < epsilon,
            abs(v.w) < epsilon);
    }

	template <typename genType>
	inline bool areOrthonormal(
		const genType& v0, 
		const genType& v1, 
		const GLMvalType epsilon)
	{
		return isNormalized(v0, epsilon) && isNormalized(v1, epsilon) && (abs(dot(v0, v1)) <= epsilon);
	}

	template <typename genType>
	inline bool areSimilar(
		const genType& v0, 
		const genType& v1, 
		const GLMvalType epsilon)
	{
		bool similar = true;
        for(typename genType::size_type i = 0; similar && i < genType::value_size(); i++)
			similar = (abs(v0[i] - v1[i]) <= epsilon);
		return similar;
	}

}//namespace vector_query
}//namespace gtx
}//namespace glm
