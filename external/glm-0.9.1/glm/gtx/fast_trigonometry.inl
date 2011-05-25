///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-08
// Updated : 2006-01-08
// Licence : This source is under MIT License
// File    : glm/gtx/fast_trigonometry.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace fast_trigonometry
{
    // sin
    template <typename T> 
    inline T fastSin(const T x)
    {
        return x - ((x * x * x) / T(6)) + ((x * x * x * x * x) / T(120)) - ((x * x * x * x * x * x * x) / T(5040));
    }

    template <typename T> 
    inline detail::tvec2<T> fastSin(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastSin(x.x),
            fastSin(x.y));
    }

    template <typename T> 
    inline detail::tvec3<T> fastSin(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastSin(x.x),
            fastSin(x.y),
            fastSin(x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> fastSin(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastSin(x.x),
            fastSin(x.y),
            fastSin(x.z),
            fastSin(x.w));
    }

    // cos
    template <typename T> 
    inline T fastCos(const T x)
    {
        return T(1) - (x * x * T(0.5)) + (x * x * x * x * T(0.041666666666)) - (x * x * x * x * x * x * T(0.00138888888888));
    }

    template <typename T> 
    inline detail::tvec2<T> fastCos(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastCos(x.x),
            fastCos(x.y));
    }

    template <typename T> 
    inline detail::tvec3<T> fastCos(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastCos(x.x),
            fastCos(x.y),
            fastCos(x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> fastCos(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastCos(x.x),
            fastCos(x.y),
            fastCos(x.z),
            fastCos(x.w));
    }

    // tan
    template <typename T> 
    inline T fastTan(const T x)
    {
        return x + (x * x * x * T(0.3333333333)) + (x * x * x * x * x * T(0.1333333333333)) + (x * x * x * x * x * x * x * T(0.0539682539));
    }

    template <typename T> 
    inline detail::tvec2<T> fastTan(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastTan(x.x),
            fastTan(x.y));
    }

    template <typename T> 
    inline detail::tvec3<T> fastTan(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastTan(x.x),
            fastTan(x.y),
            fastTan(x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> fastTan(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastTan(x.x),
            fastTan(x.y),
            fastTan(x.z),
            fastTan(x.w));
    }

    // asin
    template <typename T> 
    inline T fastAsin(const T x)
    {
        return x + (x * x * x * T(0.166666667)) + (x * x * x * x * x * T(0.075)) + (x * x * x * x * x * x * x * T(0.0446428571)) + (x * x * x * x * x * x * x * x * x * T(0.0303819444));// + (x * x * x * x * x * x * x * x * x * x * x * T(0.022372159));
    }

    template <typename T> detail::tvec2<T> fastAsin(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastAsin(x.x),
            fastAsin(x.y));
    }

    template <typename T> detail::tvec3<T> fastAsin(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastAsin(x.x),
            fastAsin(x.y),
            fastAsin(x.z));
    }

    template <typename T> detail::tvec4<T> fastAsin(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastAsin(x.x),
            fastAsin(x.y),
            fastAsin(x.z),
            fastAsin(x.w));
    }

    // acos
    template <typename T> 
    inline T fastAcos(const T x)
    {
        return T(1.5707963267948966192313216916398) - fastAsin(x); //(PI / 2)
    }

    template <typename T> detail::tvec2<T> fastAcos(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastAcos(x.x),
            fastAcos(x.y));
    }

    template <typename T> detail::tvec3<T> fastAcos(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastAcos(x.x),
            fastAcos(x.y),
            fastAcos(x.z));
    }

    template <typename T> detail::tvec4<T> fastAcos(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastAcos(x.x),
            fastAcos(x.y),
            fastAcos(x.z),
            fastAcos(x.w));
    }

    // atan
    template <typename T> 
    inline T fastAtan(const T y, const T x)
    {
        T sgn = sign(y) * sign(x);
        return abs(fastAtan(y / x)) * sgn;
    }

    template <typename T> 
    inline detail::tvec2<T> fastAtan(
		const detail::tvec2<T>& y, 
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastAtan(y.x, x.x),
            fastAtan(y.y, x.y));
    }

    template <typename T> 
    inline detail::tvec3<T> fastAtan(
		const detail::tvec3<T>& y, 
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastAtan(y.x, x.x),
            fastAtan(y.y, x.y),
            fastAtan(y.z, x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> fastAtan(
		const detail::tvec4<T>& y, 
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastAtan(y.x, x.x),
            fastAtan(y.y, x.y),
            fastAtan(y.z, x.z),
            fastAtan(y.w, x.w));
    }

    template <typename T> 
    inline T fastAtan(const T x)
    {
        return x - (x * x * x * T(0.333333333333)) + (x * x * x * x * x * T(0.2)) - (x * x * x * x * x * x * x * T(0.1428571429)) + (x * x * x * x * x * x * x * x * x * T(0.111111111111)) - (x * x * x * x * x * x * x * x * x * x * x * T(0.0909090909));
    }

    template <typename T> 
    inline detail::tvec2<T> fastAtan(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastAtan(x.x),
            fastAtan(x.y));
    }

    template <typename T> 
    inline detail::tvec3<T> fastAtan(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastAtan(x.x),
            fastAtan(x.y),
            fastAtan(x.z));
    }

    template <typename T> 
    inline detail::tvec4<T> fastAtan(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastAtan(x.x),
            fastAtan(x.y),
            fastAtan(x.z),
            fastAtan(x.w));
    }

}//namespace fast_trigonometry
}//namespace gtx
}//namespace glm
