///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-27
// Updated : 2010-11-12
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_access.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtc{
namespace matrix_access
{
    template <typename genType>
    inline genType row(
		genType const & m, 
		int index, 
		typename genType::row_type const & x)
    {
        genType Result = m;
        for(typename genType::size_type i = 0; i < genType::row_size(); ++i)
			Result[i][index] = x[i];
        return Result;
    }

    template <typename genType>
    inline typename genType::row_type row(
		genType const & m, 
		int index)
    {
		typename genType::row_type Result;
		for(typename genType::size_type i = 0; i < genType::row_size(); ++i)
			Result[i] = m[i][index];
		return Result;
    }

    template <typename genType>
    inline genType column(
		genType const & m, 
		int index, 
		typename genType::col_type const & x)
    {
        genType Result = m;
        Result[index] = x;
        return Result;
    }

    template <typename genType>
    inline typename genType::col_type column(
		genType const & m, 
		int index)
    {
        return m[index];
    }

}//namespace matrix_access
}//namespace gtc
}//namespace glm

