///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-05
// Updated : 2007-03-05
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_query.inl
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace matrix_query
{
	template<typename T> 
	inline bool isNull(
		const detail::tmat2x2<T>& m, 
		const T epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < 2 ; ++i)
			result = isNull(m[i], epsilon);
		return result;
	}

	template<typename T> 
	inline bool isNull(
		const detail::tmat3x3<T>& m, 
		const T epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < 3 ; ++i)
			result = isNull(m[i], epsilon);
		return result;
	}

	template<typename T> 
	inline bool isNull(
		const detail::tmat4x4<T>& m, 
		const T epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < 4 ; ++i)
			result = isNull(m[i], epsilon);
		return result;
	}

	template<typename genType> 
	inline bool isIdentity(
		const genType& m, 
		const typename genType::value_type epsilon)
	{
		bool result = true;
		for(typename genType::value_type i = typename genType::value_type(0); result && i < genType::col_size(); ++i)
		{
			for(typename genType::value_type j = typename genType::value_type(0); result && j < i ; ++j)
				result = abs(m[i][j]) <= epsilon;
			if(result)
				result = abs(m[i][i] - typename genType::value_type(1)) <= epsilon;
			for(typename genType::value_type j = i + typename genType::value_type(1); result && j < genType::row_size(); ++j)
				result = abs(m[i][j]) <= epsilon;
		}
		return result;
	}

	template<typename T> 
	inline bool isNormalized(
		const detail::tmat2x2<T>& m, 
		const T epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < 2; ++i)
			result = isNormalized(m[i], epsilon);
		for(int i = 0; result && i < 2; ++i)
		{
			detail::tvec2<T> v;
			for(int j = 0; j < 2; ++j)
				v[j] = m[j][i];
			result = isNormalized(v, epsilon);
		}
		return result;
	}

	template<typename T> 
	inline bool isNormalized(
		const detail::tmat3x3<T>& m, 
		const T epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < 3; ++i)
			result = isNormalized(m[i], epsilon);
		for(int i = 0; result && i < 3; ++i)
		{
			detail::tvec3<T> v;
			for(int j = 0; j < 3; ++j)
				v[j] = m[j][i];
			result = isNormalized(v, epsilon);
		}
		return result;
	}

	template<typename T> 
	inline bool isNormalized(
		const detail::tmat4x4<T>& m, 
		const T epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < 4; ++i)
			result = isNormalized(m[i], epsilon);
		for(int i = 0; result && i < 4; ++i)
		{
			detail::tvec4<T> v;
			for(int j = 0; j < 4; ++j)
				v[j] = m[j][i];
			result = isNormalized(v, epsilon);
		}
		return result;
	}

	template<typename genType> 
	inline bool isOrthogonal(
		const genType& m, 
		const typename genType::value_type epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < genType::col_size() - 1; ++i)
		for(int j= i + 1; result && j < genType::col_size(); ++j)
			result = areOrthogonal(m[i], m[j], epsilon);

		if(result)
		{
			genType tmp = transpose(m);
			for(int i = 0; result && i < genType::col_size() - 1 ; ++i)
			for(int j = i + 1; result && j < genType::col_size(); ++j)
				result = areOrthogonal(tmp[i], tmp[j], epsilon);
		}
		return result;
	}

}//namespace matrix_query
}//namespace gtx
}//namespace glm
