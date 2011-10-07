///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-09
// Updated : 2006-01-09
// Licence : This source is under MIT License
// File    : glm/gtx/fast_exponential.h
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace fast_exponential
{
    // fastPow:
	template <typename T>
    inline T fastPow(const T x, const T y)
    {
        return exp(y * log(x));
    }

    template <typename T>
    inline detail::tvec2<T> fastPow(
		const detail::tvec2<T>& x, 
		const detail::tvec2<T>& y)
    {
        return detail::tvec2<T>(
            fastPow(x.x, y.x),
            fastPow(x.y, y.y));
    }

    template <typename T>
    inline detail::tvec3<T> fastPow(
		const detail::tvec3<T>& x, 
		const detail::tvec3<T>& y)
    {
        return detail::tvec3<T>(
            fastPow(x.x, y.x),
            fastPow(x.y, y.y),
            fastPow(x.z, y.z));
    }

    template <typename T>
    inline detail::tvec4<T> fastPow(
		const detail::tvec4<T>& x, 
		const detail::tvec4<T>& y)
    {
        return detail::tvec4<T>(
            fastPow(x.x, y.x),
            fastPow(x.y, y.y),
            fastPow(x.z, y.z),
            fastPow(x.w, y.w));
    }

	template <typename T>
	inline T fastPow(const T x, int y)
    {
        T f = T(1);
        for(int i = 0; i < y; ++i)
            f *= x;
        return f;
    }

    template <typename T>
    inline detail::tvec2<T> fastPow(
		const detail::tvec2<T>& x, 
		const detail::tvec2<int>& y)
    {
        return detail::tvec2<T>(
            fastPow(x.x, y.x),
            fastPow(x.y, y.y));
    }

    template <typename T>
    inline detail::tvec3<T> fastPow(
		const detail::tvec3<T>& x, 
		const detail::tvec3<int>& y)
    {
        return detail::tvec3<T>(
            fastPow(x.x, y.x),
            fastPow(x.y, y.y),
            fastPow(x.z, y.z));
    }

    template <typename T>
    inline detail::tvec4<T> fastPow(
		const detail::tvec4<T>& x, 
		const detail::tvec4<int>& y)
    {
        return detail::tvec4<T>(
            fastPow(x.x, y.x),
            fastPow(x.y, y.y),
            fastPow(x.z, y.z),
            fastPow(x.w, y.w));
    }

    // fastExp
    // Note: This function provides accurate results only for value between -1 and 1, else avoid it.
	template <typename T>
    inline T fastExp(const T x)
    {
        // This has a better looking and same performance in release mode than the following code. However, in debug mode it's slower.
        // return 1.0f + x * (1.0f + x * 0.5f * (1.0f + x * 0.3333333333f * (1.0f + x * 0.25 * (1.0f + x * 0.2f))));
        T x2 = x * x;
        T x3 = x2 * x;
        T x4 = x3 * x;
        T x5 = x4 * x;
        return T(1) + x + (x2 * T(0.5)) + (x3 * T(0.1666666667)) + (x4 * T(0.041666667)) + (x5 * T(0.008333333333));
    }
/*  // Try to handle all values of float... but often shower than std::exp, glm::floor and the loop kill the performance
    inline float fastExp(float x)
    {
        const float e = 2.718281828f;
        const float IntegerPart = floor(x);
        const float FloatPart = x - IntegerPart;
        float z = 1.f;

        for(int i = 0; i < int(IntegerPart); ++i)
            z *= e;

        const float x2 = FloatPart * FloatPart;
        const float x3 = x2 * FloatPart;
        const float x4 = x3 * FloatPart;
        const float x5 = x4 * FloatPart;
        return z * (1.0f + FloatPart + (x2 * 0.5f) + (x3 * 0.1666666667f) + (x4 * 0.041666667f) + (x5 * 0.008333333333f));
    }

    // Increase accuracy on number bigger that 1 and smaller than -1 but it's not enough for high and negative numbers
    inline float fastExp(float x)
    {
        // This has a better looking and same performance in release mode than the following code. However, in debug mode it's slower.
        // return 1.0f + x * (1.0f + x * 0.5f * (1.0f + x * 0.3333333333f * (1.0f + x * 0.25 * (1.0f + x * 0.2f))));
        float x2 = x * x;
        float x3 = x2 * x;
        float x4 = x3 * x;
        float x5 = x4 * x;
        float x6 = x5 * x;
        float x7 = x6 * x;
        float x8 = x7 * x;
        return 1.0f + x + (x2 * 0.5f) + (x3 * 0.1666666667f) + (x4 * 0.041666667f) + (x5 * 0.008333333333f)+ (x6 * 0.00138888888888f) + (x7 * 0.000198412698f) + (x8 * 0.0000248015873f);;
    }
*/
    template <typename T>
    inline detail::tvec2<T> fastExp(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastExp(x.x),
            fastExp(x.y));
    }

    template <typename T>
    inline detail::tvec3<T> fastExp(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastExp(x.x),
            fastExp(x.y),
            fastExp(x.z));
    }

    template <typename T>
    inline detail::tvec4<T> fastExp(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastExp(x.x),
            fastExp(x.y),
            fastExp(x.z),
            fastExp(x.w));
    }

    // fastLog
	template <typename T>
    inline T fastLog(const T x)
    {
        return std::log(x);
    }

    /* Slower than the VC7.1 function...
    inline float fastLog(float x)
    {
        float y1 = (x - 1.0f) / (x + 1.0f);
        float y2 = y1 * y1;
        return 2.0f * y1 * (1.0f + y2 * (0.3333333333f + y2 * (0.2f + y2 * 0.1428571429f)));
    }
    */

    template <typename T>
    inline detail::tvec2<T> fastLog(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastLog(x.x),
            fastLog(x.y));
    }

    template <typename T>
    inline detail::tvec3<T> fastLog(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastLog(x.x),
            fastLog(x.y),
            fastLog(x.z));
    }

    template <typename T>
    inline detail::tvec4<T> fastLog(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastLog(x.x),
            fastLog(x.y),
            fastLog(x.z),
            fastLog(x.w));
    }

    //fastExp2, ln2 = 0.69314718055994530941723212145818f
	template <typename T>
    inline T fastExp2(const T x)
    {
        return fastExp(0.69314718055994530941723212145818f * x);
    }

    template <typename T>
    inline detail::tvec2<T> fastExp2(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastExp2(x.x),
            fastExp2(x.y));
    }

    template <typename T>
    inline detail::tvec3<T> fastExp2(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastExp2(x.x),
            fastExp2(x.y),
            fastExp2(x.z));
    }

    template <typename T>
    inline detail::tvec4<T> fastExp2(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastExp2(x.x),
            fastExp2(x.y),
            fastExp2(x.z),
            fastExp2(x.w));
    }

    // fastLog2, ln2 = 0.69314718055994530941723212145818f
	template <typename T>
    inline T fastLog2(const T x)
    {
        return fastLog(x) / 0.69314718055994530941723212145818f;
    }

    template <typename T>
    inline detail::tvec2<T> fastLog2(
		const detail::tvec2<T>& x)
    {
        return detail::tvec2<T>(
            fastLog2(x.x),
            fastLog2(x.y));
    }

    template <typename T>
    inline detail::tvec3<T> fastLog2(
		const detail::tvec3<T>& x)
    {
        return detail::tvec3<T>(
            fastLog2(x.x),
            fastLog2(x.y),
            fastLog2(x.z));
    }

    template <typename T>
    inline detail::tvec4<T> fastLog2(
		const detail::tvec4<T>& x)
    {
        return detail::tvec4<T>(
            fastLog2(x.x),
            fastLog2(x.y),
            fastLog2(x.z),
            fastLog2(x.w));
    }

}//namespace fast_exponential
}//namespace gtx
}//namespace glm
