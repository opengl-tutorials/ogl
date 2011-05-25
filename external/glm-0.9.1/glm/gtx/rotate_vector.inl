///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-11-02
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/rotate_vector.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace rotate_vector
{
	template <typename T>
	inline detail::tvec2<T> rotate(
		const detail::tvec2<T>& v, 
		T angle)
	{
		detail::tvec2<T> Result;
		const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
		Result.x = v.x * Cos - v.y * Sin;
		Result.y = v.x * Sin + v.y * Cos;
		return Result;
	}

	template <typename T> 
	inline detail::tvec3<T> rotate(
		const detail::tvec3<T>& v, T angle, 
		const detail::tvec3<T>& normal)
	{
		return detail::tmat3x3<T>(transform::rotate(angle, normal)) * v;
	}
/*
    template <typename T> 
    inline detail::tvec3<T> rotateGTX(const detail::tvec3<T>& x, T angle, const detail::tvec3<T>& normal)
    {
        const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
        return x * Cos + ((x * normal) * (T(1) - Cos)) * normal + cross(x, normal) * Sin;
    }
*/
	template <typename T> 
	inline detail::tvec4<T> rotate(
		const detail::tvec4<T>& v, 
		T angle, 
		const detail::tvec3<T>& normal)
	{
		return transform::rotate(angle, normal) * v;
	}

	template <typename T>
	inline detail::tvec3<T> rotateX(
		const detail::tvec3<T>& v, 
		T angle)
	{
		detail::tvec3<T> Result = v;
		const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
		Result.y = v.y * Cos - v.z * Sin;
		Result.z = v.y * Sin + v.z * Cos;
		return Result;
	}

	template <typename T>
	inline detail::tvec3<T> rotateY(
		const detail::tvec3<T>& v, 
		T angle)
	{
		detail::tvec3<T> Result = v;
		const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
		Result.x =  v.x * Cos + v.z * Sin;
		Result.z = -v.x * Sin + v.z * Cos;
		return Result;
	}

	template <typename T>
	inline detail::tvec3<T> rotateZ(
		const detail::tvec3<T>& v, 
		T angle)
	{
		detail::tvec3<T> Result = v;
		const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
		Result.x = v.x * Cos - v.y * Sin;
		Result.y = v.x * Sin + v.y * Cos;
		return Result;
	}

	template <typename T>
	inline detail::tvec4<T> rotateX(
		const detail::tvec4<T>& v, 
		T angle)
	{
		detail::tvec4<T> Result = v;
		const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
		Result.y = v.y * Cos - v.z * Sin;
		Result.z = v.y * Sin + v.z * Cos;
		return Result;
	}

	template <typename T>
	inline detail::tvec4<T> rotateY(
		const detail::tvec4<T>& v, 
		T angle)
	{
		detail::tvec4<T> Result = v;
		const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
		Result.x =  v.x * Cos + v.z * Sin;
		Result.z = -v.x * Sin + v.z * Cos;
		return Result;
	}

	template <typename T>
	inline detail::tvec4<T> rotateZ(
		const detail::tvec4<T>& v, 
		T angle)
	{
		detail::tvec4<T> Result = v;
		const T Cos = cos(radians(angle));
        const T Sin = sin(radians(angle));
		Result.x = v.x * Cos - v.y * Sin;
		Result.y = v.x * Sin + v.y * Cos;
		return Result;
	}

	template <typename T>
	inline detail::tmat4x4<T> orientation(
		const detail::tvec3<T>& Normal, 
		const detail::tvec3<T>& Up)
	{
		if(all(equal(Normal, Up)))
			return detail::tmat4x4<T>(T(1));

		detail::tvec3<T> RotationAxis = cross(Up, Normal);
		T Angle = degrees(acos(dot(Normal, Up)));
		return rotate(Angle, RotationAxis);
	}

}//namespace rotate_vector
}//namespace gtx
}//namespace glm
