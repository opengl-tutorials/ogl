///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2005-12-27
// Licence : This source is under MIT License
// File    : glm/gtx/optimum_pow.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace optimum_pow{

    template <typename genType> 
    inline genType pow2(const genType& x)
    {
        return x * x;
    }

    template <typename genType> 
    inline genType pow3(const genType& x)
    {
        return x * x * x;
    }

    template <typename genType> 
    inline genType pow4(const genType& x)
    {
        return x * x * x * x;
    }

    inline bool powOfTwo(int x)
    {
        return !(x & (x - 1));
    }

    inline detail::tvec2<bool> powOfTwo(const detail::tvec2<int>& x)
    {
        return detail::tvec2<bool>(
            powOfTwo(x.x),
            powOfTwo(x.y));
    }

    inline detail::tvec3<bool> powOfTwo(const detail::tvec3<int>& x)
    {
        return detail::tvec3<bool>(
            powOfTwo(x.x),
            powOfTwo(x.y),
            powOfTwo(x.z));
    }

    inline detail::tvec4<bool> powOfTwo(const detail::tvec4<int>& x)
    {
        return detail::tvec4<bool>(
            powOfTwo(x.x),
            powOfTwo(x.y),
            powOfTwo(x.z),
            powOfTwo(x.w));
    }

}//namespace optimum_pow
}//namespace gtx
}//namespace glm
