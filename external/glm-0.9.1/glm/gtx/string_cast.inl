///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2006 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-04-27
// Updated : 2008-05-24
// Licence : This source is under MIT License
// File    : glm/gtx/string_cast.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdarg>
#include <cstdio>

namespace glm{
namespace detail
{
	inline std::string format(const char* msg, ...)
	{
		const int STRING_BUFFER = 4096;
		char text[STRING_BUFFER];
		va_list list;

		if(msg == 0)
			return std::string();

		va_start(list, msg);
			vsprintf(text, msg, list);
		va_end(list);

		return std::string(text);
	}

	static const char* True = "true";
	static const char* False = "false";
}//namespace detail

namespace gtx{
namespace string_cast
{
	////////////////////////////////
	// Scalars

	inline std::string to_string(detail::thalf const & x)
	{
		return detail::format("half(%f)", float(x));
	}

	inline std::string to_string(float x)
	{
		return detail::format("float(%f)", x);
	}

	inline std::string to_string(double x)
	{
		return detail::format("double(%f)", x);
	}

	inline std::string to_string(int x)
	{
		return detail::format("int(%d)", x);
	}

	inline std::string to_string(unsigned int x)
	{
		return detail::format("uint(%d)", x);
	}

	////////////////////////////////
	// Bool vectors

	inline std::string to_string
	(
		detail::tvec2<bool> const & v
	)
	{
		return detail::format("bvec2(%s, %s)", 
			v.x ? detail::True : detail::False, 
			v.y ? detail::True : detail::False);
	}

	inline std::string to_string
	(
		detail::tvec3<bool> const & v
	)
	{
		return detail::format("bvec3(%s, %s, %s)", 
			v.x ? detail::True : detail::False, 
			v.y ? detail::True : detail::False, 
			v.z ? detail::True : detail::False);
	}

	inline std::string to_string
	(
		detail::tvec4<bool> const & v
	)
	{
		return detail::format("bvec4(%s, %s, %s, %s)", 
			v.x ? detail::True : detail::False, 
			v.y ? detail::True : detail::False, 
			v.z ? detail::True : detail::False, 
			v.w ? detail::True : detail::False);
	}

	////////////////////////////////
	// Half vectors

	template <>
	inline std::string to_string
	(
		detail::tvec2<detail::thalf> const & v
	)
	{
		return detail::format("hvec2(%f, %f)", float(v.x), float(v.y));
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec3<detail::thalf> const & v
	)
	{
		return detail::format("hvec3(%f, %f, %f)", float(v.x), float(v.y), float(v.z));
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec4<detail::thalf> const & v
	)
	{
		return detail::format("hvec4(%f, %f, %f, %f)", float(v.x), float(v.y), float(v.z), float(v.w));
	}

	////////////////////////////////
	// Float vectors

	template <>
	inline std::string to_string
	(
		detail::tvec2<float> const & v
	)
	{
		return detail::format("fvec2(%f, %f)", v.x, v.y);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec3<float> const & v
	)
	{
		return detail::format("fvec3(%f, %f, %f)", v.x, v.y, v.z);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec4<float> const & v
	)
	{
		return detail::format("fvec4(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
	}

	////////////////////////////////
	// Double vectors

	template <>
	inline std::string to_string
	(
		detail::tvec2<double> const & v
	)
	{
		return detail::format("dvec2(%f, %f)", v.x, v.y);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec3<double> const & v
	)
	{
		return detail::format("dvec3(%f, %f, %f)", v.x, v.y, v.z);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec4<double> const & v
	)
	{
		return detail::format("dvec4(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
	}

	////////////////////////////////
	// Int vectors

	template <>
	inline std::string to_string
	(
		detail::tvec2<int> const & v
	)
	{
		return detail::format("ivec2(%d, %d)", v.x, v.y);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec3<int> const & v
	)
	{
		return detail::format("ivec3(%d, %d, %d)", v.x, v.y, v.z);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec4<int> const & v
	)
	{
		return detail::format("ivec4(%d, %d, %d, %d)", v.x, v.y, v.z, v.w);
	}

	////////////////////////////////
	// Unsigned int vectors

	template <>
	inline std::string to_string
	(
		detail::tvec2<unsigned int> const & v
	)
	{
		return detail::format("uvec2(%d, %d)", v.x, v.y);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec3<unsigned int> const & v
	)
	{
		return detail::format("uvec3(%d, %d, %d)", v.x, v.y, v.z);
	}

	template <> 
	inline std::string to_string
	(
		detail::tvec4<unsigned int> const & v
	)
	{
		return detail::format("uvec4(%d, %d, %d, %d)", v.x, v.y, v.z, v.w);
	}

	////////////////////////////////
	// Half matrices

	template <> 
	inline std::string to_string
	(
		detail::tmat2x2<detail::thalf> const & m
	)
	{
		detail::tmat2x2<float> x(m);
		return detail::format("hmat2x2((%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat2x3<detail::thalf> const & m
	)
	{
		detail::tmat2x3<float> x(m);
		return detail::format("hmat2x3((%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], 
			x[1][0], x[1][1], x[1][2]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat2x4<detail::thalf> const & m
	)
	{
		detail::tmat2x4<float> x(m);
		return detail::format("hmat2x4((%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3], 
			x[1][0], x[1][1], x[1][2], x[1][3]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x2<detail::thalf> const & m
	)
	{
		detail::tmat3x2<float> x(m);
		return detail::format("hmat3x2((%f, %f), (%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1], 
			x[2][0], x[2][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x3<detail::thalf> const & m
	)
	{
		detail::tmat3x3<float> x(m);
		return detail::format("hmat3x3((%f, %f, %f), (%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], 
			x[1][0], x[1][1], x[1][2],
			x[2][0], x[2][1], x[2][2]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x4<detail::thalf> const & m
	)
	{
		detail::tmat3x4<float> x(m);
		return detail::format("hmat3x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3], 
			x[1][0], x[1][1], x[1][2], x[1][3], 
			x[2][0], x[2][1], x[2][2], x[2][3]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat4x2<detail::thalf> const & m
	)
	{
		detail::tmat4x2<float> x(m);
		return detail::format("hmat4x2((%f, %f), (%f, %f), (%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1], 
			x[2][0], x[2][1], 
			x[3][0], x[3][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat4x3<detail::thalf> const & m
	)
	{
		detail::tmat4x3<float> x(m);
		return detail::format("hmat4x3((%f, %f, %f), (%f, %f, %f), (%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2],
			x[1][0], x[1][1], x[1][2], 
			x[2][0], x[2][1], x[2][2],
			x[3][0], x[3][1], x[3][2]);
	}

	template <>
	inline std::string to_string
	(
		detail::tmat4x4<detail::thalf> const & m
	)
	{
		detail::tmat4x4<float> x(m);
		return detail::format("hmat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3],
			x[1][0], x[1][1], x[1][2], x[1][3],
			x[2][0], x[2][1], x[2][2], x[2][3],
			x[3][0], x[3][1], x[3][2], x[3][3]);
	}

	////////////////////////////////
	// Float matrices

	template <> 
	inline std::string to_string
	(
		detail::tmat2x2<float> const & x
	)
	{
		return detail::format("mat2x2((%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat2x3<float> const & x
	)
	{
		return detail::format("mat2x3((%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], 
			x[1][0], x[1][1], x[1][2]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat2x4<float> const & x
	)
	{
		return detail::format("mat2x4((%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3], 
			x[1][0], x[1][1], x[1][2], x[1][3]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x2<float> const & x
	)
	{
		return detail::format("mat3x2((%f, %f), (%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1], 
			x[2][0], x[2][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x3<float> const & x
	)
	{
		return detail::format("mat3x3((%f, %f, %f), (%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], 
			x[1][0], x[1][1], x[1][2],
			x[2][0], x[2][1], x[2][2]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x4<float> const & x
	)
	{
		return detail::format("mat3x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3], 
			x[1][0], x[1][1], x[1][2], x[1][3], 
			x[2][0], x[2][1], x[2][2], x[2][3]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat4x2<float> const & x
	)
	{
		return detail::format("mat4x2((%f, %f), (%f, %f), (%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1], 
			x[2][0], x[2][1], 
			x[3][0], x[3][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat4x3<float> const & x
	)
	{
		return detail::format("mat4x3((%f, %f, %f), (%f, %f, %f), (%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2],
			x[1][0], x[1][1], x[1][2], 
			x[2][0], x[2][1], x[2][2],
			x[3][0], x[3][1], x[3][2]);
	}

	template <>
	inline std::string to_string
	(
		detail::tmat4x4<float> const & x
	)
	{
		return detail::format("mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3],
			x[1][0], x[1][1], x[1][2], x[1][3],
			x[2][0], x[2][1], x[2][2], x[2][3],
			x[3][0], x[3][1], x[3][2], x[3][3]);
	}

	////////////////////////////////
	// Double matrices

	template <> 
	inline std::string to_string
	(
		detail::tmat2x2<double> const & x
	)
	{
		return detail::format("dmat2x2((%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat2x3<double> const & x
	)
	{
		return detail::format("dmat2x3((%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], 
			x[1][0], x[1][1], x[1][2]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat2x4<double> const & x
	)
	{
		return detail::format("dmat2x4((%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3], 
			x[1][0], x[1][1], x[1][2], x[1][3]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x2<double> const & x
	)
	{
		return detail::format("dmat3x2((%f, %f), (%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1],
			x[2][0], x[2][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x3<double> const & x
	)
	{
		return detail::format("dmat3x3((%f, %f, %f), (%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], 
			x[1][0], x[1][1], x[1][2],
			x[2][0], x[2][1], x[2][2]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat3x4<double> const & x
	)
	{
		return detail::format("dmat3x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3], 
			x[1][0], x[1][1], x[1][2], x[1][3],
			x[2][0], x[2][1], x[2][2], x[2][3]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat4x2<double> const & x
	)
	{
		return detail::format("dmat4x2((%f, %f), (%f, %f), (%f, %f), (%f, %f))", 
			x[0][0], x[0][1], 
			x[1][0], x[1][1], 
			x[2][0], x[2][1], 
			x[3][0], x[3][1]);
	}

	template <> 
	inline std::string to_string
	(
		detail::tmat4x3<double> const & x
	)
	{
		return detail::format("dmat4x3((%f, %f, %f), (%f, %f, %f), (%f, %f, %f), (%f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], 
			x[1][0], x[1][1], x[1][2], 
			x[2][0], x[2][1], x[2][2], 
			x[3][0], x[3][1], x[3][2]);
	}

	template <>
	inline std::string to_string
	(
		detail::tmat4x4<double> const & x
	)
	{
		return detail::format("dmat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", 
			x[0][0], x[0][1], x[0][2], x[0][3],
			x[1][0], x[1][1], x[1][2], x[1][3],
			x[2][0], x[2][1], x[2][2], x[2][3],
			x[3][0], x[3][1], x[3][2], x[3][3]);
	}

	}//namespace string_cast
	}//namespace gtx
}//namespace glm
