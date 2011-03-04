///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-04
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/fast_square_root.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace fast_square_root{

// fastSqrt
template <typename genType>
inline genType fastSqrt
(
	genType const & x
)
{
    return genType(1) / fastInverseSqrt(x);
}

template <typename valType>
inline detail::tvec2<valType> fastSqrt
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        fastSqrt(x.x), 
        fastSqrt(x.y));
}

template <typename valType>
inline detail::tvec3<valType> fastSqrt
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        fastSqrt(x.x), 
        fastSqrt(x.y), 
        fastSqrt(x.z));
}

template <typename valType>
inline detail::tvec4<valType> fastSqrt
(
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        fastSqrt(x.x), 
        fastSqrt(x.y), 
        fastSqrt(x.z), 
        fastSqrt(x.w));
}

// fastInversesqrt
template <typename genType>
inline genType fastInverseSqrt
(
	genType const & x
)
{
	genType tmp = x;
    float xhalf = 0.5f * float(tmp);
    uint i = *(uint*)&x;
    i = 0x5f375a86 - (i >> 1);
    //x = *(float*)&i;
	//x = *((float*)(char*)&i);
	tmp = detail::uif(i).f;
	tmp = tmp * (1.5f - xhalf * tmp * tmp);
    return genType(tmp);
}

template <typename valType>
inline detail::tvec2<valType> fastInverseSqrt
(
	detail::tvec2<valType> const & x
)
{
    return detail::tvec2<valType>(
        fastInverseSqrt(x.x), 
        fastInverseSqrt(x.y));
}

template <typename valType>
inline detail::tvec3<valType> fastInverseSqrt
(
	detail::tvec3<valType> const & x
)
{
    return detail::tvec3<valType>(
        fastInverseSqrt(x.x), 
        fastInverseSqrt(x.y), 
        fastInverseSqrt(x.z));
}

template <typename valType>
inline detail::tvec4<valType> fastInverseSqrt
(
	detail::tvec4<valType> const & x
)
{
    return detail::tvec4<valType>(
        fastInverseSqrt(x.x), 
        fastInverseSqrt(x.y), 
        fastInverseSqrt(x.z), 
        fastInverseSqrt(x.w));
}

// fastLength
template <typename genType>
inline genType fastLength
(
	genType const & x
)
{
    return abs(x);
}

template <typename valType>
inline valType fastLength
(
	detail::tvec2<valType> const & x
)
{
    valType sqr = x.x * x.x + x.y * x.y;
    return fastSqrt(sqr);
}

template <typename valType>
inline valType fastLength
(
	detail::tvec3<valType> const & x
)
{
    valType sqr = x.x * x.x + x.y * x.y + x.z * x.z;
    return fastSqrt(sqr);
}

template <typename valType>
inline valType fastLength
(
	detail::tvec4<valType> const & x
)
{
    valType sqr = x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w;
    return fastSqrt(sqr);
}

// fastDistance
template <typename genType>
inline genType fastDistance
(
	genType const & x, 
	genType const & y
)
{
    return fastLength(y - x);
}

template <typename valType>
inline valType fastDistance
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y
)
{
    return fastLength(y - x);
}

template <typename valType>
inline valType fastDistance
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y
)
{
    return fastLength(y - x);
}

template <typename valType>
inline valType fastDistance
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y
)
{
    return fastLength(y - x);
}

// fastNormalize
template <typename genType>
inline genType fastNormalize
(
	genType const & x
)
{
    return x > genType(0) ? genType(1) : -genType(1);
}

template <typename valType>
inline detail::tvec2<valType> fastNormalize
(
	detail::tvec2<valType> const & x
)
{
    valType sqr = x.x * x.x + x.y * x.y;
    return x * fastInverseSqrt(sqr);
}

template <typename valType>
inline detail::tvec3<valType> fastNormalize
(
	detail::tvec3<valType> const & x
)
{
    valType sqr = x.x * x.x + x.y * x.y + x.z * x.z;
    return x * fastInverseSqrt(sqr);
}

template <typename valType>
inline detail::tvec4<valType> fastNormalize
(
	detail::tvec4<valType> const & x
)
{
    valType sqr = x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w;
    return x * fastInverseSqrt(sqr);
}

}//namespace fast_square_root
}//namespace gtx
}//namespace glm
