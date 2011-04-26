///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2008-07-24
// Licence : This source is under MIT License
// File    : glm/gtx/norm.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace norm
{
	template <typename T>
    inline T length2(
		const T x)
    {
        return x * x;
    }

    template <typename T>
    inline T length2(
		const detail::tvec2<T>& x)
    {
        return dot(x, x);
    }

    template <typename T>
    inline T length2(
		const detail::tvec3<T>& x)
    {
        return dot(x, x);
    }

    template <typename T>
    inline T length2(
		const detail::tvec4<T>& x)
    {
        return dot(x, x);
    }

    template <typename T> 
    inline T length2(
		const detail::tquat<T>& q)
    {
        return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    }

    template <typename T> 
	T distance2(
		const T p0, 
		const T p1)
	{
		return length2(p1 - p0);
	}

    template <typename T> 
	T distance2(
		const detail::tvec2<T>& p0, 
		const detail::tvec2<T>& p1)
	{
		return length2(p1 - p0);
	}

    template <typename T> 
	T distance2(
		const detail::tvec3<T>& p0, 
		const detail::tvec3<T>& p1)
	{
		return length2(p1 - p0);
	}

    template <typename T>
	T distance2(
		const detail::tvec4<T>& p0, 
		const detail::tvec4<T>& p1)
	{
		return length2(p1 - p0);
	}

    template <typename T> 
    inline T l1Norm(
		const detail::tvec3<T>& a, 
		const detail::tvec3<T>& b)
    {
        return abs(b.x - a.x) + abs(b.y - a.y) + abs(b.z - a.z);
    }

    template <typename T> 
    inline T l1Norm(
		const detail::tvec3<T>& v)
    {
        return abs(v.x) + abs(v.y) + abs(v.z);
    }

    template <typename T> 
    inline T l2Norm(
		const detail::tvec3<T>& a, 
		const detail::tvec3<T>& b)
    {
        return length(b - a);
    }

    template <typename T> 
    inline T l2Norm(
		const detail::tvec3<T>& v)
    {
        return length(v);
    }

	template <typename T> 
	inline T lxNorm(
		const detail::tvec3<T>& x, 
		const detail::tvec3<T>& y, 
		unsigned int Depth)
	{
		return pow(pow(y.x - x.x, T(Depth)) + pow(y.y - x.y, T(Depth)) + pow(y.z - x.z, T(Depth)), T(1) / T(Depth));
	}

	template <typename T> 
	inline T lxNorm(
		const detail::tvec3<T>& v, 
		unsigned int Depth)
	{
		return pow(pow(v.x, T(Depth)) + pow(v.y, T(Depth)) + pow(v.z, T(Depth)), T(1) / T(Depth));
	}

}//namespace norm
}//namespace gtx
}//namespace glm
