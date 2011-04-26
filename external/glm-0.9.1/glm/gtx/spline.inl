///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-01-25
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/spline.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace spline
{
	template <typename genType>
	inline genType catmullRom(
		const genType& v1, 
		const genType& v2, 
		const genType& v3, 
		const genType& v4, 
		const GLMvalType& s)
	{
		GLMvalType s1 = s;
		GLMvalType s2 = optimum_pow::pow2(s);
		GLMvalType s3 = optimum_pow::pow3(s);

		GLMvalType f1 = -s3 + GLMvalType(2) * s2 - s;
		GLMvalType f2 = GLMvalType(3) * s3 - GLMvalType(5) * s2 + GLMvalType(2);
		GLMvalType f3 = GLMvalType(-3) * s3 + GLMvalType(4) * s2 + s;
		GLMvalType f4 = s3 - s2;

		return (f1 * v1 + f2 * v2 + f3 * v3 + f4 * v4) / GLMvalType(2);

	}

	template <typename genType>
	inline genType hermite(
		const genType& v1, 
		const genType& t1, 
		const genType& v2, 
		const genType& t2, 
		const GLMvalType& s)
	{
		GLMvalType s1 = s;
		GLMvalType s2 = optimum_pow::pow2(s);
		GLMvalType s3 = optimum_pow::pow3(s);

		GLMvalType f1 = GLMvalType(2) * s3 - GLMvalType(3) * s2 + GLMvalType(1);
		GLMvalType f2 = GLMvalType(-2) * s3 + GLMvalType(3) * s2;
		GLMvalType f3 = s3 - GLMvalType(2) * s2 + s;
		GLMvalType f4 = s3 - s2;

		return f1 * v1 + f2 * v2 + f3 * t1 + f4 * t2;
	}

	template <typename genType>
	inline genType cubic(
		const genType& v1, 
		const genType& v2, 
		const genType& v3, 
		const genType& v4, 
		const GLMvalType& s)
	{
		return ((v1 * s + v2) * s + v3) * s + v4;
	}

}//namespace spline
}//namespace gtx
}//namespace glm
