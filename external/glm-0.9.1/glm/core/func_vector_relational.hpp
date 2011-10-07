///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-03
// Updated : 2008-09-09
// Licence : This source is under MIT License
// File    : glm/core/func_vector_relational.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_vector_relational
#define glm_core_func_vector_relational

#include "_detail.hpp"

namespace glm
{
	namespace test{
		void main_core_func_vector_relational();
	}//namespace test

	namespace core{
	namespace function{
	//! Define vector relational functions from Section 8.3 of GLSL 1.30.8 specification. 
	//! Included in glm namespace.
	namespace vector_relational
	{
		/// \addtogroup core_funcs
		///@{

		//! Returns the component-wise comparison result of x < y.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <typename T, template <typename> class vecType> 
		inline typename vecType<T>::bool_type lessThan
		(
			vecType<T> const & x, 
			vecType<T> const & y
		)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
				"Invalid template instantiation of 'lessThan', GLM vector types required");
			GLM_STATIC_ASSERT(detail::is_bool<T>::_NO,
				"Invalid template instantiation of 'lessThan', GLM vector types required floating-point or integer value types vectors");

			typename vecType<bool>::bool_type Result(vecType<bool>::null);
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result[i] = x[i] < y[i];

			return Result;
		}

		//! Returns the component-wise comparison of result x <= y.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <typename T, template <typename> class vecType> 
		inline typename vecType<T>::bool_type lessThanEqual
		(
			vecType<T> const & x, 
			vecType<T> const & y
		)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
				"Invalid template instantiation of 'lessThanEqual', GLM vector types required");
			GLM_STATIC_ASSERT(detail::is_bool<T>::_NO, 
				"Invalid template instantiation of 'lessThanEqual', GLM vector types required floating-point or integer value types vectors");

			typename vecType<bool>::bool_type Result(vecType<bool>::null);
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result[i] = x[i] <= y[i];
			return Result;
		}

		//! Returns the component-wise comparison of result x > y.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <typename T, template <typename> class vecType> 
		inline typename vecType<T>::bool_type greaterThan
		(
			vecType<T> const & x, 
			vecType<T> const & y
		)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
				"Invalid template instantiation of 'greaterThan', GLM vector types required");
			GLM_STATIC_ASSERT(detail::is_bool<T>::_NO, 
				"Invalid template instantiation of 'greaterThan', GLM vector types required floating-point or integer value types vectors");

			typename vecType<bool>::bool_type Result(vecType<bool>::null);
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result[i] = x[i] > y[i];
			return Result;
		}

		//! Returns the component-wise comparison of result x >= y.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <typename T, template <typename> class vecType> 
		inline typename vecType<T>::bool_type greaterThanEqual
		(
			vecType<T> const & x, 
			vecType<T> const & y
		)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
				"Invalid template instantiation of 'greaterThanEqual', GLM vector types required");
			GLM_STATIC_ASSERT(detail::is_bool<T>::_NO, 
				"Invalid template instantiation of 'greaterThanEqual', GLM vector types required floating-point or integer value types vectors");

			typename vecType<bool>::bool_type Result(vecType<bool>::null);
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result[i] = x[i] >= y[i];
			return Result;
		}

		//! Returns the component-wise comparison of result x == y.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <typename T, template <typename> class vecType> 
		inline typename vecType<T>::bool_type equal
		(
			vecType<T> const & x, 
			vecType<T> const & y
		)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
				"Invalid template instantiation of 'equal', GLM vector types required");

			typename vecType<bool>::bool_type Result(vecType<bool>::null);
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result[i] = x[i] == y[i];
			return Result;
		}

		//! Returns the component-wise comparison of result x != y.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <typename T, template <typename> class vecType> 
		inline typename vecType<T>::bool_type notEqual
		(
			vecType<T> const & x, 
			vecType<T> const & y
		)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
				"Invalid template instantiation of 'notEqual', GLM vector types required");

			typename vecType<bool>::bool_type Result(vecType<bool>::null);
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result[i] = x[i] != y[i];
			return Result;
		}

		//! Returns true if any component of x is true.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <template <typename> class vecType> 
		inline bool any(vecType<bool> const & v)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<bool> >::_YES, 
				"Invalid template instantiation of 'any', GLM boolean vector types required");

			bool Result = false;
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result = Result || v[i];
			return Result;
		}

		//! Returns true if all components of x are true.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <template <typename> class vecType> 
		inline bool all(vecType<bool> const & v)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<bool> >::_YES, 
				"Invalid template instantiation of 'all', GLM boolean vector types required");

			bool Result = true;
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result = Result && v[i];
			return Result;
		}

		//! Returns the component-wise logical complement of x.
		//! (From GLSL 1.30.08 specification, section 8.6)
		template <template <typename> class vecType> 
		inline vecType<bool> not_(vecType<bool> const & v)
		{
			GLM_STATIC_ASSERT(detail::is_vector<vecType<bool> >::_YES, 
				"Invalid template instantiation of 'not_', GLM vector types required");

			typename vecType<bool>::bool_type Result(vecType<bool>::null);
			for(typename vecType<bool>::size_type i = 0; i < vecType<bool>::value_size(); ++i)
				Result[i] = !v[i];
			return Result;
		}

		///@}

	}//namespace vector_relational
	}//namespace function
	}//namespace core

	using namespace core::function::vector_relational;
}//namespace glm

#include "func_vector_relational.inl"

#endif//glm_core_func_vector_relational
