///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-01-26
// Updated : 2010-01-26
// Licence : This source is under MIT License
// File    : glm/core/type_mat.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat
#define glm_core_type_mat

#include "type_gentype.hpp"

namespace glm{
namespace detail
{
	//template 
	//<
	//	typename T, 
	//	template <typename> class C, 
	//	template <typename> class R
	//>
	//struct matType
	//{
	//	enum ctor{null};
	//	typedef T value_type;
	//	typedef std::size_t size_type;
	//	typedef C<T> col_type;
	//	typedef R<T> row_type;
	//	static size_type const col_size;
	//	static size_type const row_size;
	//};

	//template 
	//<
	//	typename T, 
	//	template <typename> class C, 
	//	template <typename> class R
	//>
	//typename matType<T, C, R>::size_type const 
	//matType<T, C, R>::col_size = matType<T, C, R>::col_type::value_size;

	//template 
	//<
	//	typename T, 
	//	template <typename> class C, 
	//	template <typename> class R
	//>
	//typename matType<T, C, R>::size_type const 
	//matType<T, C, R>::row_size = matType<T, C, R>::row_type::value_size;

}//namespace detail
}//namespace glm

#endif//glm_core_type_mat
