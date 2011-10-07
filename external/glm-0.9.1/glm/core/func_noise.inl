///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-01
// Updated : 2008-09-23
// Licence : This source is under MIT License
// File    : glm/core/func_noise.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace core{
	namespace function{
	namespace noise{

	// noise1
	template <typename genType>
	inline genType noise1
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'noise1' only accept floating-point values");

		int iNbr = int(x + genType(3) / genType(2)) * 1103515245 + 12345;
		return genType(int(iNbr / genType(65536)) % 32768) / genType(32767);
	}

	template <typename T>
	inline typename detail::tvec2<T>::value_type noise1
	(
		detail::tvec2<T> const & x
	)
	{
		T tmp(0);
		for(typename detail::tvec2<T>::size_type i = 0; i < detail::tvec2<T>::value_size(); ++i)
			tmp += x[i];
		return noise1(tmp);
	}

	template <typename T>
	inline typename detail::tvec3<T>::value_type noise1
	(
		detail::tvec3<T> const & x
	)
	{
		T tmp(0);
		for(typename detail::tvec3<T>::size_type i = 0; i < detail::tvec3<T>::value_size(); ++i)
			tmp += x[i];
		return noise1(tmp);
	}

	template <typename T>
	inline typename detail::tvec4<T>::value_type noise1
	(
		detail::tvec4<T> const & x
	)
	{
		T tmp(0);
		for(typename detail::tvec4<T>::size_type i = 0; i < detail::tvec4<T>::value_size(); ++i)
			tmp += x[i];
		return noise1(tmp);
	}

	// noise2
	template <typename genType>
	inline detail::tvec2<genType> noise2
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'noise2' only accept floating-point values");

		genType f1 = x * genType(1103515245) + genType(12345);
		genType f2 = f1 * genType(1103515245) + genType(12345);
		return detail::tvec2<genType>(
			noise1(f1),
			noise1(f2));
	}

	template <typename T>
	inline detail::tvec2<T> noise2
	(
		detail::tvec2<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise2' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec2<T>::size_type i = 0; i < detail::tvec2<T>::value_size(); ++i)
			f0 += x[i];
		
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		return detail::tvec2<T>(
			noise1(f1),
			noise1(f2));
	}

	template <typename T>
	inline detail::tvec2<T> noise2
	(
		detail::tvec3<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise2' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec3<T>::size_type i = 0; i < detail::tvec3<T>::value_size(); ++i)
			f0 += x[i];

		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		return detail::tvec2<T>(
			noise1(f1),
			noise1(f2));
	}

	template <typename T>
	inline detail::tvec2<T> noise2
	(
		detail::tvec4<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise2' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec4<T>::size_type i = 0; i < detail::tvec4<T>::value_size(); ++i)
			f0 += x[i];
		
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		return detail::tvec2<T>(
			noise1(f1),
			noise1(f2));
	}

	// noise3
	template <typename genType>
	inline detail::tvec3<genType> noise3
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'noise3' only accept floating-point values");

		genType f1 = x * genType(1103515245) + genType(12345);
		genType f2 = f1 * genType(1103515245) + genType(12345);
		genType f3 = f2 * genType(1103515245) + genType(12345);
		return detail::tvec3<genType>(
			noise1(f1),
			noise1(f2),
			noise1(f3));
	}

	template <typename T>
	inline detail::tvec3<T> noise3
	(
		detail::tvec2<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise3' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec2<T>::size_type i = 0; i < detail::tvec2<T>::value_size(); ++i)
			f0 += x[i];
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		T f3 = f2 * T(1103515245) + T(12345);
		return detail::tvec3<T>(
			noise1(f1),
			noise1(f2),
			noise1(f3));
	}

	template <typename T>
	inline detail::tvec3<T> noise3
	(
		detail::tvec3<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise3' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec3<T>::size_type i = 0; i < detail::tvec3<T>::value_size(); ++i)
			f0 += x[i];
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		T f3 = f2 * T(1103515245) + T(12345);
		return detail::tvec3<T>(
			noise1(f1),
			noise1(f2),
			noise1(f3));
	}

	template <typename T>
	inline detail::tvec3<T> noise3
	(
		detail::tvec4<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise3' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec4<T>::size_type i = 0; i < detail::tvec4<T>::value_size(); ++i)
			f0 += x[i];
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		T f3 = f2 * T(1103515245) + T(12345);
		return detail::tvec3<T>(
			noise1(f1),
			noise1(f2),
			noise1(f3));
	}

	// noise4
	template <typename genType>
	inline detail::tvec4<genType> noise4
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'noise4' only accept floating-point values");

		genType f1 = x * genType(1103515245) + genType(12345);
		genType f2 = f1 * genType(1103515245) + genType(12345);
		genType f3 = f2 * genType(1103515245) + genType(12345);
		genType f4 = f3 * genType(1103515245) + genType(12345);
		return detail::tvec4<genType>(
			noise1(f1),
			noise1(f2),
			noise1(f3),
			noise1(f4));
	}

	template <typename T>
	inline detail::tvec4<T> noise4
	(
		detail::tvec2<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise4' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec2<T>::size_type i = 0; i < detail::tvec2<T>::value_size(); ++i)
			f0 += x[i];
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		T f3 = f2 * T(1103515245) + T(12345);
		T f4 = f3 * T(1103515245) + T(12345);
		return detail::tvec4<T>(
			noise1(f1),
			noise1(f2),
			noise1(f3),
			noise1(f4));
	}

	template <typename T>
	inline detail::tvec4<T> noise4
	(
		detail::tvec3<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise4' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec3<T>::size_type i = 0; i < detail::tvec3<T>::value_size()(); ++i)
			f0 += x[i];
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		T f3 = f2 * T(1103515245) + T(12345);
		T f4 = f3 * T(1103515245) + T(12345);
		return detail::tvec4<T>(
			noise1(f1),
			noise1(f2),
			noise1(f3),
			noise1(f4));
	}

	template <typename T>
	inline detail::tvec4<T> noise4
	(
		detail::tvec4<T> const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'noise4' only accept floating-point values");

		T f0(0);
		for(typename detail::tvec4<T>::size_type i = 0; i < detail::tvec4<T>::value_size()(); ++i)
			f0 += x[i];
		T f1 = f0 * T(1103515245) + T(12345);
		T f2 = f1 * T(1103515245) + T(12345);
		T f3 = f2 * T(1103515245) + T(12345);
		T f4 = f3 * T(1103515245) + T(12345);
		return detail::tvec4<T>(
			noise1(f1),
			noise1(f2),
			noise1(f3),
			noise1(f4));
	}

	}//namespace noise
	}//namespace function
	}//namespace core
}//namespace glm
